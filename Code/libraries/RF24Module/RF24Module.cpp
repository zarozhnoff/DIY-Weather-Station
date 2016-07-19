#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Module.h>

RF24Module::RF24Module(RF24* radio)
{
	rf24 = radio;
}

void RF24Module::setup()
{
	rf24->begin();
	delay(100);
	rf24->setChannel(76);
	rf24->setDataRate(RF24_1MBPS);
	rf24->setPALevel(RF24_PA_HIGH);
}

RadioResponse RF24Module::send(RadioRequest request, uint16_t timeout = defaut_timeout)
{
	adjustToSending();

	rf24->startListening();
	rf24->stopListening();

	rf24->write(&request, sizeof(request));
	adjustToReading();

	int startWaitingResponseTime = millis();
	bool isResponseReceived = false;
	while (millis() - startWaitingResponseTime >= timeout)
	{
		if (rf24->available())
		{
			RadioResponse response;
			rf24->read(&response, sizeof(response));

			return response;
		}
	}

	return RadioResponse::CreateUnsuccesfull(Timeout);
}

bool RF24Module::read(void* data, uint8_t size)
{
	if (!rf24->available())
	{
		return false;
	}

	return rf24->read(data, size);
}


void RF24Module::adjustToReading()
{
	if (!isReadingPipeOpened)
	{
		rf24->openReadingPipe(1, pipe);
		isReadingPipeOpened = true;
	}

	if (!isListening)
	{
		rf24->startListening();
		isListening = true;
	}
}

void RF24Module::adjustToSending()
{
	if (isListening)
	{
		rf24->stopListening();
		isListening = false;
	}
	if (isReadingPipeOpened)
	{
		rf24->openWritingPipe(pipe);
		isReadingPipeOpened = false;
	}
}