#include "Enums.hpp"

#include "ICommunicator.hpp"
#include "ILedstrip.hpp"

#include "SerialCommunicator.hpp"
#include "WS2812Strip.hpp"

ICommunicator* communicator;
ILedstrip* strip;

#define STRIP_SIZE 30
#define STRIP_PIN 12

CRGB Leds[STRIP_SIZE];

void setup() {
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(115200);
  FastLED.addLeds<WS2812B, STRIP_PIN, RGB>(Leds, STRIP_SIZE);
  strip = new WS2812Strip(Leds,STRIP_SIZE);
}

void loop() {
  // put your main code here, to run repeatedly:
  States state = communicator->GetState();
  strip->SetState(state);
}
