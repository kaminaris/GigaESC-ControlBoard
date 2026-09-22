# GigaControl connector pinout

Generated from the saved schematic on 2026-09-22. Pin numbers refer to the control-card sockets, not a viewing direction. Match numbered physical contacts on the mating power board.

J1–J3: 1 mm pitch 2×10 female sockets, local footprint `Hanxia_HX_PM1.0-2x10P_ZC`.

| Connector | Odd pin | Signal | Even pin | Signal |
|---|---:|---|---:|---|
| J1 | 1 | `+5V` | 2 | `GND` |
| J1 | 3 | `+3.3V` | 4 | `+3.3REF` |
| J1 | 5 | `POWER-STAGE-DISABLE` | 6 | `POWER-STAGE-LOCKOUT` |
| J1 | 7 | `MOSTEMP3` | 8 | `IN-V` |
| J1 | 9 | `H3` | 10 | `GND` |
| J1 | 11 | `L3` | 12 | `GND` |
| J1 | 13 | `CURR3-FILTERED` | 14 | `GND` |
| J1 | 15 | `VSENSE3` | 16 | `GND` |
| J1 | 17 | `MOSTEMP2` | 18 | `GND` |
| J1 | 19 | `H2` | 20 | `GND` |
| J2 | 1 | `L2` | 2 | `GND` |
| J2 | 3 | `CURR2-FILTERED` | 4 | `GND` |
| J2 | 5 | `VSENSE2` | 6 | `GND` |
| J2 | 7 | `MOSTEMP1` | 8 | `GND` |
| J2 | 9 | `H1` | 10 | `GND` |
| J2 | 11 | `L1` | 12 | `GND` |
| J2 | 13 | `CURR1-FILTERED` | 14 | `GND` |
| J2 | 15 | `VSENSE1` | 16 | `GND` |
| J2 | 17 | `SPI1-NSS` | 18 | `SPI1-MOSI` |
| J2 | 19 | `SPI1-SCK-ADC` | 20 | `SPI1-MISO-ADC2` |
| J3 | 1 | `USBD+` | 2 | `USBD-` |
| J3 | 3 | `SWDIO` | 4 | `GND` |
| J3 | 5 | `SWCLK` | 6 | `I2C2-SDA/USART3-RX` |
| J3 | 7 | `GND` | 8 | `I2C2-SCL/USART3-TX` |
| J3 | 9 | `HALL1-IN` | 10 | `GND` |
| J3 | 11 | `HALL2-IN` | 12 | `SERVO` |
| J3 | 13 | `HALL3-IN` | 14 | `IN-CANL` |
| J3 | 15 | `TEMPMOTOR-IN` | 16 | `IN-CANH` |
| J3 | 17 | `NRST` | 18 | `GND` |
| J3 | 19 | `ESP-TX` | 20 | `ESP-RX` |

J1/J2/J3 mate with GigaDFN56 J31/J32/J33 respectively. Control phase 1 maps to power-board phase 3, phase 2 to phase 2, and phase 3 to phase 1; each mapping includes H, L, current, phase voltage and MOSFET temperature. Other signals match directly.

J1 pin 4 exports the analog reference; J1 pin 8 receives divided bus voltage. No raw battery voltage crosses this interface. USB carries data and ground only; the external connector is on the power board.

The connectors are unkeyed. Verify orientation, insertion depth and mechanical support against the assembled boards.
