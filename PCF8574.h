/**
 * This class is designed to allow user to use PCF8574 gpio expander like any standard arduino pins.\n
 */
#ifndef PCF8574_H
#define PCF8574_H
#endif
/* C++ detection */
#ifdef __cplusplus
extern "C" {


#include "stm32f4xx_hal.h"

class PCF8574
{
	public:
	/*Create a new PCF8574 instance*/
	PCF8574();
	/*Check the I2C connection and store the PCF8574 chip address*/
	HAL_StatusTypeDef begin(I2C_HandleTypeDef *hi2c, uint8_t address);
	//
	/**
		 * Set the state of a pin (HIGH or LOW)
		 *
		 * @param pin The pin to set
		 * @param value The new state of the pin
		 */
	void PCF8574_digitalWrite (uint8_t pin, bool state);
	/**
		 * Read the state of a pin
		 *
		 * @param pin The pin to read back
		 * @return
		 */
	bool PCF8574_digitalRead (uint8_t pin);
	/**
		 * Toggle the state of a pin
		 */
	void PCF8574_toggle(uint8_t pin);
	/**
		 * Exactly like write(0x00), set all pins to LOW
		 */
	void PCF8574_clear();
	/**
		 * Exactly like write(0xFF), set all pins to HIGH
		 */
	void PCF8574_set();

	private:
	HAL_StatusTypeDef PCF8574_ReadDataByte (uint8_t val);
	HAL_StatusTypeDef PCF8574_WriteDataByte (uint8_t val);
	I2C_HandleTypeDef * _hi2c;  // I2C handle
	uint8_t _address; //I2C address
	uint8_t _PORT;
	uint8_t _PIN;
};
/* C++ detection */
#ifdef __cplusplus
}

#endif
#endif
