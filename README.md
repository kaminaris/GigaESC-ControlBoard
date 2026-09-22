# GigaControl

Compact six-layer control card for modular GigaESC motor controllers. The MCU, CAN transceiver, IMU and signal conditioning live here; the MOSFET power stage and power supply are separate boards.

## Hardware

- STM32F405RGT6 with an 8 MHz oscillator.
- SIT3051 CAN transceiver with onboard 120 Ω termination.
- LSM6DS3TR-C IMU on I²C.
- REF3033 analog supply/reference, also exported to the power board.
- Three 1 mm pitch 2×10 female sockets for power, PWM, feedback and external interfaces.
- USB data, SWD, Hall inputs, motor temperature, SERVO, UART and shared SPI/ADC signals pass through the power board.

Open `GigaControl.kicad_pro` in KiCad 10. Local symbols and footprints are included. Keep `HDR-TH_20P-P1.00-V-F-R2-C10-S1.00.step` beside the project for the connector models. Some other models still use `KICAD9_3DMODEL_DIR`; configure that variable if they are missing in KiCad 10.

See [connector pinout](CONNECTOR_PINOUT.md) for the current interface and [firmware adaptation guide](bldc-config/VESC-CONFIG-GUIDE.md) for the supplied VESC configuration template.

## Design notes

- 1 µF VCAP capacitors, the shared SPI/ADC filtering and the REF3033 arrangement are intentional choices reported tested by the designer. This does not imply validation of every optional interface mode.
- Bridge JP1 only when U3 (REF3033) is not fitted; it supplies VDDA from the main 3.3 V rail.
- Phase numbering is local to each board. The current GigaDFN56 pairing exchanges phase groups 1 and 3 consistently across PWM and feedback; phase 2 is unchanged.
- Adapt the firmware configuration to the actual power board and application before use.

## Repository housekeeping

Keep the KiCad project, active schematic sheets (`MCU`, `Filters`, `CAN`, `IMU`), local libraries, library tables, connector STEP model and firmware configuration sources.

Cleanup candidates, not deleted:

- Regenerable/local files: `fp-info-cache`, `GigaControl.dsn`, `GigaControl.step`, `.idea/`, `*.kicad_prl`, and `_autosave-*`.
- Old recovery files: `X3.0CH-Library.bak` and `GigaControl-backups/`, once their contents are no longer needed. Leave active lock files alone while KiCad is open.
- Unreferenced schematic files: `Connectors.kicad_sch`, `ESP32.kicad_sch`, and the empty `Power.kicad_sch`. Archive or remove after confirming they are not wanted as design references.
- Legacy footprints: `X3.0CH-Master`, `X3.0CH`, and `SolderJumper-3-0.5-Small` are not used by the current board; retain if other projects share this library.
- `production/` contains generated outputs; preserve any release/manufacturing records that still matter.

Review on 2026-09-22: saved-board DRC reports no violations, unconnected items or schematic mismatches. ERC has one warning for PB2 tied to GND. These checks do not replace hardware validation.
