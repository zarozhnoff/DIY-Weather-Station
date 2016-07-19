#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RadioCommunication.h>

const uint64_t pipe = 0xF0F1F2F3F4LL;
const uint16_t defaut_timeout = 500;

class RF24Module
{
private:
	RF24* rf24;
	bool isReadingPipeOpened;
	bool isListening;

	void adjustToReading();
	void adjustToSending();

  public:
    RF24Module(RF24* radio);

    void setup();

	RadioResponse send(RadioRequest request, uint16_t timeout);

    bool read(void* data, uint8_t size);
};