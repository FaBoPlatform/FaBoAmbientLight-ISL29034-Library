/**
 @file FaBoAmbientLight_ISL29034.cpp
 @brief This is a library for the FaBo Ambient Light I2C Brick.

   http://fabo.io/217.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include "FaBoAmbientLight_ISL29034.h"

FaBoAmbientLight::FaBoAmbientLight(uint8_t addr) {
  _i2caddr = addr;
  _range = ISL29034_FS_0;
  _resolution = ISL29034_RES_16;
  Wire.begin();
}

void FaBoAmbientLight::begin() {
  setOperation(ISL29034_OP_ALS_CONT);
  setRange(ISL29034_FS_3);
  setResolution(ISL29034_RES_16);
}

void FaBoAmbientLight::readID() {
  uint8_t data;
  readI2c(ISL29034_REG_ID, 1, &data);
  Serial.println(data,HEX);
  Serial.println(data&ISL29034_ID_MASK,HEX);
}

void FaBoAmbientLight::setOperation(uint8_t config) {
  writeI2c(ISL29034_REG_CMD1, config);
}

void FaBoAmbientLight::setRange(uint8_t config) {
  uint8_t data;
  _range = config;
  readI2c(ISL29034_REG_CMD2, 1, &data);
  data &= 0xFC; // 11111100
  data |= config;
  writeI2c(ISL29034_REG_CMD2, data );
}

void FaBoAmbientLight::setResolution(uint8_t config) {
  uint8_t data;
  _resolution = config;
  readI2c(ISL29034_REG_CMD2, 1, &data);
  data &= 0xF3; // 11110011
  data |= config;
  writeI2c(ISL29034_REG_CMD2, data );
}

uint16_t FaBoAmbientLight::readADC() {
  uint16_t adc;
  uint8_t data[2];

  switch (_resolution) {
    case ISL29034_RES_16:
      delay(90);
      break;
    case ISL29034_RES_12:
      delay(6);
      break;
    case ISL29034_RES_8:
      delayMicroseconds(352);
      break;
    case ISL29034_RES_4:
      delayMicroseconds(22);
      break;
  }

  readI2c(ISL29034_REG_DATA_L, 2, data);
  adc = (((uint16_t)data[1])<<8) | (uint16_t)data[0];
  return adc;
}

float FaBoAmbientLight::readLux() {
  uint16_t adc,range,count;
  adc = readADC();

  switch (_range) {
    case ISL29034_FS_0:
      range = 1000;
      break;
    case ISL29034_FS_1:
      range = 4000;
      break;
    case ISL29034_FS_2:
      range = 16000;
      break;
    case ISL29034_FS_3:
      range = 64000;
      break;
  }

  switch (_resolution) {
    case ISL29034_RES_16:
      count = 65535;
      break;
    case ISL29034_RES_12:
      count = 4095;
      break;
    case ISL29034_RES_8:
      count = 255;
      break;
    case ISL29034_RES_4:
      count = 15;
      break;
  }

  return ((float)range / (float)count) * (float)adc;
}






void FaBoAmbientLight::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

void FaBoAmbientLight::readI2c(uint8_t address, uint8_t num, uint8_t * data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  uint8_t i = 0;
  Wire.requestFrom(_i2caddr, num);
  while( Wire.available() ) {
    data[i++] = Wire.read();
  }
}
