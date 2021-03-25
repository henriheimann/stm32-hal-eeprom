#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "mock_hal.h"
}

uint32_t HAL_GetTick()
{
	return mock().actualCall(__FUNCTION__).returnUnsignedLongIntValue();
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size,
                                          uint32_t Timeout)
{
	return (HAL_StatusTypeDef)mock().actualCall(__FUNCTION__)
			.withParameter("hi2c", hi2c)
			.withParameter("DevAddress", DevAddress)
			.withParameter("pData", pData)
			.withParameter("Size", Size)
			.withParameter("Timeout", Timeout)
			.returnIntValue();
}

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                    uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return (HAL_StatusTypeDef)mock().actualCall(__FUNCTION__)
			.withParameter("hi2c", hi2c)
			.withParameter("DevAddress", DevAddress)
			.withParameter("MemAddress", MemAddress)
			.withParameter("MemAddSize", MemAddSize)
			.withParameter("pData", pData)
			.withParameter("Size", Size)
			.withParameter("Timeout", Timeout)
			.returnIntValue();
}

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                   uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return (HAL_StatusTypeDef)mock().actualCall(__FUNCTION__)
			.withParameter("hi2c", hi2c)
			.withParameter("DevAddress", DevAddress)
			.withParameter("MemAddress", MemAddress)
			.withParameter("MemAddSize", MemAddSize)
			.withParameter("pData", pData)
			.withParameter("Size", Size)
			.withParameter("Timeout", Timeout)
			.returnIntValue();
}