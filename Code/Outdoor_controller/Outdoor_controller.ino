#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Module.h>

#include <OneWire.h>
#include <DallasTemperature.h>


#define THERMOMETER_PIN 8
#define LIGHT_PIN 0
#define RAIN_PIN 1
#define RADIO_CE 9
#define RADIO_CSN 10

RF24Module radio(RADIO_CE, RADIO_CSN);

OneWire oneWire(THERMOMETER_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  radio.setup();
  radio.startWriting();
}

void loop()
{
  float data[3];
  sensors.requestTemperatures();
  data[0] = sensors.getTempCByIndex(0);
  data[1] = (float)analogRead(LIGHT_PIN);
  data[2] = (float)analogRead(RAIN_PIN);

  radio.send(&data, sizeof(data));
}


