#define DEBUG

#include "Enums.hpp"
#include "Color.hpp"

#include "ILedstrip.hpp"
#include "WS2812Strip.hpp"
#include "PulseAnimator.hpp"
#include "PotAnimator.hpp"

#define STRIP_SIZE 30
#define STRIP_PIN 12

const int pulseLedsSize = 60;
const int pulseLedsPin = 10;
const int potLeds1Size = 30;
const int potLeds1Pin = 11;
const int potLeds2Size = 30;
const int potLeds2Pin = 9;

CRGB pulseLeds[pulseLedsSize];
CRGB potLeds1[potLeds1Size];
CRGB potLeds2[potLeds2Size];

PulseAnimator *pulseAnimator;
PotAnimator *potAnimator;
PotAnimator *potAnimator2;

ILedstrip *pulseStrip;
ILedstrip *potStrip1;
ILedstrip *potStrip2;

void setup()
{
  FastLED.addLeds<WS2812B, pulseLedsPin, RGB>(pulseLeds, pulseLedsSize);
  FastLED.addLeds<WS2812B, potLeds1Pin, RGB>(potLeds1, potLeds1Size);
  FastLED.addLeds<WS2812B, potLeds2Pin, RGB>(potLeds2, potLeds2Size);

  pulseStrip = new WS2812Strip(pulseLeds, pulseLedsSize, 255);
  potStrip1 = new WS2812Strip(potLeds1, potLeds1Size, 255);
  potStrip2 = new WS2812Strip(potLeds2, potLeds2Size, 255);

  pulseAnimator = new PulseAnimator(pulseStrip);
  potAnimator = new PotAnimator(potStrip1);
  potAnimator2 = new PotAnimator(potStrip2);

  pulseAnimator->TurnOffLeds();
  potAnimator->TurnOnLeds(myColorR, myColorG, mycolorB);
  potAnimator2->TurnOnLeds(myColorR, myColorG, mycolorB);

  Serial.begin(115200);
#ifdef DEBUG
  Serial.println("Began on 115200");
#endif
}

void loop()
{
  // Serial communication if statemnets
  if (Serial.read() == 'l')
  {
#ifdef DEBUG
    Serial.println("I read a r (Right pulse) ");
#endif
    Serial.flush();
    pulseAnimator->PulseRight();
  }

  if (Serial.read() == 'r')
  {
#ifdef DEBUG
    Serial.println("I read a l (Left pulse) ");
#endif
    Serial.flush();
    pulseAnimator->PulseLeft();
  }

  if (Serial.read() == 'd')
  {
    potAnimator->StartFadeOut();
    potAnimator2->StartFadeOut();
#ifdef DEBUG
    Serial.println("I read a d (Going out) ");
#endif
  }

  if (Serial.read() == 'c')
  {
    potAnimator->StartFadeIn();
    potAnimator2->StartFadeIn();
    Serial.flush();
#ifdef DEBUG
    Serial.println("I read a c (Calm) ");
#endif
  }

  if (Serial.read() == 'p')
  {
    potAnimator->PulseEffect();
    potAnimator2->PulseEffect();
    Serial.flush();
#ifdef DEBUG
    Serial.println("I read p (FadeEffect)");
#endif
  }

  // do a update every (pulse_update_period) 500ms
  pulseAnimator->Update();
  potAnimator->Update();
  potAnimator2->Update();
}
