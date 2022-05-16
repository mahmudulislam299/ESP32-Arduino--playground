#include <Wire.h>
#define EN_PIN 5
 
void setup() 
{
  Wire.begin();
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  
}
 
void loop() 
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) 
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.print(address,HEX);
      Serial.print("  |  ");
      Serial.println(address);
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) 
  {
    Serial.println("No I2C devices found\n");
  }
  else 
  {
    Serial.print("no of I2C device is : ");
    Serial.println(nDevices);
    Serial.println("done\n");
  }
  delay(5000);          
}