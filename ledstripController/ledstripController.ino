#define DEBUG

#include "Enums.hpp"

#include "ILedstrip.hpp"
#include "WS2812Strip.hpp"
#include "PulseAnimator.hpp"
#include "PotAnimator.hpp"

#define STRIP_SIZE 30
#define STRIP_PIN 12

const int pulseLedsSize = 60;
const int pulseLedsPin = 10;
const int potLeds1Size = 30;
const int potLeds1Pin = 8;
const int potLeds2Size = 30;
const int potLeds2Pin = 9;

CRGB pulseLeds[pulseLedsSize];
CRGB potLeds1[potLeds1Size];
CRGB potLeds2[potLeds2Size];

PulseAnimator* pulseAnimator;
PotAnimator* potAnimator;
PotAnimator* potAnimator2;

void setup() {
  FastLED.addLeds<WS2812B, pulseLedsPin, RGB>(pulseLeds, pulseLedsSize);
  FastLED.addLeds<WS2812B, potLeds1Pin, RGB>(potLeds1, potLeds1Size);
  FastLED.addLeds<WS2812B, potLeds2Pin, RGB>(potLeds2, potLeds2Size);

  ILedstrip* pulseStrip;
  ILedstrip* potStrip1;
  ILedstrip* potStrip2;

  pulseStrip = new WS2812Strip(pulseLeds, pulseLedsSize, 255);
  potStrip1 = new WS2812Strip(potLeds1, potLeds1Pin, 255);
  potStrip2 = new WS2812Strip(potLeds2, potLeds2Pin, 255);

  pulseAnimator = new PulseAnimator(pulseStrip);
  potAnimator = new PotAnimator(potStrip1);
  potAnimator2 = new PotAnimator(potStrip2);

  Serial.begin(9600);
}

void loop() {
  if (Serial.read() == 's'){
    pulseAnimator->PulseLeft(255);
  }
  pulseAnimator->Update();
}
