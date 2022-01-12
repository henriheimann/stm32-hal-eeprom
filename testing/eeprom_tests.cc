#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "../eeprom.h"
#include "mock_hal.h"
}

TEST_GROUP(stm32_hal_eeprom)
{
	void teardown()
	{
		mock().clear();
	}
};

TEST(stm32_hal_eeprom, test_eeprom_read_bytes_success)
{
	I2C_HandleTypeDef i2c;

	eeprom_handle_t handle = { &i2c, 0x20, 32, 0xff, EEPROM_ADDRESSING_TYPE_16BIT };

	uint8_t buffer[4];

	mock().expectOneCall("HAL_I2C_Mem_Read")
		.withParameter("hi2c", &i2c)
		.withParameter("DevAddress", 0x40)
		.withParameter("MemAddress", 0)
		.withParameter("MemAddSize", 2)
		.withParameter("pData", buffer)
		.withParameter("Size", 4)
		.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
		.andReturnValue(HAL_OK);

	bool result = eeprom_read_bytes(&handle, 0, buffer, sizeof(buffer));

	CHECK_TEXT(result, "Read should be successful");
	mock().checkExpectations();
}

TEST(stm32_hal_eeprom, test_eeprom_write_byte_8bit_1bit_overflow_success)
{
	I2C_HandleTypeDef i2c;

	eeprom_handle_t handle = { &i2c, 0x20, 32, 0x1ff, EEPROM_ADDRESSING_TYPE_8BIT_1BIT_OVERFLOW };

	mock().expectOneCall("HAL_GetTick").andReturnValue(100L);
	mock().expectOneCall("HAL_GetTick").andReturnValue(200L);
	mock().expectOneCall("HAL_I2C_Mem_Write")
			.withParameter("hi2c", &i2c)
			.withParameter("DevAddress", 0x42)
			.withParameter("MemAddress", 0xf0)
			.withParameter("MemAddSize", 1)
			.withParameter("Size", 1)
			.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);
	mock().expectOneCall("HAL_I2C_Master_Transmit")
			.withParameter("hi2c", &i2c)
			.withParameter("DevAddress", 0x40)
			.withParameter("pData", (void*)NULL)
			.withParameter("Size", 0)
			.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
			.andReturnValue(HAL_TIMEOUT);
	mock().expectOneCall("HAL_I2C_Master_Transmit")
			.withParameter("hi2c", &i2c)
			.withParameter("DevAddress", 0x40)
			.withParameter("pData", (void*)NULL)
			.withParameter("Size", 0)
			.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
			.andReturnValue(HAL_OK);

	bool result = eeprom_write_byte(&handle, 0x1f0, 0xa4);

	CHECK_TEXT(result, "Write should be successful");
	mock().checkExpectations();
}

TEST(stm32_hal_eeprom, test_eeprom_write_byte_success)
{
	I2C_HandleTypeDef i2c;

	eeprom_handle_t handle = { &i2c, 0x20, 32, 0xff, EEPROM_ADDRESSING_TYPE_16BIT };

	mock().expectOneCall("HAL_GetTick").andReturnValue(100L);
	mock().expectOneCall("HAL_GetTick").andReturnValue(200L);
	mock().expectOneCall("HAL_I2C_Mem_Write")
		.withParameter("hi2c", &i2c)
		.withParameter("DevAddress", 0x40)
		.withParameter("MemAddress", 0xf0)
		.withParameter("MemAddSize", 2)
		.withParameter("Size", 1)
		.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
		.ignoreOtherParameters()
		.andReturnValue(HAL_OK);
	mock().expectOneCall("HAL_I2C_Master_Transmit")
		.withParameter("hi2c", &i2c)
		.withParameter("DevAddress", 0x40)
		.withParameter("pData", (void*)NULL)
		.withParameter("Size", 0)
		.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
		.andReturnValue(HAL_TIMEOUT);
	mock().expectOneCall("HAL_I2C_Master_Transmit")
		.withParameter("hi2c", &i2c)
		.withParameter("DevAddress", 0x40)
		.withParameter("pData", (void*)NULL)
		.withParameter("Size", 0)
		.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
		.andReturnValue(HAL_OK);

	bool result = eeprom_write_byte(&handle, 0xf0, 0xa4);

	CHECK_TEXT(result, "Write should be successful");
	mock().checkExpectations();
}

TEST(stm32_hal_eeprom, test_eeprom_write_byte_failure_write_timeout)
{
	I2C_HandleTypeDef i2c;

	eeprom_handle_t handle = { &i2c, 0x20, 32, 0xff, EEPROM_ADDRESSING_TYPE_16BIT };

	mock().expectOneCall("HAL_GetTick").andReturnValue(100L);
	mock().expectOneCall("HAL_GetTick").andReturnValue(EEPROM_WRITE_TIMEOUT + 100L);
	mock().expectOneCall("HAL_I2C_Mem_Write")
			.withParameter("hi2c", &i2c)
			.withParameter("DevAddress", 0x40)
			.withParameter("MemAddress", 0xf0)
			.withParameter("MemAddSize", 2)
			.withParameter("Size", 1)
			.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);
	mock().expectOneCall("HAL_I2C_Master_Transmit")
			.withParameter("hi2c", &i2c)
			.withParameter("DevAddress", 0x40)
			.withParameter("pData", (void*)NULL)
			.withParameter("Size", 0)
			.withParameter("Timeout", EEPROM_I2C_TIMEOUT)
			.andReturnValue(HAL_TIMEOUT);

	bool result = eeprom_write_byte(&handle, 0xf0, 0xa4);

	CHECK_FALSE_TEXT(result, "Write should be unsuccessful");
	mock().checkExpectations();
}

TEST(stm32_hal_eeprom, test_eeprom_write_bytes_success)
{
	I2C_HandleTypeDef i2c;

	eeprom_handle_t handle = { &i2c, 0x20, 2, 0xff, EEPROM_ADDRESSING_TYPE_16BIT };

	mock().expectOneCall("HAL_I2C_Mem_Write")
			.withParameter("MemAddress", 0x01)
			.withParameter("Size", 1)
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);
	mock().expectOneCall("HAL_I2C_Mem_Write")
			.withParameter("MemAddress", 0x02)
			.withParameter("Size", 2)
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);
	mock().expectOneCall("HAL_I2C_Mem_Write")
			.withParameter("MemAddress", 0x04)
			.withParameter("Size", 2)
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);

	mock().expectNCalls(3, "HAL_GetTick").andReturnValue(100L);
	mock().expectNCalls(3, "HAL_I2C_Master_Transmit")
			.ignoreOtherParameters()
			.andReturnValue(HAL_OK);

	uint8_t buffer[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

	bool result = eeprom_write_bytes(&handle, 0x01, buffer, sizeof(buffer));

	CHECK_TEXT(result, "Write should be successful");
	mock().checkExpectations();
}