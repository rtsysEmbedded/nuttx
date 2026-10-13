# Portable NuttX Build Environment (Docker)

This directory contains a self-contained Docker build environment for this
NuttX tree. The same image works on any machine that runs Docker:

| Host                         | CPU            | Tested             |
| ---------------------------- | -------------- | ------------------ |
| Linux                        | x86_64         | Yes                |
| Linux (e.g. Raspberry Pi 5)  | aarch64        | No (see note)      |
| macOS (Docker Desktop)       | Intel / Apple Silicon | No (see note) |
| Windows 10/11 (Docker Desktop, WSL2 backend) | x86_64 / arm64 | No (see note) |

> **Note:** The x86_64 path was built and verified end-to-end
> (`frdm-mcxn947:nsh`). The aarch64 toolchain archive URL and SHA-256 are taken
> from Arm's official `.sha256asc` file, but the aarch64 image was not built
> because no arm64 host or emulator was available during testing.

## Files

| File            | Purpose                                                        |
| --------------- | -------------------------------------------------------------- |
| `Dockerfile`    | Image definition. Reads every setting from `config.json`.      |
| `config.json`   | **Single source of all settings** (packages, toolchain, apps, board, outputs). |
| `entrypoint.sh` | Container entry point (`nuttx-docker`): configure, build, menuconfig, shell. |
| `README.md`     | This document.                                                 |

## How it works

```
 host                                     container (nuttx-builder)
 ─────────────────────────────            ─────────────────────────────────────
 nuttx/ (this repo) ── bind mount ──────▶ /workspace/nuttx
   tools/docker/config.json  ──read at runtime──▶ entrypoint.sh
                                          /opt/toolchains/arm-none-eabi  (image)
                                          /opt/nuttx-apps (pinned, image)
 [optional] apps/   ── bind mount ──────▶ /workspace/apps (overrides /opt/nuttx-apps)
 nuttx/build-output/ ◀──── artifacts ──── make
```

### Build time (`docker build`)

1. `config.json` is copied into the image as `/etc/nuttx-docker/config.json`.
2. `image.apt_packages` are installed from Ubuntu 24.04.
   - `kconfig-frontends-nox` provides `kconfig-tweak`/`kconfig-conf` (used by
     `tools/sethost.sh`).
   - `python3-kconfiglib` provides `menuconfig`/`olddefconfig`; `tools/Unix.mk`
     prefers kconfiglib when it is on `PATH`.
3. The Arm GNU Toolchain is selected by the CPU of the **build machine**
   (`uname -m` → `image.toolchain.host_map`). The archive URL is generated from
   `url_template`, then checked against `image.toolchain.sha256[<host>]`. If the
   checksum does not match, the build fails.
4. `nuttx-apps` is fetched at the exact commit in `image.apps.ref`.
   The default commit `7b383d05` is the `nuttx-apps` master head of 2025-05-13,
   which matches the upstream base of this fork (the same OP-TEE patch series
   appears in both repositories).

### Run time (`docker run`)

1. `entrypoint.sh` reads `tools/docker/config.json` from the **mounted tree**
   (falling back to the copy baked into the image), so you can change
   `build.*` settings without rebuilding the image.
2. If the container starts as root and the mounted tree belongs to a non-root
   user (normal on Linux), the script switches to that UID/GID with `setpriv`.
   Files generated in your tree are then owned by you, not by root.
3. If `/workspace/apps/Makefile` exists (you mounted your own apps tree),
   it is used instead of the pinned copy in the image.
4. `tools/configure.sh -E <host_flag> -a <apps> <board:config>` is run when
   no `.config` exists or a board is given explicitly. Then `make -j<jobs>`
   runs, and `build.artifacts` are copied to `build.output_dir`.

## Usage

All commands are run from the root of this repository.

### 1. Build the image (once, or after changing `image.*` in `config.json`)

```sh
docker build -t nuttx-builder tools/docker
```

### 2. Build the default board (`build.board_config`)

Linux / macOS / WSL / Git Bash:

```sh
docker run --rm -v "$PWD":/workspace/nuttx nuttx-builder
```

Windows PowerShell:

```powershell
docker run --rm -v "${PWD}:/workspace/nuttx" nuttx-builder
```

Windows `cmd.exe`:

```bat
docker run --rm -v "%cd%:/workspace/nuttx" nuttx-builder
```

Outputs appear in `build-output/` (`nuttx`, `nuttx.bin`, `nuttx.hex`,
`nuttx.map`, `.config`).

### 3. Other commands

| Command (append to `docker run --rm -it -v "$PWD":/workspace/nuttx nuttx-builder`) | Effect |
| ---------------------------------- | ------------------------------------------------- |
| `build`                            | Configure if needed, then build (default command). |
| `build frdm-mcxn236:nsh`           | Force reconfigure for that board, then build.     |
| `configure frdm-mcxn947:nsh`       | Only distclean and configure.                     |
| `menuconfig`                       | Interactive configuration (needs `-it`).          |
| `savedefconfig`                    | Write `defconfig` from the current `.config`.     |
| `clean` / `distclean`              | Clean the tree.                                   |
| `shell`                            | Interactive bash inside the environment.          |
| any other command                  | Executed as-is in `/workspace/nuttx` (e.g. `make -j8`). |

### 4. Use your own `nuttx-apps` checkout

Put it next to this repository, or anywhere else, and mount it:

```sh
docker run --rm -v "$PWD":/workspace/nuttx -v "$PWD/../apps":/workspace/apps nuttx-builder
```

## Configuration reference (`config.json`)

| Key                                 | Used at | Meaning |
| ----------------------------------- | ------- | ------- |
| `image.apt_packages`                | build   | Ubuntu packages installed in the image. |
| `image.toolchain.version`           | build   | Arm GNU Toolchain release (e.g. `13.3.rel1`). |
| `image.toolchain.target`            | build/run | Toolchain triplet; also used for `<target>-size`. |
| `image.toolchain.url_template`      | build   | Download URL; `{version}`, `{host}`, `{target}` are substituted. |
| `image.toolchain.host_map`          | build   | Maps `uname -m` to Arm's host name in the archive file name. |
| `image.toolchain.sha256`            | build   | Expected SHA-256 per host archive. **Update together with `version`.** |
| `image.toolchain.install_dir`       | build   | Install location; binaries are symlinked into `/usr/local/bin`. |
| `image.apps.repository` / `.ref`    | build   | `nuttx-apps` source and exact commit, tag or branch. |
| `image.apps.install_dir`            | build/run | Location of the pinned apps tree in the image. |
| `build.workspace`                   | run     | Mount point of this repository inside the container. |
| `build.apps_override_dir`           | run     | If it contains a `Makefile`, it replaces the pinned apps. |
| `build.board_config`                | run     | Default `<board>:<config>`. |
| `build.configure_host_flag`         | run     | Host flag passed to `configure.sh` (`-l` = Linux; the container is always Linux). |
| `build.jobs`                        | run     | `make -j` value; `0` = number of CPUs in the container. |
| `build.make_args`                   | run     | Extra arguments for `make` (e.g. `["V=1"]`). |
| `build.output_dir`                  | run     | Directory (relative to the tree) where artifacts are copied. |
| `build.artifacts`                   | run     | Files copied to `output_dir` after a successful build. |

### Updating the toolchain

1. Pick a release from <https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads>.
2. Get the official checksums:
   ```sh
   V=14.2.rel1
   for h in x86_64 aarch64; do
     curl -sL "https://developer.arm.com/-/media/Files/downloads/gnu/$V/binrel/arm-gnu-toolchain-$V-$h-arm-none-eabi.tar.xz.sha256asc"
   done
   ```
3. Put `version` and both `sha256` values in `config.json`, then rebuild the image.

## Limitations and notes

- **`FROM ubuntu:24.04`** is the only value inside the `Dockerfile`. Docker
  evaluates `FROM` before any file can be read, so it cannot come from JSON.
- **Windows line endings:** the `Dockerfile` strips CR from `entrypoint.sh` and
  `config.json`. The NuttX scripts themselves (`tools/*.sh`) still need LF.
  Clone with `git config --global core.autocrlf false` (or `input`).
- **Windows/macOS performance:** bind mounts from the host file system are
  slow on Docker Desktop. For faster builds, clone the repository inside WSL2
  (Windows) or use a named volume.
- **Corporate proxies / TLS inspection:** if `curl` fails with exit code 60
  during `docker build`, the proxy's CA is not trusted inside the build. Add
  the CA to the build context and install it in an early layer, or build on a
  network without TLS inspection.
- Flashing/debugging (LinkServer, pyOCD, OpenOCD) is **not** included. USB
  pass-through to containers is not portable across Docker Desktop hosts, so
  flash `build-output/nuttx.bin` or `nuttx.hex` from the host.
