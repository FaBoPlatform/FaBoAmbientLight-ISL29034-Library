/**
 * @file  fabo-isl29034.cpp
 * @brief fabo libtary of ISL29034
 * @author Akira Sasaki
 * @date 2,10, 2016
 */

#include "fabo-isl29034.h"

/**
 * @brief Read Sensor Data
 * @return uint16_t : Read Data
 */
uint16_t isl29034::readData()
{
  uint16_t ambient;
  uint8_t buffer[2];

  readI2c(ISL29034_DATA_REG, 2, buffer);
  ambient = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return ambient;
}

/**
 * @brief Set Config
 */
void isl29034::configuration()
{
  writeI2c(ISL29034_COMMAND_II_REG, ISL29034_LUX_RANGE_64000|ISL29034_CLOCK_65536);
}

/**
 * @brief Power ON
 */
void isl29034::powerOn()
{
  writeI2c(ISL29034_COMMAND_I_REG, ISL29034_ALS_CONTINUOSULY);
}

/**
 * @brief Write I2C Data
 * @param [in] register_addr : Write Register Address
 * @param [in] value  : Write Data
 */
void isl29034::writeI2c(byte register_addr, byte value) {
  Wire.beginTransmission(HTS221_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.write(value);
  Wire.endTransmission();
}

/**
 * @brief Read I2C Data
 * @param [in] register_addr : register address
 * @param [in] num   : Data Length
 * @param [out] *buf : Read Data
 */
void isl29034::readI2c(byte register_addr, int num, byte *buf) {
  Wire.beginTransmission(HTS221_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.endTransmission(false);

  //Wire.beginTransmission(DEVICE_ADDR);
  Wire.requestFrom(HTS221_SLAVE_ADDRESS, num);

  int i = 0;
  while (Wire.available())
  {
    buf[i] = Wire.read();
    i++;
  }
  //Wire.endTransmission();
}

isl29034 faboAmbientLight;
