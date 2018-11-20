#include "i2c.h"
#include "pca9685.h"
#include "main.h"
#include "gpio.h"

static uint8_t i2c_read_reg8(uint8_t address, uint8_t reg)
{
	uint8_t val;

	i2c_master_read(address, reg, 1, &val, 1);

	return val;
}

static void i2c_write_reg8(uint8_t address, uint8_t reg, uint8_t val)
{
	uint8_t tx_data[2];
	tx_data[0] = reg;
	tx_data[1] = val;

	i2c_master_write(address, tx_data, 2);
}

static void i2c_write_reg8_multiple(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len)
{
	uint8_t tx_data[5];
	//uint8_t tx_data[len + 1];
	tx_data[0] = reg;

	for (int i = 0; i < len; i++)
		tx_data[i + 1] = data[i];

	i2c_master_write(address, tx_data, len + 1);
}

/**
 * @brief      Initializes the PCA9685 chip.
 *
 * Initializes the PCA9685 controller and sets all output pins low.
 */
void pca9685_init(void)
{
	int i;

// set output enable
set_OutputEnable_PCA9685();


	/* Enable register auto-increment */
	i2c_write_reg8(PCA9685_I2C_ADDR, PCA9685_MODE1, 0x20);
	/* Outputs configured with a totem pole structure, low when disabled */
	i2c_write_reg8(PCA9685_I2C_ADDR, PCA9685_MODE2, 0x10);
	// INVRT = 0, OUTDRV = 1, OUTNE = 01 (MODE2 register bits)


	/* Turn all pins off */
	for (i = 0; i < 16; i++)
			pca9685_set_pin(i, 0);
}

/**
 * @brief      Sets the output PWM frequency.
 *
 * @param[in]  frequency  The requested output frequency.
 */
void pca9685_set_frequency(uint16_t frequency)
{
	uint32_t prescaler;
	uint8_t mode1;

	/* clamp requested frequency to valid range */
	if (frequency < 24)
		frequency = 24;
	if (frequency > 1526)
		frequency = 1526;

	/*
	 * calculate prescaler according to PCA9685 datasheet:
	 * prescaler = (osc_clock / (4096 * pwm_freq)) - 1
	 */
	prescaler = (uint32_t)(((PCA9685_INT_OSC_CLK >> 12) / (double)frequency) + 0.5);
	prescaler--;

	/* clamp prescaler to valid range */
	if (prescaler < 0x03)
		prescaler = 0x03;
	if (prescaler > 0xff)
		prescaler = 0xff;

	/* Enter sleep mode before setting prescaler */
	mode1 = i2c_read_reg8(PCA9685_I2C_ADDR, PCA9685_MODE1);
	i2c_write_reg8(PCA9685_I2C_ADDR, PCA9685_MODE1, mode1 | PCA9685_MODE1_SLEEP);
	i2c_write_reg8(PCA9685_I2C_ADDR, PCA9685_PRE_SCALE, prescaler & 0xff);
	i2c_write_reg8(PCA9685_I2C_ADDR, PCA9685_MODE1, mode1);
}

/**
 * @brief      Sets the duration for which an output pin should be on or off.
 *
 * @param[in]  index      The output pin to set.
 * @param[in]  ticks_on   The number of ticks for which the pin should be high.
 * @param[in]  ticks_off  The number of ticks for which the pin should be low.
 *
 * Sets the number of ticks for which a given output should be on and off. This
 * function is not recommended for setting a simple duty cycle - use
 * @a pca9685_set_pin instead.
 */
void pca9685_set_pwm(uint8_t index, uint16_t ticks_on, uint16_t ticks_off)
{
	uint8_t data[4];

	data[0] = ticks_on & 0xff;
	data[1] = ticks_on >> 8;
	data[2] = ticks_off & 0xff;
	data[3] = ticks_off >> 8;

	i2c_write_reg8_multiple(PCA9685_I2C_ADDR, PCA9685_LED0_ON_L + index * PCA9685_LED_OFFSET, data, 4);
}

/**
 * @brief      Sets an output pin to a duty cycle.
 *
 * @param[in]  index  The output pin to set.
 * @param[in]  val    The duty cycle to set, from 0 to 4095.
 */
void pca9685_set_pin(uint8_t index, uint16_t val)
{
	/* Clamp requested value to valid range */
	if (val > 4095)
		val = 4095;

	if (val == 4095)
		pca9685_set_pwm(index, 4096, 0); /* special value for 100% DC */
	else if (val == 0)
		pca9685_set_pwm(index, 0, 4096);
	else
		pca9685_set_pwm(index, 0, val);
}
