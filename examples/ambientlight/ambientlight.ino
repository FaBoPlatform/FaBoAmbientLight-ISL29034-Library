//
// FaBo AmbientLight Brick
//
// brick_i2c_ambientlight
//

#include <Wire.h>
#include "fabo-isl29034.h"

void setup()
{
  Serial.begin(115200);
   
  faboAmbientLight.configuration();
  faboAmbientLight.powerOn();
}

void loop()
{ 
  double ambient = faboAmbientLight.readData();

  Serial.print("Ambient:");
  Serial.println(ambient);
  delay(1000);
}
