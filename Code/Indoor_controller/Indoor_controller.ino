#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Module.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RADIO_CE 9
#define RADIO_CSN 10

RF24Module radio(RADIO_CE, RADIO_CSN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();

  radio.setup();
  radio.startListening();
}

void loop()
{
  float data[3];

  if (radio.read(&data, sizeof(data)))
  {
    lcd.clear();
    lcd.print(data[0]);
    lcd.setCursor(0, 1);
    lcd.print(data[1]);
    lcd.setCursor(8, 0);
    lcd.print(data[2]);
  }
}

