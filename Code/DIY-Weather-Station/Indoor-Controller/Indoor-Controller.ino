#pragma region RadioLibraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Module.h>
#pragma endregion
#pragma region LCDLibraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDBacklightController.h>
#pragma endregion
#pragma region DateTimeLibraries
#include <DateTime.h>
#include <DateTimeStrings.h>
#pragma endregion

#define BACKLIGHT_SWITCHER_PIN 0
#define PHOTORESISTOR_PIN 1
#define RADIO_CE 9
#define RADIO_CSN 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
LCDBacklightController lcdBacklightController(&lcd, BACKLIGHT_SWITCHER_PIN, PHOTORESISTOR_PIN);
RF24 rf24(RADIO_CE, RADIO_CSN);
RF24Module radio(&rf24);

void setup()
{
	Serial.begin(9600);

	lcd.begin();
	lcd.backlight();

	radio.setup();
}

void loop()
{
	//lcdBacklightController.CheckBacklightMode();
	/*delay(1000);
	int output = random(150);
	radio.send(&output, sizeof(output));
	radio.startListening();
	int input;
	while (!radio.read(&input, sizeof(input)))
	{

	}
	lcd.clear();
	lcd.print(output);
	lcd.setCursor(0, 1);
	lcd.print(input);
	lcd.setCursor(0, 4);*/
}