#define DEBUG

#include "Enums.hpp"

#include "ICommunicator.hpp"
#include "ILedstrip.hpp"
#include "IDistanceSensor.hpp"

#include "SerialCommunicator.hpp"
#include "WS2812Strip.hpp"
#include "UltrasonicDistanceSensor.hpp"

#define STRIP_SIZE 30
#define STRIP_PIN 12

ICommunicator* communicator;
ILedstrip* strip;

IDistanceSensor* sensor;



CRGB Leds[STRIP_SIZE];

void setup() {
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(9600);
  sensor = new UltrasonicDistanceSensor(9, 10);

  FastLED.addLeds<WS2812B, STRIP_PIN, RGB>(Leds, STRIP_SIZE);

  
  strip = new WS2812Strip(Leds,STRIP_SIZE);

  #ifdef DEBUG
  Serial.println("Started");
  #endif
}


States state = UNINITIALIZED;
void loop() {
  // put your main code here, to run repeatedly:
  

  //check what state it should be in


  state = sensor->GetState();


  
  Serial.println(state);
  strip->SetState(state);
}
