# GigaControl connector pinout

Three 2x10, 1.00 mm pitch straight female sockets on the control card: Hanxia HX PM1.0-2x10P ZC, LCSC C22465702. Matching proposed right-angle male headers on the power board: HX PZ1.0-2x10P WZ, C22465711.

F.Cu view: J1, J2, J3 left to right; odd row at Y=88.1, even row at Y=87.1. Pad-1 X positions: 138.1, 150.1, 162.1 mm. Three sockets span 34.4 mm of nominal housing length. Phase contacts and connector positions are preserved. Three reserved interface contacts have been reclaimed for GND; active peripheral signals retain their numeric sequence while shifting pins.

J3 GND contacts: pins 1, 10, and 20 (left, middle, right). Peripheral remapping starts at J2 pin 17; the table below is authoritative.

| Column | Connector | Odd pin | Signal | Even pin | Signal |
|---:|---|---:|---|---:|---|
| 1 | J1 | 1 | `+5V` | 2 | `GND` |
| 2 | J1 | 3 | `+3.3V` | 4 | `IN V` |
| 3 | J1 | 5 | `POWER STAGE DISABLE` | 6 | `POWER STAGE LOCKOUT` |
| 4 | J1 | 7 | `MOSTEMP3` | 8 | `GND` |
| 5 | J1 | 9 | `H3` | 10 | `GND` |
| 6 | J1 | 11 | `L3` | 12 | `GND` |
| 7 | J1 | 13 | `CURR3 FILTERED` | 14 | `GND` |
| 8 | J1 | 15 | `VSENSE3` | 16 | `GND` |
| 9 | J1 | 17 | `MOSTEMP2` | 18 | `GND` |
| 10 | J1 | 19 | `H2` | 20 | `GND` |
| 11 | J2 | 1 | `L2` | 2 | `GND` |
| 12 | J2 | 3 | `CURR2 FILTERED` | 4 | `GND` |
| 13 | J2 | 5 | `VSENSE2` | 6 | `GND` |
| 14 | J2 | 7 | `MOSTEMP1` | 8 | `GND` |
| 15 | J2 | 9 | `H1` | 10 | `GND` |
| 16 | J2 | 11 | `L1` | 12 | `GND` |
| 17 | J2 | 13 | `CURR1 FILTERED` | 14 | `GND` |
| 18 | J2 | 15 | `VSENSE1` | 16 | `GND` |
| 19 | J2 | 17 | `SPI1-MOSI` | 18 | `USBD-` |
| 20 | J2 | 19 | `SPI1-MISO-ADC2` | 20 | `USBD+` |
| 21 | J3 | 1 | `GND` | 2 | `SPI1-SCK-ADC` |
| 22 | J3 | 3 | `ESP-TX` | 4 | `SPI1-NSS` |
| 23 | J3 | 5 | `ESP-RX` | 6 | `IN-CANH` |
| 24 | J3 | 7 | `HALL-VOLTAGE` | 8 | `IN-CANL` |
| 25 | J3 | 9 | `HALL1 IN` | 10 | `GND` |
| 26 | J3 | 11 | `HALL2 IN` | 12 | `HALL3 IN` |
| 27 | J3 | 13 | `SERVO` | 14 | `TEMPMOTOR IN` |
| 28 | J3 | 15 | `NRST` | 16 | `I2C2 SDA{slash}USART3 RX` |
| 29 | J3 | 17 | `I2C2 SCL{slash}USART3 TX` | 18 | `SWDIO` |
| 30 | J3 | 19 | `SWCLK` | 20 | `GND` |

Phase 3: columns 4-8; phase 2: 9-13; phase 1: 14-18. All 41 active non-ground signals retained, with 19 ground contacts. RESERVED1/2/3 no longer cross the connector; their MCU-side circuitry is unchanged.

## Mechanical notes

- Local socket footprint follows the Hanxia drawing: body 10.4 x 2.5 mm, height 2 mm, 1 x 1 mm pin grid, 0.50 mm finished holes. Pads are 0.8 mm; courtyard includes body tolerance plus assembly clearance. No 3D model is assigned.
- Numbering is the project logical odd/even convention; the unkeyed manufacturer drawing does not define pin 1. Power-board mating placement must map contacts physically, not copy the control footprint rotation blindly.
- Upright card inserts horizontally with right-angle male pins on the horizontal power board. Allow withdrawal clearance and provide a guide/support; do not rely on the three connectors for vibration support.
- Header drawing has 0.30 mm square contacts and 2.00 mm nominal horizontal exposed tips; the 1.8 mm dimension is vertical tail projection. Socket drawing does not specify a recommended mating-pin insertion range; verify engagement with samples before manufacture.
- Connector fanout remains unfinished; moving pads does not reroute existing traces. No raw battery voltage crosses the interface.
