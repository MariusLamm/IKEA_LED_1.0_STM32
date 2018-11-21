#ifndef __pca9685_H
#define __pca9685_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f0xx_hal.h"
#include <stdint.h>
#include "main.h"

#define PCA9685_I2C_ADDR					0x80        /**< PCA9685 I2C slave address */

#define PCA9685_INT_OSC_CLK				25000000UL  /**< Clock frequency of the internal oscillator */

#define PCA9685_MODE1							0x00        /**< MODE1 register address */
#define PCA9685_MODE1_RESTART			(1 << 7)    /**< Restart enabled/disabled */
#define PCA9685_MODE1_EXTCLK			(1 << 6)    /**< Use external/internal clock */
#define PCA9685_MODE1_AI					(1 << 5)    /**< Register auto-increment enabled/disabled */
#define PCA9685_MODE1_SLEEP				(1 << 4)    /**< Sleep mode enabled/disabled */
#define PCA9685_MODE1_SUB1				(1 << 3)    /**< Response to I2C subaddress 1 enabled/disabled */
#define PCA9685_MODE1_SUB2				(1 << 2)    /**< Response to I2C subaddress 2 enabled/disabled */
#define PCA9685_MODE1_SUB3				(1 << 1)    /**< Response to I2C subaddress 3 enabled/disabled */
#define PCA9685_MODE1_ALLCALL			(1 << 0)    /**< Response to all call I2C address enabled/disabled */

#define PCA9685_MODE2							0x01        /**< MODE2 register address */
#define PCA9685_MODE2_INVRT				(1 << 4)    /**< Invert output logic state */
#define PCA9685_MODE2_OCH					(1 << 3)    /**< Outputs change on ACK (1) or STOP (0) */
#define PCA9685_MODE2_OUTDRV			(1 << 2)    /**< Outputs are totem pole (1) or open-drain (0) */
#define PCA9685_MODE2_OUTNE(x)		((x) << 0)  /**< Output configuration when OE not asserted */
#define PCA9685_MODE2_OUTNE_MASK	0x03        /**< Output configuration mask */

#define PCA9685_SUBADR1						0x02        /**< I2C subaddress 1 */
#define PCA9685_SUBADR2						0x03        /**< I2C subaddress 2 */
#define PCA9685_SUBADR3						0x04        /**< I2C subaddress 3 */
#define PCA9685_ALLCALLADR				0x05        /**< I2C all call address */

#define PCA9685_LED0_ON_L					0x06				/**< LED0_ON_L register address */
#define PCA9685_LED0_ON_H					0x07				/**< LED0_ON_H register address */
#define PCA9685_LED0_OFF_L				0x08				/**< LED0_OFF_L register address */
#define PCA9685_LED0_OFF_H				0x09				/**< LED0_OFF_H register address */
#define PCA9685_LED_OFFSET				0x04        /**< LED register offset */

#define PCA9685_ALL_LED_ON_L			0xfa				/**< ALL_LED_ON_L register address */
#define PCA9685_ALL_LED_ON_H			0xfb				/**< ALL_LED_ON_H register address */
#define PCA9685_ALL_LED_OFF_L			0xfc				/**< ALL_LED_OFF_L register address */
#define PCA9685_ALL_LED_OFF_H			0xfd				/**< ALL_LED_OFF_H register address */
#define PCA9685_PRE_SCALE					0xfe				/**< PRE_SCALE register address */

void pca9685_init(void);
void pca9685_set_frequency(uint16_t frequency);
void pca9685_set_pwm(uint8_t index, uint16_t ticks_on, uint16_t ticks_off);
void pca9685_set_pin(uint8_t index, uint16_t val);
void set_OutputEnable_PCA9685(void);

#ifdef __cplusplus
}
#endif
#endif /* PCA9685_H_ */
