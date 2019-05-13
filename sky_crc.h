#ifndef _SKY_CRC_H
#define _SKY_CRC_H

#if defined(TEST_BUILD)
#include "sky_crc_mock.h"
#else
#include "stm32l4xx_hal.h"
#endif
#include <stdbool.h>

CRC_HandleTypeDef *initializeCRC();
void deinitializeCRC();

uint32_t calculateCRC(uint8_t *data, uint32_t size);

#endif
