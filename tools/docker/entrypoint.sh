#!/usr/bin/env bash
# SPDX-License-Identifier: Apache-2.0
#
# Container entrypoint for the portable NuttX build environment.
# All settings come from config.json (see tools/docker/README.md).
#
# Usage: nuttx-docker <command> [args]
#   build [board:config]      configure (if needed) and build
#   configure <board:config>  distclean and configure
#   menuconfig                run menuconfig on the current configuration
#   savedefconfig             write defconfig of the current configuration
#   clean | distclean         clean the tree
#   shell                     interactive shell inside the environment
#   <anything else>           executed as-is inside the workspace

set -euo pipefail

baked_cfg="${NUTTX_DOCKER_CONFIG:?NUTTX_DOCKER_CONFIG not set}"

cfgget()
{
  jq -r "$1" "$cfg"
}

# Prefer the config.json of the mounted tree so runtime settings can be
# changed without rebuilding the image.

cfg="$baked_cfg"
workspace="$(cfgget '.build.workspace')"
if [ -r "$workspace/tools/docker/config.json" ]; then
  cfg="$(mktemp)"
  sed 's/\r$//' "$workspace/tools/docker/config.json" > "$cfg"
fi

if [ ! -f "$workspace/Makefile" ] || [ ! -x "$workspace/tools/configure.sh" ]; then
  echo "ERROR: NuttX source tree not mounted at $workspace" >&2
  echo "       docker run --rm -it -v \"\$PWD\":$workspace <image> ..." >&2
  exit 1
fi

# Drop root privileges to the owner of the mounted tree so that generated
# files are not owned by root on the host.

if [ "$(id -u)" = "0" ]; then
  owner_uid="$(stat -c %u "$workspace")"
  owner_gid="$(stat -c %g "$workspace")"
  if [ "$owner_uid" != "0" ]; then
    export HOME=/tmp
    exec setpriv --reuid="$owner_uid" --regid="$owner_gid" --clear-groups \
      "$0" "$@"
  fi
fi

apps_dir="$(cfgget '.image.apps.install_dir')"
apps_override="$(cfgget '.build.apps_override_dir')"
if [ -f "$apps_override/Makefile" ]; then
  apps_dir="$apps_override"
fi

board_config="$(cfgget '.build.board_config')"
host_flag="$(cfgget '.build.configure_host_flag')"
jobs="$(cfgget '.build.jobs')"
if [ "$jobs" = "0" ]; then
  jobs="$(nproc)"
fi
mapfile -t make_args < <(cfgget '.build.make_args[]')
output_dir="$workspace/$(cfgget '.build.output_dir')"
mapfile -t artifacts < <(cfgget '.build.artifacts[]')

cd "$workspace"

do_configure()
{
  local target="$1"

  echo "Configuring $target (apps: $apps_dir)"
  # configure.sh requires the apps path relative to the NuttX directory.

  ./tools/configure.sh -E "$host_flag" \
    -a "$(realpath --relative-to="$workspace" "$apps_dir")" "$target"
}

do_build()
{
  if [ $# -gt 0 ]; then
    do_configure "$1"
  elif [ ! -f .config ]; then
    do_configure "$board_config"
  fi

  make -j"$jobs" "${make_args[@]}"

  mkdir -p "$output_dir"
  for f in "${artifacts[@]}"; do
    if [ -e "$f" ]; then
      cp -f "$f" "$output_dir/"
    fi
  done
  echo "Artifacts copied to $output_dir"
  if [ -f nuttx ]; then
    "$(cfgget '.image.toolchain.target')-size" nuttx 2>/dev/null || true
  fi
}

cmd="${1:-build}"
[ $# -gt 0 ] && shift

case "$cmd" in
  build)
    do_build "$@"
    ;;
  configure)
    do_configure "${1:-$board_config}"
    ;;
  menuconfig|savedefconfig|clean|distclean|olddefconfig)
    make "$cmd"
    ;;
  shell)
    exec bash
    ;;
  *)
    exec "$cmd" "$@"
    ;;
esac
