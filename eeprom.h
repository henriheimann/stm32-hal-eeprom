#pragma once

#if (defined STM32L011xx) || (defined STM32L021xx) || \
	(defined STM32L031xx) || (defined STM32L041xx) || \
	(defined STM32L051xx) || (defined STM32L052xx) || (defined STM32L053xx) || \
	(defined STM32L061xx) || (defined STM32L062xx) || (defined STM32L063xx) || \
	(defined STM32L071xx) || (defined STM32L072xx) || (defined STM32L073xx) || \
	(defined STM32L081xx) || (defined STM32L082xx) || (defined STM32L083xx)
#include "stm32l0xx_hal.h"
#elif defined (STM32L412xx) || defined (STM32L422xx) || \
	defined (STM32L431xx) || (defined STM32L432xx) || defined (STM32L433xx) || defined (STM32L442xx) || defined (STM32L443xx) || \
	defined (STM32L451xx) || defined (STM32L452xx) || defined (STM32L462xx) || \
	defined (STM32L471xx) || defined (STM32L475xx) || defined (STM32L476xx) || defined (STM32L485xx) || defined (STM32L486xx) || \
    defined (STM32L496xx) || defined (STM32L4A6xx) || \
    defined (STM32L4R5xx) || defined (STM32L4R7xx) || defined (STM32L4R9xx) || defined (STM32L4S5xx) || defined (STM32L4S7xx) || defined (STM32L4S9xx)
#include "stm32l4xx_hal.h"
#else
#error Platform not implemented
#endif

#include <stdbool.h>
#include <stdint.h>

#define EEPROM_24LC32A_ADDRESS 0x50
#define EEPROM_24LC32A_MAX_ADDRESS 0x7FFF
#define EEPROM_24LC32A_PAGE_SIZE 32

/**
 * The timeout used in all I2C transmits.
 */
#ifndef EEPROM_I2C_TIMEOUT
#define EEPROM_I2C_TIMEOUT 100
#endif

/**
 * The timeout for EEPROM write cycle completion
 */
#ifndef EEPROM_WRITE_TIMEOUT
#define EEPROM_WRITE_TIMEOUT 1000
#endif

/**
 * Handle defining a connected EEPROM.
 */
typedef struct {

	/**
	 * The handle to the I2C bus used.
	 */
	I2C_HandleTypeDef *i2c_handle;

	/**
	 * The device address of the EEPROM.
	 */
	uint8_t device_address;

	/**
	 * The page size of this EEPROM.
	 */
	uint16_t page_size;

	/**
	 * The maximum address of this EEPROM.
	 */
	uint16_t max_address;

} eeprom_handle_t;

/**
 * Writes a value to the given address on the EEPROM.
 * @param handle The handle to the EEPROM.
 * @param address The address to write to.
 * @param value The byte to write.
 * @return True on success, false otherwise.
 */
bool eeprom_write_byte(eeprom_handle_t *handle, uint16_t address, uint8_t value);

/**
 * Writes the bytes to the given address on the EEPROM pagewise.
 * @param handle The handle to the EEPROM.
 * @param address The address to write to.
 * @param source Pointer to the bytes to write.
 * @param count The number of bytes to write.
 * @return True on success, false otherwise.
 */
bool eeprom_write_bytes(eeprom_handle_t *handle, uint16_t address, uint8_t *source, size_t count);

/**
 * Reads the bytes starting at the given address from the EEPROM.
 * @param handle The handle to the EEPROM.
 * @param address The address to read from.
 * @param dest The buffer to write into.
 * @param count The number of bytes to read.
 * @return True on success, false otherwise.
 */
bool eeprom_read_bytes(eeprom_handle_t *handle, uint16_t address, uint8_t *dest, size_t count);
