# FRDM-MCXN947

NuttX board support for the NXP **FRDM-MCXN947** development board, built on
the existing `mcx-nxxx` architecture port (the same port that supports the
MCXN236 / FRDM-MCXN236).

> **Status:** compile-tested only (Make and CMake, GCC 13.2.1). Not yet
> verified on real hardware. See [Open items](#open-items) before relying on
> it.

## 1. Chip summary

| Item | Value | Source |
|---|---|---|
| CPU | 2 × Arm Cortex-M33 (CPU0 + CPU1). NuttX runs on CPU0 only. | SDK `MCXN947_cm33_core0.h` / `_core1.h` |
| Core clock used by NuttX | 150 MHz (FIRC 48 MHz → PLL0) | SDK `BOARD_BootClockPLL150M()` |
| Internal flash | 2 MB at `0x0000_0000` (bank 1 starts at `0x0010_0000`) | SDK `MCXN947_cm33_core0_flash.ld` |
| System SRAM (RAMA–RAMH) | 416 KB at `0x2000_0000`–`0x2006_7FFF` | SDK core0 + core1 linker files |
| SRAMX | 96 KB at `0x0400_0000` (not used yet) | SDK `MCXN947_cm33_core0_flash.ld` |
| NVIC | 156 external interrupts (172 vectors), 3 priority bits | SDK `NUMBER_OF_INT_VECTORS`, `__NVIC_PRIO_BITS` |

## 2. Board resources

| Function | MCU pin | Notes |
|---|---|---|
| Console RX (LPUART4) | P1_8 = FC4_P0, ALT2 | MCU-Link VCOM, USB-C connector **J17** |
| Console TX (LPUART4) | P1_9 = FC4_P1, ALT2 | 115200 8N1 |
| LED red | P0_10 | Active low. No NuttX LED driver yet. |
| LED green | P0_27 | Active low. No NuttX LED driver yet. |
| LED blue | P1_2 | Active low. No NuttX LED driver yet. |
| Button SW2 | P0_23 | No NuttX button driver yet. |
| Button SW3 | P0_6 | No NuttX button driver yet. |

Pin data is taken from the NXP MCUXpresso SDK example board files for
`frdmmcxn947` (`board.h` and `demo_apps/hello_world/cm33_core0/pin_mux.c`).

## 3. Configurations

### `nsh`

NuttShell on LPUART4 (MCU-Link virtual COM port), with `procfs` mounted at
`/proc` and `ostest` built in.

Build with Make:

```sh
cd nuttx
./tools/configure.sh -l frdm-mcxn947:nsh
make -j$(nproc)
```

Build with CMake:

```sh
cmake -S nuttx -B build -DBOARD_CONFIG=frdm-mcxn947:nsh
cmake --build build -j$(nproc)
```

The build produces `nuttx` (ELF), `nuttx.bin` (raw binary, load address
`0x0000_0000`) and `nuttx.hex`.

## 4. Flashing and console

1. Connect a USB-C cable to the MCU-Link port **J17**. This one port gives
   both the debug probe (CMSIS-DAP) and the virtual COM port.
2. Program `nuttx.hex` (or `nuttx.bin` at `0x0`) with any tool that supports
   the MCXN947 through MCU-Link: NXP LinkServer, MCUXpresso IDE, pyOCD with
   the MCXN947 device pack, or J-Link if the MCU-Link was reflashed with
   J-Link firmware.
3. Open the virtual COM port at **115200 8N1**, with no flow control, and
   reset the board. The `nsh>` prompt should appear.

## 5. How the chip support was derived

All MCXN947-specific data was taken from the NXP MCUXpresso SDK, not typed in
by hand:

| NuttX file | SDK source |
|---|---|
| `arch/arm/include/mcx-nxxx/n947_irq.h` | `IRQn_Type` in `MCXN947_cm33_core0.h` |
| `arch/arm/src/mcx-nxxx/hardware/n947/n947_memorymap.h` | `*_BASE` (non-secure) in `MCXN947_cm33_core0.h` |
| `arch/arm/src/mcx-nxxx/hardware/n947/n947_clock.h` | `SYSCON_Type` offsets in `MCXN947_cm33_core0.h`, and `clock_attach_id_t` / `clock_ip_name_t` in `drivers/fsl_clock.h` |
| `arch/arm/src/mcx-nxxx/hardware/n947/n947_gpio.h` | Same register layout as N236 (checked, see below) |

SDK revisions used:

- `nxp-mcuxpresso/mcux-sdk` @ `8a289764d763` (device header "rev. 2.0,
  2023-02-01, build b240715")
- `nxp-mcuxpresso/mcux-sdk-examples` @ `52b428258efd` (`frdmmcxn947` board
  files)

### Verification performed

1. **Method check against N236.** The same extraction was run on the SDK's
   MCXN236 files and compared with the existing hand-written NuttX N236
   headers. IRQ numbers (156/156), peripheral base addresses, and clock-mux
   selector values (281/281) all match.
2. **N236 → N947 register compatibility.** The register layouts that the
   shared `mcx-nxxx` drivers use were compared field by field between the two
   SDK device headers:
   - `SPC`, `FMU`, `PORT`, `GPIO`, `LPUART` and `LP_FLEXCOMM` are identical.
   - `SCG` is identical except `TROCSR` (`0x900`). That register exists only
     on N236 and NuttX does not use it.
   - `SYSCON` on the N947 has every N236 register at the same offset. The
     N947 only adds registers (FlexComm 8/9, USB0, SCT, TSI, SINC, DAC,
     FlexSPI, uSDHC, ENET, CMP2, EMVSIM, I3C extras, CPU1 control).
   - Clock gates: all 137 `AHBCLKCTRLn` bit positions in NuttX match the N947
     SDK `kCLOCK_*` gate list exactly.
3. **IRQ table.** The N947 table keeps every N236 vector number. It fills the
   slots that are reserved on the N236 (ENET, NPU, USDHC, FlexSPI, eDMA1
   CH8–15, FlexComm 8/9, …). Vector table size in the linked image is
   `0x2B0` = 172 entries, which matches `NUMBER_OF_INT_VECTORS`.
4. **Clock tree.** `nxxx_clockconfig()` performs the same sequence and
   values as the SDK's `BOARD_BootClockPLL150M()` for FRDM-MCXN947: DCDC and
   core LDO in overdrive, flash RWSC = 3, SRAM at 1.2 V, FIRC 48 MHz,
   PLL0 SELI = 27, SELP = 13, N = 8, M = 50, P = 1 → 150 MHz.
   `pll0_setup()` follows the SDK's `CLOCK_SetPLL0Freq()`: it decodes the
   2-bit `APLLCTRL.SOURCE` field, sets `APLLLOCK_CNFG.LOCK_TIME` to
   `(48 MHz / N) / 2000 + 300` = 3300, and waits until
   `APLLCSR.APLL_LOCK` = 1 before MAIN_CLK is switched to PLL0.
5. **Builds.** `frdm-mcxn947:nsh` (Make and CMake) and `frdm-mcxn236:nsh`
   (regression) build with zero warnings. All new and changed C and header
   files pass `tools/nxstyle`.

## 6. Open items

These are known gaps. None of them blocks the `nsh` console path at build
level, but they must be checked during hardware bring-up.

1. **Hardware test.** Boot, console I/O, SysTick timing and `ostest` have
   not been run on a board yet.
2. **`CONFIG_BOARD_LOOPSPERMSEC=2664`** was carried over from FRDM-MCXN236.
   The two boards have the same core, clock (150 MHz) and flash wait-states,
   but the value has not been calibrated on the N947. Calibrate it with
   `CONFIG_EXAMPLES_CALIB_UDELAY`.
3. **LPUART instance numbering.** The `mcx-nxxx` Kconfig offers LPUART1–9,
   but the driver (`nxxx_lpuart.c`, `nxxx_lowputc.c`) implements LPUART0–7.
   FlexComm 8/9 (N947 only) are not wired into the driver yet. The console
   (LPUART4) is not affected.
4. **Not used yet:** CPU1, SRAMX, the on-board LEDs and buttons, and the
   peripherals that only the N947 has (ENET, USB0 FS, uSDHC, FlexSPI, DAC,
   OPAMP, PowerQuad, NPU, FlexComm 8/9, …).
