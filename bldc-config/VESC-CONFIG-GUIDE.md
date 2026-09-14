# BLDC / VESC config adaptation guide

The files in this folder are a **starting hardware configuration** for this compute module:

- `hw_giga_devkit_xkb_v3.h`
- `hw_giga_devkit_xkb_v3.c`

They are meant to be reused when building a custom VESC power board around this module, but several values must be updated for the final hardware.

## What this config represents

- Compute-module side (STM32, interface signals, logic-level control, basic mappings)
- A reference power-stage assumption used during development

If your gate driver, shunts, divider ratios, thermistors, or protection strategy differ, this config must be edited before production use.

## Integration into VESC firmware

1. Copy these two files into your VESC firmware hardware config area.
2. Build with the matching target:
   - `make -j24 giga_devkit_xkb_v3`
3. Flash firmware and validate on low-voltage/current-limited supply first.

## Parameters that usually require changes

| Area | Where | Typical reason to change |
|---|---|---|
| Input voltage scaling | `VIN_R1`, `VIN_R2` in `.h` | Your bus-voltage divider uses different resistor values |
| Current measurement model | `CURRENT_SHUNT_RES`, `CURRENT_AMP_GAIN`, `BOOST_*` in `.h` | Different shunt value, amplifier gain, or sensor topology |
| Current calibration | `CURRENT_CAL1/2/3` in `.h` | Remove phase gain mismatch after hardware bring-up |
| ADC channel mapping | `hw_setup_adc_channels()` in `.c`, ADC index macros in `.h` | Your analog nets are routed to different MCU ADC pins |
| Temperature model | `NTC_TEMP_*`, beta assumptions in `.h` | Different NTC beta/value or placement |
| Driver polarity / fault behavior | `ENABLE_GATE`, `DISABLE_GATE`, `IS_DRV_FAULT` in `.h` | Different gate driver enable polarity or fault pin polarity |
| Dead time | `HW_DEAD_TIME_NSEC` in `.h` | Different MOSFET + driver switching characteristics |
| Electrical limits | `HW_LIM_*`, `MCCONF_L_*`, `MCCONF_FOC_*` in `.h` | Match voltage, current, thermal, ERPM, and duty limits to your power stage |

## Minimum checklist before first full-power test

1. Confirm pinout/mappings against your power-board schematic.
2. Recalculate and set voltage divider and current-sense parameters.
3. Verify gate enable and fault polarity with scope/logic checks.
4. Set conservative voltage/current/temperature limits.
5. Calibrate current channels (`CURRENT_CAL1/2/3`), then re-test.
6. Increase limits gradually only after thermal and fault behavior is verified.

## Recommended workflow for new power boards

1. Keep this compute-module mapping as baseline.
2. Fork the config under a new board name (do not overwrite blindly).
3. Update electrical model values first (voltage/current/temp).
4. Update protection and limits.
5. Perform staged bring-up: low-voltage -> nominal voltage -> load testing.

This approach keeps the compute module reusable while allowing safe tuning for each new power board design.
