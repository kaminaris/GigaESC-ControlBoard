# DevKitX2-Castellated6L

Compact KiCad-based logic board for a VESC compute module interface.

![Front view](./pic-front.png)
![Back view](./pic-back.png)

## Compute-module concept

This project is intentionally a **compute module** for VESC-based designs: the module carries the critical control electronics (MCU, sensing interface, comms, timing, and core protection/control signals), while the high-power stage is implemented on a separate power board.

The goal is to make custom VESC power-stage design easier and faster: reuse this proven logic module, then adapt only the power-board-specific hardware and firmware parameters.

## Project status

- **Schematic revision:** `V1.1.0`
- **Top sheet date:** `2025-11-01`
- **KiCad format:** v10 (`generator_version "10.0"`)

## Hardware summary

| Item | Value |
|---|---|
| Board outline | 20 mm x 20 mm |
| PCB thickness | 1.5984 mm |
| Copper layers | 6 (`F.Cu`, `In1.Cu`, `In2.Cu`, `In3.Cu`, `In4.Cu`, `B.Cu`) |
| Surface finish | ENIG |
| Solder mask color | Green |
| Main MCU | `STM32F405RGT6` |
| Main interface connector | `J4` / `X3.0CH-Library:X3.0-CH` |
| Main mating footprint | `X3.0CH-Library:X3.0CH-Master` |

## Main castellated footprint pinout (J4)

Pin map below is the authoritative interface mapping used by this project (`X3.0CH-Library.kicad_sym`, symbol `X3.0-CH`).

| Pin | Signal | Pin | Signal |
|---|---|---|---|
| 1 | `POWER_STAGE_DISABLE` | 26 | `USBD+` |
| 2 | `POWER_STAGE_LOCKOUT` | 27 | `USBD-` |
| 3 | `GND` | 28 | `GND` |
| 4 | `IN-V` | 29 | `CANL` |
| 5 | `HALL-VCC` | 30 | `CANH` |
| 6 | `HALL1` | 31 | `GND` |
| 7 | `HALL2` | 32 | `MOSI` |
| 8 | `HALL3` | 33 | `MISO/ADC2` |
| 9 | `TEMP-MOTOR` | 34 | `SCK/ADC` |
| 10 | `GND` | 35 | `NSS` |
| 11 | `3.3V` | 36 | `VSENSE1` |
| 12 | `5V` | 37 | `CURRENT1` |
| 13 | `GND` | 38 | `L1` |
| 14 | `DIO` | 39 | `H1` |
| 15 | `CLK` | 40 | `TEMP1` |
| 16 | `GND` | 41 | `VSENSE2` |
| 17 | `U1-TX` | 42 | `CURRENT2` |
| 18 | `U1-RX` | 43 | `L2` |
| 19 | `RESERVED1` | 44 | `H2` |
| 20 | `NRST` | 45 | `TEMP2` |
| 21 | `SERVO` | 46 | `VSENSE3` |
| 22 | `U3-RX` | 47 | `CURRENT3` |
| 23 | `U3-TX` | 48 | `L3` |
| 24 | `RESERVED2` | 49 | `H3` |
| 25 | `RESERVED3` | 50 | `TEMP3` |

## Interface highlights

- **Power rails:** `+5V`, `+3.3V`, `+3.3REF`, `GND`
- **CAN:** `CAN TX`, `CAN RX`, `IN-CANH`, `IN-CANL`
- **Debug/programming:** `SWDIO`, `SWCLK`, `NRST`
- **USB data:** `USBD+`, `USBD-`
- **Comms/control:** `ESP-TX`, `ESP-RX`, `SERVO`
- **Sensors/analog:** `HALL1/2/3`, `TEMPMOTOR`, `VSENSE1/2/3`, `CURR1/2/3 FILTERED`
- **Digital interface:** `SPI1-MOSI`, `SPI1-MISO-ADC2`, `SPI1-SCK-ADC`, `SPI1-NSS`
- **I2C/UART muxed lines:** `I2C2 SDA/USART3 RX`, `I2C2 SCL/USART3 TX`

## BLDC firmware config for custom power boards

`bldc-config\` contains the VESC hardware config template used with this module:

- `hw_giga_devkit_xkb_v3.h`
- `hw_giga_devkit_xkb_v3.c`

These values are **not final for every design**. When you create a new power board, you should update divider ratios, current-sense parameters, thermal constants, limits, and related mappings to match your hardware.

See the **[BLDC/VESC config adaptation guide](./bldc-config/VESC-CONFIG-GUIDE.md)** for the modification workflow and which parameters must be reviewed.

## Opening the project

1. Open KiCad 10.
2. Open `DevKitX2-Castellated6L.kicad_pro`.
3. If needed, update symbol/footprint library paths so local `X3.0CH-Library` entries resolve.
