
#include <Wire.h>
#include <FaBoAmbientLight_ISL29034.h>

FaBoAmbientLight faboAmbientLight;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("RESET");

  faboAmbientLight.readID();
  faboAmbientLight.setOperation();
  faboAmbientLight.setRange();

}

void loop() {
  Serial.println( faboAmbientLight.readData() );

}
