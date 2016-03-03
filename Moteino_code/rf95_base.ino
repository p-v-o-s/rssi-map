// rf95_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_client
// Tested with Moteino-LoRa, MoteinoMEGA-LoRa

#include <SPI.h>
#include <RH_RF95.h>

//#define FREQUENCY  434
#define FREQUENCY  915

// Singleton instance of the radio driver
#ifdef __AVR_ATmega1284P__
  #define LED           15 // Moteino MEGAs have LEDs on D15
  #define FLASH_SS      23 // and FLASH SS on D23
#else
  #define LED           9 // Moteinos have LEDs on D9
  #define FLASH_SS      8 // and FLASH SS on D8
#endif

RH_RF95 rf95;


void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  if (!rf95.init()) {
    //Serial.println("init failed");
  }
  else { 
    // Serial.print("init OK - "); 
    //Serial.print(FREQUENCY); Serial.print("mhz"); 
    }
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  rf95.setFrequency(FREQUENCY);

  rf95.setTxPower(23); //high power -- originally 13, range= 5 to 23
}


void loop()
{

  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(LED, HIGH);
//      RH_RF95::printBuffer("request: ", buf, len);
      //Serial.print("got request: ");
      //Serial.println((char*)buf);
      //Serial.print("RSSI: ");
      //Serial.println(rf95.lastRssi(), DEC);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      //uint8_t data[] = "counter";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      //Serial.println("Sent a reply");

      //output to serial for recording
      Serial.print(micros());
      Serial.print(",");
      Serial.println(rf95.lastRssi(), DEC);
      
      digitalWrite(LED, LOW);
    }
    else
    {
     // Serial.println("recv failed");
    }
  }
}
