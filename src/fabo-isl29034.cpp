#include "fabo-isl29034.h"

void isl29034::powerOn()
{
  writeI2c(ISL29034_COMMAIN_I_REG, ISL29034_ALS_CONTINUOSULY);  
}

void isl29034::configuration()
{
  writeI2c(ISL29034_COMMAIN_II_REG, ISL29034_LUX_RANGE_64000|ISL29034_CLOCK_65536);  
}

uint16_t isl29034::readData()
{
  uint16_t ambient;
  uint8_t buffer[2];

  readI2c(ISL29034_DATA_REG, 2, buffer);
  ambient = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return ambient;
}

// I2Cへの書き込み
void isl29034::writeI2c(byte register_addr, byte value) {
  Wire.beginTransmission(HTS221_SLAVE_ADDRESS);  
  Wire.write(register_addr);         
  Wire.write(value);                 
  Wire.endTransmission();        
}

// I2Cへの読み込み
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

