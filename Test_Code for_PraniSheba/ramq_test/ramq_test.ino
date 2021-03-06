
#include "ramQ.h"
#include "Serial.h"

#define TOTAL_BUFFER  4
typedef struct 
{
  int volt;
  int current;
}sensor_t;

sensor_t sensor[TOTAL_BUFFER];

void setup()
{
  Serial.begin(9600);
  SerialBegin(9600);
  ramQSet(&sensor, sizeof(sensor_t), TOTAL_BUFFER);
  Serial.println(sizeof(sensor_t));
  Serial.println(F("Setup done"));

}

void loop()
{
  int num = 0;
  if (Serial.available())
  {
    num = Serial.parseInt();
    if (num == 1)
    {
      Serial.println(F("|----------------------------------------------|"));
      getData((sensor_t*)ramQHead());
      ramQUpdateHead();
    }

    if (num == 2)
    {
      sensor_t *readPtr = (sensor_t*)ramQRead();
      if (readPtr != NULL)
      {
        
        Serial.println(F("<-----Read Data---->"));
        printSensor(readPtr);
        ramQUpdateTail();
      }
    }
  }

      
//  if (_ramQFlash != NULL)
//  {
//    Serial.println(F("<======Flash Pointer Test========>"));
//    sensor_t *sen = (sensor_t*)_ramQFlash;
//    uint8_t fCount = 0;
//    do
//    {
//      printSensor(sen);
//      sen++;
//      fCount++;
//    } while (fCount < TOTAL_BUFFER / 2);
//    _ramQFlash = NULL;
//  }


}

sensor_t *getData(sensor_t *sensor)
{
  sensor -> volt = random(1, 10);
  sensor -> current = random(11, 20);
  Serial.println(F("Generated data"));
  Serial.print(F("Current :")); Serial.print(sensor -> volt);
  Serial.print(F(" | Volt :")); Serial.println(sensor -> current);
  return sensor;

}

void printSensor(sensor_t *sensor)
{
  Serial.print(F("Current :")); Serial.print(sensor -> volt);
  Serial.print(F(" | Volt :")); Serial.println(sensor -> current);
}
