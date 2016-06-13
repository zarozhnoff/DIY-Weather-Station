#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Module.h>

RF24Module::RF24Module(uint8_t ce_pin, uint8_t csn_pin)
    {
      rf24 = RF24(ce_pin, csn_pin);
    }

    void RF24Module::setup()
    {
      rf24.begin();
      delay(100);
      rf24.setChannel(76);
      rf24.setDataRate(RF24_1MBPS);
      rf24.setPALevel(RF24_PA_HIGH);
    }

    void RF24Module::send(void* data, uint8_t size)
    {
      rf24.startListening();
      rf24.stopListening();
      rf24.write(data, size);
    }

    bool RF24Module::read(void* data, uint8_t size)
    {
      if(!rf24.available())
      {
        return false;
      }

      rf24.read(data, size);

      return true;
    }


    void RF24Module::startListening()
    {
      rf24.openReadingPipe(1, pipe);
      rf24.startListening();
    }

    void RF24Module::startWriting()
    {
      rf24.stopListening();
      rf24.openWritingPipe(pipe);
    }