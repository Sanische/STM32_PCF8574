#include "PCF8574.h"

PCF8574::PCF8574()
{
}

HAL_StatusTypeDef PCF8574::begin(I2C_HandleTypeDef *hi2c, uint8_t address) {

	/* Store the I2C address and init the Wire library */
	_hi2c = hi2c;
	_address = (uint16_t)(address<<1);


	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(_hi2c, _address, 2, 2);
	return result;
}

HAL_StatusTypeDef PCF8574::PCF8574_ReadDataByte (uint8_t val)
{
	HAL_StatusTypeDef status;
	status=HAL_I2C_Master_Receive(_hi2c, _address, &val, 1, 10);
	return status;
}

HAL_StatusTypeDef PCF8574::PCF8574_WriteDataByte (uint8_t val)
{

	HAL_StatusTypeDef status;
	status=HAL_I2C_Master_Transmit(_hi2c, _address, &val, 1, 10);
	_PORT=val;
	return status;
}

void PCF8574::PCF8574_digitalWrite (uint8_t pin, bool state)
{
	/* Set PORT bit value */
	if(pin>=0&&pin<8)
	{
	if(state)
	{
		_PORT|=(uint8_t)(1<<pin);
	}
	else
	{
		_PORT&=(uint8_t)~((uint8_t)(1<<pin));
	}
	/* Update GPIO values */
	PCF8574_WriteDataByte (_PORT);
	}
}

void PCF8574::PCF8574_toggle(uint8_t pin) {

	/* Toggle pin state */
	_PORT ^= (1 << pin);
	/* Update GPIO values */
	PCF8574_WriteDataByte (_PORT);
}

bool PCF8574::PCF8574_digitalRead (uint8_t pin)
{
	/* Update GPIO values */
	PCF8574_ReadDataByte (_PIN);
	return (_PIN & (1 << pin)) ? 1 : 0;
}

void PCF8574::clear() {

	/* User friendly wrapper for write() */
	PCF8574_WriteDataByte (0x00);
}

void PCF8574::set() {

	/* User friendly wrapper for write() */
	write(0xFF);
}
