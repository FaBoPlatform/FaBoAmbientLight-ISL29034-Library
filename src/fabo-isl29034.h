/**
 * @file  fabo-isl29034.h
 * @brief fabo libtary of ISL29034
 * @author Akira Sasaki
 * @date 2,10, 2016
 */

#include "Arduino.h"
#include "Wire.h"

/** Power Param : Power Down */
#define ISL29034_POWER_DOWN 0b000
/** Power Param : ALS_ONLY */
#define ISL29034_ALS_ONLY 0b001
/** Power Param : ALS_CONTINUOSULY */
#define ISL29034_ALS_CONTINUOSULY 0b101
/** Power Param : IR_CONTINUOSULY */
#define ISL29034_IR_CONTINUOSULY 0b110

/** Lux range : 1000 */
#define ISL29034_LUX_RANGE_1000 0b00
/** Lux range : 4000 */
#define ISL29034_LUX_RANGE_4000 0b01
/** Lux range : 16000 */
#define ISL29034_LUX_RANGE_16000 0b10
/** Lux range : 64000 */
#define ISL29034_LUX_RANGE_64000 0b11

/** Clock : 65535 */
#define ISL29034_CLOCK_65536 0b0000
/** Clock : 4096 */
#define ISL29034_CLOCk_4096 0b0100
/** Clock : 256 */
#define ISL29034_CLOCK_256 0b1000
/** Clock : 16 */
#define ISL29034_CLOCK_16 0b1100

/** Register address : COMMAND_I_REG */
#define ISL29034_COMMAND_I_REG 0x00
/** Register address : COMMAND_II_REG */
#define ISL29034_COMMAND_II_REG 0x01
/** Register address : DATA_REG */
#define ISL29034_DATA_REG 0x02

/**
 * @class isl29034
 * @brief isl29034 control
 */
class isl29034
{
public:
  int readData(void);
  void configuration(void);
  void powerOn(void);
private:
  void writeI2c(byte register_addr, byte value);
  void readI2c(byte register_addr, int num, byte *buf);
};

extern isl29034 faboAmbientLight;
