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
  Wire.begin();
}

void FaBoAmbientLight::readID() {
  uint8_t data;
  readI2c(ISL29034_REG_ID, 1, &data);
  Serial.println(data,HEX);
  Serial.println(data&ISL29034_ID_MASK,HEX);
}

void FaBoAmbientLight::setOperation() {
  writeI2c(ISL29034_REG_CMD1, ISL29034_OP_ALSCONT);
}

void FaBoAmbientLight::setRange() {
  uint8_t data;
  readI2c(ISL29034_REG_CMD2, 1, &data);
  data &= 0xFC; // 11111100
  data |= ISL29034_FS_3;
  writeI2c(ISL29034_REG_CMD2, data );
}

void FaBoAmbientLight::setResolution() {
  writeI2c(ISL29034_REG_CMD2, ISL29034_FS_3|ISL29034_RES_4 );
}

uint16_t FaBoAmbientLight::readData() {
  uint16_t ambient;
  uint8_t buffer[2];

  

  readI2c(ISL29034_REG_DATA_L, 2, buffer);
  ambient = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return ambient;
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
