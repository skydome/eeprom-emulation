#include "eeprom.h"
#include "sky_led.h"
#include "eeprom_emul.h"


uint32_t getFW1Version(){
 return readFromEEPROM(FW1_VERSION_INDEX);
}

uint32_t getFW1Health(){
 return readFromEEPROM(FW1_HEALTH_INDEX);
}

uint32_t getFW2Version(){
  return readFromEEPROM(FW2_VERSION_INDEX);
}

uint32_t getFW2Health(){
  return readFromEEPROM(FW2_HEALTH_INDEX);
}

uint32_t getCurrentFWAddress(){
  return readFromEEPROM(FW_CURRENT_ADDRESS_INDEX);
}

void setFW1Version(uint32_t version){
  writeToEEPROM(FW1_VERSION_INDEX, version);
}

void setFW2Version(uint32_t version){
  writeToEEPROM(FW2_VERSION_INDEX, version);
}

void setFW1Health(uint32_t status){
  writeToEEPROM(FW1_HEALTH_INDEX, status);
}

void setFW2Health(uint32_t status){
  writeToEEPROM(FW2_HEALTH_INDEX, status);
}

void setCurrentFWAddress(uint32_t newAddress){
  writeToEEPROM(FW_CURRENT_ADDRESS_INDEX, newAddress);
}

uint16_t VirtualEEPROM[NB_OF_VARIABLES];
__IO uint32_t ErasingOnGoing = 0;
EE_Status ee_status = EE_OK;

void initializeEEPROM(){
  for (uint16_t varValue = 0; varValue < NB_OF_VARIABLES; varValue++){
    VirtualEEPROM[varValue] = 10*varValue + 1;
  }
  ee_status = EE_Init(VirtualEEPROM, EE_CONDITIONAL_ERASE);
}

uint32_t readFromEEPROM(uint16_t virtualAddress){
  uint32_t data;
  EE_ReadVariable32bits(VirtualEEPROM[virtualAddress], &data);
  return data;
}

void Error_Handler(){
  while( 1 ){
    SKY_LED_TOGGLE(SKY_LED1);
    HAL_Delay(2000);
  }
}

void writeToEEPROM(uint16_t virtualAddress, uint32_t data){
  HAL_FLASH_Unlock();
  __HAL_RCC_PWR_CLK_ENABLE();
  ee_status = EE_Init(VirtualEEPROM, EE_CONDITIONAL_ERASE);

  while (ErasingOnGoing == 1) { }

  if(ee_status != EE_OK) {
    Error_Handler();
  }
  ee_status = EE_WriteVariable32bits(VirtualEEPROM[virtualAddress], data);

  if ((ee_status & EE_STATUSMASK_CLEANUP) == EE_STATUSMASK_CLEANUP) {
    ErasingOnGoing = 1;
    ee_status|= EE_CleanUp_IT();
  }

  if ((ee_status & EE_STATUSMASK_ERROR) == EE_STATUSMASK_ERROR) {
    Error_Handler();
  }

  HAL_FLASH_Lock();
}

