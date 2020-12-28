#include "eeprom.h"

#include <stdio.h>
#include <assert.h>

static bool eeprom_wait_for_write_completion(eeprom_handle_t *handle)
{
	uint32_t tick_start = HAL_GetTick();

	while (HAL_I2C_Master_Transmit(handle->i2c_handle, (handle->device_address << 1u), NULL, 0, EEPROM_I2C_TIMEOUT) != HAL_OK) {
		if ((HAL_GetTick() - tick_start) >= EEPROM_WRITE_TIMEOUT) {
			return false;
		}
	}

	return true;
}

bool eeprom_write_byte(eeprom_handle_t *handle, uint16_t address, uint8_t value)
{
	assert(address <= handle->max_address);

	if (HAL_I2C_Mem_Write(handle->i2c_handle, (handle->device_address << 1u), address, 2, &value, 1, EEPROM_I2C_TIMEOUT) != HAL_OK) {
		return false;
	}

	return eeprom_wait_for_write_completion(handle);
}

bool eeprom_write_bytes(eeprom_handle_t *handle, uint16_t address, uint8_t *source, size_t count)
{
	assert(address + count <= handle->max_address);

	uint16_t current_address = address;
	uint8_t *source_ptr = source;

	while (count > 0) {

		uint16_t next_page_address = ((current_address / handle->page_size) + 1) * handle->page_size;
		uint16_t max_bytes_writable = next_page_address - current_address;
		uint16_t bytes_to_write = count < max_bytes_writable ? count : max_bytes_writable;

		if (HAL_I2C_Mem_Write(handle->i2c_handle, (handle->device_address << 1u), current_address, 2, source_ptr, bytes_to_write,
						EEPROM_I2C_TIMEOUT) != HAL_OK) {
			return false;
		}

		if (!eeprom_wait_for_write_completion(handle)) {
			return false;
		}

		current_address += bytes_to_write;
		source_ptr += bytes_to_write;
		count -= bytes_to_write;
	}

	return true;
}

bool eeprom_read_bytes(eeprom_handle_t *handle, uint16_t address, uint8_t *dest, size_t count)
{
	assert(address + count <= handle->max_address);
	return HAL_I2C_Mem_Read(handle->i2c_handle, (handle->device_address << 1u), address, 2, dest, count, EEPROM_I2C_TIMEOUT) == HAL_OK;
}
