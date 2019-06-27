#define DEBUG

#include "Enums.hpp"

#include "ICommunicator.hpp"
#include "ILedstrip.hpp"
#include "IDistanceSensor.hpp"

#include "SerialCommunicator.hpp"
#include "WS2812Strip.hpp"
#include "UltrasonicDistanceSensor.hpp"

ICommunicator* communicator;
ILedstrip* strip;

#define STRIP_SIZE 30
#define STRIP_PIN 12

int x = 0;

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

void loop() {
  // put your main code here, to run repeatedly:
  if (state != (States)OUT)
  {
    restlesness = sensor->CalculateRestlesness(state);
  }

  //check what state it should be in
  state = sensor->CalculateRestlesness(restlesness);

  float motor_distance = motor->CalculateHeight(restlesness);
  Serial.println(state);
  strip->SetState(state);

}
