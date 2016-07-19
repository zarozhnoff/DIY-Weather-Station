#include <SPI.h>
#include <nRF24L01.h>
#include <RF24/RF24.h>
#include <RF24Module/RF24Module.h>

#define RADIO_CE 9
#define RADIO_CSN 7

RF24 rf24(RADIO_CE, RADIO_CSN);
RF24Module radio(&rf24);

void setup()
{
	radio.setup();
}

void loop()
{
	radio.startListening();

	int input;
	while (!radio.read(&input, sizeof(input)))
	{

	}
	radio.startWriting();
	int output = pow(input, 2);
	radio.send(&output, sizeof(output));
}