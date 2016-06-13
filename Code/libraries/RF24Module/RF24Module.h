#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xF0F1F2F3F4LL;

static RF24 rf24(0, 0);

class RF24Module
{
private:

  public:
    RF24Module(uint8_t ce_pin, uint8_t csn_pin);

    void setup();

    void send(void* data, uint8_t size);

    bool read(void* data, uint8_t size);

    void startListening();

    void startWriting();
};
