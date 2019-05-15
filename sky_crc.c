#include "sky_crc.h"

CRC_HandleTypeDef CrcHandle;

CRC_HandleTypeDef *initializeCRC() {
  CRC->CR = CRC_CR_RESET;
  __HAL_RCC_CRC_CLK_ENABLE();
  CrcHandle.Instance = CRC;
  CrcHandle.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  CrcHandle.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  CrcHandle.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_BYTE;
  CrcHandle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_ENABLE;
  CrcHandle.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  HAL_CRC_Init(&CrcHandle);

  return &CrcHandle;
}

void deinitializeCRC() {
  HAL_CRC_DeInit(&CrcHandle);
  __HAL_RCC_CRC_CLK_DISABLE();
}

uint32_t calculateCRC(uint8_t *data, uint32_t size) { return ~HAL_CRC_Calculate(&CrcHandle, (uint32_t *)data, size); }
