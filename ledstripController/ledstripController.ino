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

bool start_fading = false;  
bool potAnimator_bool = false;
bool un_fade = false;
bool dead = false;

CRGB pulseLeds[pulseLedsSize];
CRGB potLeds1[potLeds1Size];
CRGB potLeds2[potLeds2Size];

PulseAnimator *pulseAnimator;
PotAnimator *potAnimator;
PotAnimator *potAnimator2;

void setup()
{
  FastLED.addLeds<WS2812B, pulseLedsPin, RGB>(pulseLeds, pulseLedsSize);
  FastLED.addLeds<WS2812B, potLeds1Pin, RGB>(potLeds1, potLeds1Size);
  FastLED.addLeds<WS2812B, potLeds2Pin, RGB>(potLeds2, potLeds2Size);

  ILedstrip *pulseStrip;
  ILedstrip *potStrip1;
  ILedstrip *potStrip2;

  pulseStrip = new WS2812Strip(pulseLeds, pulseLedsSize, 255);
  potStrip1 = new WS2812Strip(potLeds1, potLeds1Pin, 255);
  potStrip2 = new WS2812Strip(potLeds2, potLeds2Pin, 255);

  pulseAnimator = new PulseAnimator(pulseStrip);
  potAnimator = new PotAnimator(potStrip1);
  potAnimator2 = new PotAnimator(potStrip2);

  Serial.begin(9600);
#ifdef DEBUG
  Serial.println("Began on 9600");
#endif
}

void loop()
{
  // Serial communication if statemnets
  if (Serial.read() == 'l')
  {
    pulseAnimator->PulseLeft(255);
#ifdef DEBUG
    Serial.println("I read a l (Left pulse) ");
#endif
  }
  else if (Serial.read() == 'r')
  {
    pulseAnimator->PulseRight(255);
#ifdef DEBUG
    Serial.println("I read a r (Right pulse) ");
#endif
  }
  else if (Serial.read() == '5')
  {
    start_fading = true;
#ifdef DEBUG
    Serial.println("I read a 5 (Going out) ");
#endif
  }
  else if (Serial.read() == '1')
  {
    if(dead){
      dead = false;
      un_fade = true;
    }
#ifdef DEBUG
    Serial.println("I read a 1 (Calm) ");
#endif
  }

  // do a update every (pulse_update_period) 500ms
  pulseAnimator->Update();

  //do a fade effect for 600 ticks
  if (start_fading)
  {
    if(potAnimator->FadeOut()){
        Serial.println("potAnimator->FadeOut(); = true");
        start_fading = false;
        dead = true;
    }
  }
  if (un_fade)
  {
    if(potAnimator->FadeIn()){
        Serial.println("potAnimator->FadeIn(); = true");
        un_fade = false;
        dead = false;
    }
  }
}
