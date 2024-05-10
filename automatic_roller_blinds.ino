#include "DHT.h"
#include <L298N.h>

const unsigned int IN1 = 2;
const unsigned int IN2 = 3;
L298N motor(IN1, IN2);

#define DHTPIN 7     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define LDRPIN 6

int blinds = 0;

int isDay(int ldrval)
{
  if(ldrval == 1)
    return 0;
  else
    return 1;
}
int isHot(float temp)
{
  if(temp>35.0)
    return 1;
  else
    return 0;
}
void close()
{
  if(blinds==0)
  {
    Serial.println("closing");
    motor.forward();
    delay(3000);
    motor.stop();
    blinds = 1;
  }
}
void open()
{
  if(blinds == 1)
  {
    Serial.println("opening");
    motor.backward();
    delay(3000);
    motor.stop();
    blinds = 0;
  }
}

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  delay(3000);
  int ldrval = digitalRead(LDRPIN);
  float t = dht.readTemperature();
  Serial.print("Temperature = ");Serial.println(t);
  Serial.print("Light = ");Serial.println(ldrval);
  
  if(isHot(t))
  {
    close();
  }
  else
  {
    if(isDay(ldrval))
    {
      open();
    }
    else
    {
      close();
    }
  }
}

