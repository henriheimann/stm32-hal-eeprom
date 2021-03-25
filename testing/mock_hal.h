#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
	HAL_OK       = 0x00,
	HAL_ERROR    = 0x01,
	HAL_BUSY     = 0x02,
	HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

typedef struct
{
	uint8_t mock;
} I2C_HandleTypeDef;

uint32_t HAL_GetTick();

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size,
										  uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                    uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                   uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
