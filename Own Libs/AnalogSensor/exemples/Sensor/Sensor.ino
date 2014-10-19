#include <AnalogSensor.h>

AnalogSensor sensor = AnalogSensor(0,1.27,0,6,13,12);

void setup()
{
  Serial.begin(19200);
  sensor.enableSensor(true);
}

void loop()
{
  sensor.readSensor();
  Serial.println(sensor.value);
  delay(50);
}

