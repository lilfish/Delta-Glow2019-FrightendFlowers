#define DEBUG

#include "Enums.hpp"

#include "ILedstrip.hpp"
#include "WS2812Strip.hpp"

#define STRIP_SIZE 30
#define STRIP_PIN 12

const int pulseLedsSize = 0;
const int pulseLedsPin = 0;
const int potLeds1Size = 0;
const int potLeds1Pin = 0;
const int potLeds2Size = 0;
const int potLeds2Pin = 0;

CRGB pulseLeds[pulseLedsSize];
CRGB potLeds1[potLeds1Size];
CRGB potLeds2[potLeds2Size];

ILedstrip* pulseStrip;
ILedstrip* potStrip1;
ILedstrip* potStrip2;

void setup() {
  FastLED.addLeds<WS2812B, pulseLedsPin, RGB>(pulseLeds, pulseLedsSize);
  FastLED.addLeds<WS2812B, potLeds1Pin, RGB>(potLeds1, potLeds1Size);
  FastLED.addLeds<WS2812B, potLeds2Pin, RGB>(potLeds2, potLeds2Size);

  pulseStrip = new WS2812Strip(pulseLeds, pulseLedsSize, 255);
  potStrip1 = new WS2812Strip(potLeds1, potLeds1Pin, 255);
  potStrip2 = new WS2812Strip(potLeds2, potLeds2Pin, 255);
}

void loop() {
  pulseStrip->Update();
  potStrip1->Update();
  potStrip2->Update();
}
