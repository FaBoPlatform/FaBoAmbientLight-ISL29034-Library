#include "Arduino.h"
#include "Wire.h"

// Param of power
#define ISL29034_POWER_DOWN 0b000
#define ISL29034_ALS_ONLY 0b001
#define ISL29034_ALS_CONTINUOSULY 0b101
#define ISL29034_IR_CONTINUOSULY 0b110

// Lux range
#define ISL29034_LUX_RANGE_1000 0b00
#define ISL29034_LUX_RANGE_4000 0b01
#define ISL29034_LUX_RANGE_16000 0b10
#define ISL29034_LUX_RANGE_64000 0b11

// Clock
#define ISL29034_CLOCK_65536 0b0000
#define ISL29034_CLOCk_4096 0b0100
#define ISL29034_CLOCK_256 0b1000
#define ISL29034_CLOCK_16 0b1100

// Register address
#define ISL29034_COMMAIN_I_REG 0x00
#define ISL29034_COMMAIN_II_REG 0x01
#define ISL29034_DATA_REG 0x02

class isl29034
{
public:
  int readData(void);
  void configuration(void);
  void powerOn(void);
private:
  void readI2c(byte register_addr, int num, byte *buf);
  void writeI2c(byte register_addr, byte value);
};

extern isl29034 faboAmbientLight;
