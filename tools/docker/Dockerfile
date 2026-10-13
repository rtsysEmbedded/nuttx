# SPDX-License-Identifier: Apache-2.0
#
# Portable NuttX build environment.
#
# Every setting (packages, toolchain version/checksums, nuttx-apps revision,
# board, artifacts) is read from config.json in this directory.  The only
# value Docker syntax forces into this file is the FROM base image.
#
# Build (context is this directory):
#   docker build -t nuttx-builder tools/docker
#
# See tools/docker/README.md for usage.

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive \
    NUTTX_DOCKER_CONFIG=/etc/nuttx-docker/config.json

COPY config.json ${NUTTX_DOCKER_CONFIG}

# jq is needed first to read the package list from config.json.

RUN apt-get update -qq \
 && apt-get install -y -qq --no-install-recommends jq ca-certificates \
 && jq -r '.image.apt_packages[]' "${NUTTX_DOCKER_CONFIG}" \
      | xargs apt-get install -y -qq --no-install-recommends \
 && rm -rf /var/lib/apt/lists/*

# Cross toolchain: pick the archive matching the build machine CPU,
# download it and verify the SHA-256 published by Arm.

RUN set -eu; \
    cfg="${NUTTX_DOCKER_CONFIG}"; \
    machine="$(uname -m)"; \
    host="$(jq -r --arg m "$machine" '.image.toolchain.host_map[$m] // empty' "$cfg")"; \
    [ -n "$host" ] || { echo "Unsupported host CPU: $machine" >&2; exit 1; }; \
    version="$(jq -r '.image.toolchain.version' "$cfg")"; \
    target="$(jq -r '.image.toolchain.target' "$cfg")"; \
    dest="$(jq -r '.image.toolchain.install_dir' "$cfg")"; \
    sha="$(jq -r --arg h "$host" '.image.toolchain.sha256[$h]' "$cfg")"; \
    url="$(jq -r '.image.toolchain.url_template' "$cfg" \
           | sed -e "s|{version}|$version|g" -e "s|{host}|$host|g" -e "s|{target}|$target|g")"; \
    echo "Toolchain: $url"; \
    curl -fsSL -o /tmp/toolchain.tar.xz "$url"; \
    echo "$sha  /tmp/toolchain.tar.xz" | sha256sum -c -; \
    mkdir -p "$dest"; \
    tar -C "$dest" --strip-components=1 -xJf /tmp/toolchain.tar.xz; \
    rm -f /tmp/toolchain.tar.xz; \
    ln -s "$dest"/bin/* /usr/local/bin/; \
    "${target}-gcc" --version | head -1

# nuttx-apps at the pinned revision (can be overridden at run time by
# mounting your own apps tree, see README.md).

RUN set -eu; \
    cfg="${NUTTX_DOCKER_CONFIG}"; \
    repo="$(jq -r '.image.apps.repository' "$cfg")"; \
    ref="$(jq -r '.image.apps.ref' "$cfg")"; \
    dest="$(jq -r '.image.apps.install_dir' "$cfg")"; \
    git init -q "$dest"; \
    git -C "$dest" remote add origin "$repo"; \
    git -C "$dest" fetch -q --depth 1 origin "$ref"; \
    git -C "$dest" checkout -q FETCH_HEAD; \
    rm -rf "$dest/.git"; \
    chmod -R a+rwX "$dest"

# The workspace is a bind mount whose owner may differ from the build user.

RUN git config --system --add safe.directory '*'

# Strip CR in case the file was checked out with CRLF on Windows.

COPY entrypoint.sh /usr/local/bin/nuttx-docker
RUN sed -i 's/\r$//' /usr/local/bin/nuttx-docker "${NUTTX_DOCKER_CONFIG}" \
 && chmod 0755 /usr/local/bin/nuttx-docker

ENTRYPOINT ["/usr/local/bin/nuttx-docker"]
CMD ["build"]
