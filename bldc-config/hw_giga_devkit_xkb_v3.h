/*
	Copyright 2018 Benjamin Vedder	benjamin@vedder.se

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The VESC firmware is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

///////////////
/// To compile, go ubuntu wsl2 and run: make -j24 giga_devkit_xkb_v3
///////////////

#ifndef HW_GIGA_DEVKIT_CORE_V2_H_
#define HW_GIGA_DEVKIT_CORE_V2_H_

#define HW_NAME							"GigaESC DevKitX3.0-CH"

// HW properties
#define HW_HAS_3_SHUNTS
#define INVERTED_SHUNT_POLARITY
#define HW_HAS_PHASE_FILTERS
// #define HW_USE_25MHZ_EXT_CLOCK
// #define HW_USE_BRK

// Macros

#define HW_ADC_CHANNELS			18
#define HW_ADC_INJ_CHANNELS		3
#define HW_ADC_NBR_CONV			6

// ADC Indexes - refer to .c for descriptions
#define ADC_IND_CURR1			0
#define ADC_IND_CURR2			1
#define ADC_IND_CURR3			2

#define ADC_IND_VIN_SENS		8
#define ADC_IND_SENS1			3
#define ADC_IND_SENS2			4
#define ADC_IND_SENS3			5

#define ADC_IND_EXT				6
#define ADC_IND_EXT2			7

#define ADC_IND_EXT3			10

#define ADC_IND_TEMP_MOS		11
#define ADC_IND_TEMP_MOS_2		12
#define ADC_IND_TEMP_MOS_3		13
#define ADC_IND_TEMP_MOTOR		15

#define ADC_IND_VREFINT			9

// ADC macros and settings

// Component parameters (can be overridden)
#ifndef V_REG
#define V_REG					3.30
#endif
#ifndef VIN_R1
#define VIN_R1					(348.0f * 3.0f)
#endif
#ifndef VIN_R2
#define VIN_R2					(18.7f)
#endif

// Hall sensor sees only a fraction of entire current ex shunt will see 5A while hall sees 1.471A
// We only measure 1.471A out of 6.471A total current so we need to extrapolate it
// Original formula is ((V_REG / 4095.0) / (CURRENT_SHUNT_RES * CURRENT_AMP_GAIN))
#define BOOST_SHUNT             0.0002f
#define BOOST_HALL_INTERNAL_RES 0.00068f
#define BOOST_HALL_SENS         0.033f
#define CURRENT_RATIO           ((BOOST_SHUNT + BOOST_HALL_INTERNAL_RES) / BOOST_SHUNT)

// Effective resistance seen by the measurement
#define CURRENT_SHUNT_RES       BOOST_HALL_SENS
#define CURRENT_AMP_GAIN        (1.0f/CURRENT_RATIO)

/*
#ifndef CURRENT_AMP_GAIN
#define CURRENT_AMP_GAIN		20.0
#endif
// shunt gives 4x the voltage, so divide by 4
#ifndef CURRENT_SHUNT_RES
#define CURRENT_SHUNT_RES		(0.0002)*4
#endif
*/

#define CURRENT_CAL1 0.716605
#define CURRENT_CAL2 0.716605
#define CURRENT_CAL3 0.716605

// Input voltage
#define GET_INPUT_VOLTAGE()		((V_REG / 4095.0) * (float)ADC_Value[ADC_IND_VIN_SENS] * ((VIN_R1 + VIN_R2) / VIN_R2))

// NTC Termistors
#define NTC_RES(adc_val)		((4095.0 * 10000.0) / adc_val - 10000.0)

#define NTC_RES_MOTOR(adc_val)	(10000.0 / ((4095.0 / (float)adc_val) - 1.0)) // Motor temp sensor on low side
#define NTC_TEMP_MOTOR(beta)	(1.0 / ((logf(NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 10000.0) / beta) + (1.0 / 298.15)) - 273.15)

#define NTC_TEMP(adc_ind)		hw_giga_get_temp()
#define NTC_TEMP_MOS1()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS2()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_2]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS3()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_3]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)

// Voltage on ADC channel
#define ADC_VOLTS(ch)			((float)ADC_Value[ch] / 4096.0 * V_REG)

// Double samples in beginning and end for positive current measurement.
// Useful when the shunt sense traces have noise that causes offset.
#ifndef CURR1_DOUBLE_SAMPLE
#define CURR1_DOUBLE_SAMPLE		0
#endif
#ifndef CURR2_DOUBLE_SAMPLE
#define CURR2_DOUBLE_SAMPLE		0
#endif
#ifndef CURR3_DOUBLE_SAMPLE
#define CURR3_DOUBLE_SAMPLE		0
#endif

#define LED_GREEN_GPIO			GPIOD
#define LED_GREEN_PIN			2
#define LED_RED_GPIO			GPIOC
#define LED_RED_PIN				12

#define LED_GREEN_ON()			palSetPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_GREEN_OFF()			palClearPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_RED_ON()			palSetPad(LED_RED_GPIO, LED_RED_PIN)
#define LED_RED_OFF()			palClearPad(LED_RED_GPIO, LED_RED_PIN)

// Aux - TCKE812NA,RF -- not present
#define AUX_GPIO			GPIOB
#define AUX_PIN				3
#define AUX_ON()			palSetPad(AUX_GPIO, AUX_PIN)
#define AUX_OFF()			palClearPad(AUX_GPIO, AUX_PIN)

// Sensor port voltage control -- not present
#define SENSOR_VOLTAGE_GPIO		GPIOB
#define SENSOR_VOLTAGE_PIN		4
#define SENSOR_PORT_5V()		palSetPad(SENSOR_VOLTAGE_GPIO, SENSOR_VOLTAGE_PIN);
#define SENSOR_PORT_3V3()		palClearPad(SENSOR_VOLTAGE_GPIO, SENSOR_VOLTAGE_PIN);

// Phase voltage filter
#define PHASE_FILTER_GPIO		GPIOC
#define PHASE_FILTER_PIN1		9
#define PHASE_FILTER_PIN2		13
#define PHASE_FILTER_PIN3		14
#define PHASE_FILTER_OFF()		palSetPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN1); palSetPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN2); palSetPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN3)
#define PHASE_FILTER_ON()		palClearPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN1); palClearPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN2); palClearPad(PHASE_FILTER_GPIO, PHASE_FILTER_PIN3)

// Hall filter -- not present
#define HALL_FILTER_GPIO		GPIOC
#define HALL_FILTER_PIN			15
#define HALL_FILTER_OFF()		palSetPad(HALL_FILTER_GPIO, HALL_FILTER_PIN);
#define HALL_FILTER_ON()		palClearPad(HALL_FILTER_GPIO, HALL_FILTER_PIN);

// Current filter is permanently on, set it to unused GPIOs
/*
#define CURRENT_FILTER_GPIO1	GPIOE
#define CURRENT_FILTER_PIN1		3
#define CURRENT_FILTER_GPIO2	GPIOE
#define CURRENT_FILTER_PIN2		4
#define CURRENT_FILTER_GPIO3	GPIOE
#define CURRENT_FILTER_PIN3		5

#define CURRENT_FILTER_ON()		palSetPad(CURRENT_FILTER_GPIO1, CURRENT_FILTER_PIN1); \
 								palSetPad(CURRENT_FILTER_GPIO2, CURRENT_FILTER_PIN2); \
 		                        palSetPad(CURRENT_FILTER_GPIO3, CURRENT_FILTER_PIN3);

#define CURRENT_FILTER_OFF()	palClearPad(CURRENT_FILTER_GPIO1, CURRENT_FILTER_PIN1); \
 								palClearPad(CURRENT_FILTER_GPIO2, CURRENT_FILTER_PIN2); \
 								palClearPad(CURRENT_FILTER_GPIO3, CURRENT_FILTER_PIN3);
*/

// COMM-port ADC GPIOs
#define HW_ADC_EXT_GPIO			GPIOA
#define HW_ADC_EXT_PIN			5
#define HW_ADC_EXT2_GPIO		GPIOA
#define HW_ADC_EXT2_PIN			6


// UART Peripheral
#define HW_UART_DEV             SD3
#define HW_UART_GPIO_AF         GPIO_AF_USART3
#define HW_UART_TX_PORT         GPIOB
#define HW_UART_TX_PIN          10
#define HW_UART_RX_PORT         GPIOB
#define HW_UART_RX_PIN          11

// SPI pins
#define HW_SPI_DEV				SPID1
#define HW_SPI_GPIO_AF			GPIO_AF_SPI1
#define HW_SPI_PORT_NSS			GPIOA
#define HW_SPI_PIN_NSS			4
#define HW_SPI_PORT_SCK			GPIOA
#define HW_SPI_PIN_SCK			5
#define HW_SPI_PORT_MOSI		GPIOA
#define HW_SPI_PIN_MOSI			7
#define HW_SPI_PORT_MISO		GPIOA
#define HW_SPI_PIN_MISO			6

// I2C Peripheral
#define HW_I2C_DEV				I2CD2
#define HW_I2C_GPIO_AF			GPIO_AF_I2C2
#define HW_I2C_SCL_PORT			GPIOB
#define HW_I2C_SCL_PIN			10
#define HW_I2C_SDA_PORT			GPIOB
#define HW_I2C_SDA_PIN			11
// Hall/encoder pins
#define HW_HALL_ENC_GPIO1		GPIOC
#define HW_HALL_ENC_PIN1		6
#define HW_HALL_ENC_GPIO2		GPIOC
#define HW_HALL_ENC_PIN2		7
#define HW_HALL_ENC_GPIO3		GPIOC
#define HW_HALL_ENC_PIN3		8

#define HW_ENC_TIM				TIM3
#define HW_ENC_TIM_AF			GPIO_AF_TIM3
#define HW_ENC_TIM_CLK_EN()		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)
#define HW_ENC_EXTI_PORTSRC		EXTI_PortSourceGPIOC
#define HW_ENC_EXTI_PINSRC		EXTI_PinSource8
#define HW_ENC_EXTI_CH			EXTI9_5_IRQn
#define HW_ENC_EXTI_LINE		EXTI_Line8
#define HW_ENC_EXTI_ISR_VEC		EXTI9_5_IRQHandler
#define HW_ENC_TIM_ISR_CH		TIM3_IRQn
#define HW_ENC_TIM_ISR_VEC		TIM3_IRQHandler

// Permanent UART Peripheral (for HM10)
#define HW_UART_P_BAUD			115200
#define HW_UART_P_DEV			SD4
#define HW_UART_P_GPIO_AF		GPIO_AF_UART4
#define HW_UART_P_TX_PORT		GPIOC
#define HW_UART_P_TX_PIN		10
#define HW_UART_P_RX_PORT		GPIOC
#define HW_UART_P_RX_PIN		11

// ICU Peripheral for servo decoding
#define HW_USE_SERVO_TIM4
#define HW_ICU_TIMER			TIM4
#define HW_ICU_TIM_CLK_EN()		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE)
#define HW_ICU_DEV				ICUD4
#define HW_ICU_CHANNEL			ICU_CHANNEL_2
#define HW_ICU_GPIO_AF			GPIO_AF_TIM4
#define HW_ICU_GPIO				GPIOB
#define HW_ICU_PIN				7

// I2C for IMU
#define LSM6DS3_SDA_GPIO        GPIOB
#define LSM6DS3_SDA_PIN         9
#define LSM6DS3_SCL_GPIO        GPIOB
#define LSM6DS3_SCL_PIN         8

// Hardware protection
#define HW_RESET_DRV_FAULTS()	hw_giga_reset_faults()

/*
#define HW_PROTECTION_CLEAR_GPIO	GPIOD
#define HW_PROTECTION_CLEAR_PIN		4
*/

#define HW_POWER_STAGE_DISABLE_GPIO	GPIOC
#define HW_POWER_STAGE_DISABLE_PIN	5

// Do not touch
#define HW_POWER_STAGE_LOCKOUT_GPIO	GPIOB
#define HW_POWER_STAGE_LOCKOUT_PIN	12

#define BRK_GPIO					GPIOB
#define BRK_PIN						12

// STDRIVEG600
#define ENABLE_GATE()  			palSetPad(HW_POWER_STAGE_DISABLE_GPIO, HW_POWER_STAGE_DISABLE_PIN)
#define DISABLE_GATE() 			palClearPad(HW_POWER_STAGE_DISABLE_GPIO, HW_POWER_STAGE_DISABLE_PIN)
#define IS_DRV_FAULT()			!(palReadPad(HW_POWER_STAGE_LOCKOUT_GPIO, HW_POWER_STAGE_LOCKOUT_PIN))

// Normal enabled low
//#define ENABLE_GATE()			palClearPad(HW_POWER_STAGE_DISABLE_GPIO, HW_POWER_STAGE_DISABLE_PIN)
//#define DISABLE_GATE()			palSetPad(HW_POWER_STAGE_DISABLE_GPIO, HW_POWER_STAGE_DISABLE_PIN)
//#define IS_DRV_FAULT()			(palReadPad(HW_POWER_STAGE_LOCKOUT_GPIO, HW_POWER_STAGE_LOCKOUT_PIN))
// #define IS_LV_OUTPUT_FAULT()	!(palReadPad(HW_5V_FAULT_GPIO, HW_5V_FAULT_PIN) && palReadPad(HW_3V3_FAULT_GPIO, HW_3V3_FAULT_PIN))


// Measurement macros
#define ADC_V_L1				ADC_Value[ADC_IND_SENS1]
#define ADC_V_L2				ADC_Value[ADC_IND_SENS2]
#define ADC_V_L3				ADC_Value[ADC_IND_SENS3]
#define ADC_V_ZERO				(ADC_Value[ADC_IND_VIN_SENS] / 2)

// Macros
#define READ_HALL1()			palReadPad(HW_HALL_ENC_GPIO1, HW_HALL_ENC_PIN1)
#define READ_HALL2()			palReadPad(HW_HALL_ENC_GPIO2, HW_HALL_ENC_PIN2)
#define READ_HALL3()			palReadPad(HW_HALL_ENC_GPIO3, HW_HALL_ENC_PIN3)

// Default setting overrides
#ifndef MCCONF_L_MIN_VOLTAGE
#define MCCONF_L_MIN_VOLTAGE			32.0		// Minimum input voltage
#endif

#ifndef MCCONF_DEFAULT_MOTOR_TYPE
#define MCCONF_DEFAULT_MOTOR_TYPE		MOTOR_TYPE_FOC
#endif
// EXPERIMENTAL: we would need to increase FREQ DIVIDER to up the switching frequency
// VESC has soft limit at around 40kHz because of ISR that could crash the RTOS
// BUT increasing divider makes motor detection not working properly
#ifndef MCCONF_FOC_F_ZV
#define MCCONF_FOC_F_ZV					30000.0
#endif
#define FOC_CONTROL_LOOP_FREQ_DIVIDER	1

#define HW_LIM_FOC_CTRL_LOOP_FREQ		5000.0, 25000.0	//Limit to 50kHz max
#ifndef MCCONF_L_MAX_ABS_CURRENT
#define MCCONF_L_MAX_ABS_CURRENT		200.0	// The maximum absolute current above which a fault is generated
#endif
#ifndef MCCONF_FOC_SAMPLE_V0_V7
#define MCCONF_FOC_SAMPLE_V0_V7			false	// Run control loop in both v0 and v7 (requires phase shunts)
#endif
#ifndef MCCONF_L_CURRENT_MAX
#define MCCONF_L_CURRENT_MAX			150.0	// Current limit in Amperes (Upper)
#endif
#ifndef MCCONF_L_CURRENT_MIN
#define MCCONF_L_CURRENT_MIN			-150.0	 // Current limit in Amperes (Lower)
#endif
#ifndef MCCONF_L_SLOW_ABS_OVERCURRENT
#define MCCONF_L_SLOW_ABS_OVERCURRENT	false	// Use the raw current for the overcurrent fault detection
#endif
#ifndef MCCONF_L_IN_CURRENT_MAX
	#define MCCONF_L_IN_CURRENT_MAX			250.0	// Input current limit in Amperes (Upper)
#endif
#ifndef MCCONF_L_IN_CURRENT_MIN
	#define MCCONF_L_IN_CURRENT_MIN			-200.0	// Input current limit in Amperes (Lower)
#endif

// Mosfet and K/W for working out temperatures
#define HW_TEMP_MOSFET_R				0.0017f		// Resistance of mosfets
#define HW_TEMP_MOSFET_KW				2.0f		// Kelvin/Watt of mosfets
#define HW_TEMP_MOSFET_COUNT			3.0f		// How many mosfets in parallel
#define HW_TEMP_SHUNT_KW				25.0f		// Kelvin/Watt of shunts
#define HW_TEMP_NUM_PHASES				3.0f		// How many phases

// Setting limits
#define HW_LIM_CURRENT					-250.0, 250.0
#define HW_LIM_CURRENT_IN				-180.0, 180.0
#define HW_LIM_CURRENT_ABS				0.0, 350.0
#define HW_LIM_VIN						-1.0, 190.0
#define HW_LIM_ERPM						-200e3, 200e3
#define HW_LIM_DUTY_MIN					0.0, 0.1
#define HW_LIM_DUTY_MAX					0.0, 0.99
#define HW_LIM_TEMP_FET					-40.0, 110.0
#ifndef MCCONF_L_MAX_VOLTAGE
#define MCCONF_L_MAX_VOLTAGE			190	// Maximum input voltage
#endif
#ifndef MCCONF_FOC_DT_US
#define MCCONF_FOC_DT_US				0.1 // Microseconds for dead time compensation
#endif

#define HW_DEAD_TIME_NSEC				100.0
// 0.053A at 100ns
// 0.051A at 80ns
// 0.049A at 60ns
// 0.049A at 40ns
// 0.049A at 30ns

// HW-specific functions
float hw_giga_get_temp(void);
void hw_giga_set_curr_trip(uint16_t);
void hw_giga_reset_faults(void);

#endif
