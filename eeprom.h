#ifndef EEPROM_H
#define EEPROM_H

#include <inttypes.h>
#include "eeprom_emul.h"

void initializeEEPROM();
EE_Status writeToEEPROM(uint16_t virtualAddress, uint32_t data);
uint32_t readFromEEPROM(uint16_t virtualAddress);

uint32_t getFW1Version();
uint32_t getFW1Health();
uint32_t getFW2Version();
uint32_t getFW2Health();
uint32_t getCurrentFWAddress();
void setFW1Version(uint32_t version);
void setFW2Version(uint32_t version);
void setFW1Health(uint32_t status);
void setFW2Health(uint32_t status);
void setCurrentFWAddress(uint32_t newAddress);

#define FW1_VERSION_INDEX  0
#define FW1_HEALTH_INDEX  1
#define FW2_VERSION_INDEX  2
#define FW2_HEALTH_INDEX  3
#define FW_CURRENT_ADDRESS_INDEX  4
#define FW_HEALTHY 0
#define FW_BROKEN 1

#endif
