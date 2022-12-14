/**
 ********************************************************************************
 * @file    :LPS25HB.c
 * @author  :Vytautas Daunoras
 * @date    :2022-10-20
 ********************************************************************************
 */

#include "main.h"
#include "LPS25HB.h"

uint8_t chipID;
uint8_t datatowrite = 0;
int16_t val;
uint8_t Temp_RAW[2];

uint8_t LPS25HB_Initialise(I2C_HandleTypeDef * i2cHandle) {

  // Pradzioje patikriname ID
  HAL_I2C_Mem_Read(i2cHandle, LPS25HB_ADDRESS, LPS25HB_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, & chipID, 1, 100);

  if (chipID != LPS25HB_DEVICE_ID) {
    return 1; //jei ID nesutampa inicializacija nutraukiama
  } 

  datatowrite = (0x01 << 7); //power on PD
  if (HAL_I2C_Mem_Write(i2cHandle, LPS25HB_ADDRESS, LPS25HB_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, & datatowrite, 1, 100) != HAL_OK) {
    return 1;
  }
  return 0;
}
float LPS25HB_Measure_Temperature(I2C_HandleTypeDef * i2cHandle) {

  datatowrite = (0x01 << 0); // One shot mode
  if (HAL_I2C_Mem_Write(i2cHandle, LPS25HB_ADDRESS, LPS25HB_CTRL_REG2, I2C_MEMADD_SIZE_8BIT, & datatowrite, 1, 100) != HAL_OK) {
    return 1;
  }

  HAL_I2C_Mem_Read_IT(i2cHandle, LPS25HB_ADDRESS, LPS25HB_TEMP_OUT_L | 0x80, I2C_MEMADD_SIZE_8BIT, Temp_RAW, 2);

  val = (Temp_RAW[1] << 8) | (Temp_RAW[0]);
  return 42.5f + val / 480.0f;
}
