#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>
#include <Arduino.h>
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  34
#define LED_PIN     7
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];


    
class WS2812Strip : public ILedstrip
{
private:
    CRGB *ledArray;
    int numleds;
    States old_state;

    int stepinanimation = 0;
    int calmCounter;
    void ledAnimation();

    int strip_size =60; 
    int currentMillis;
    int startMillis;
    int period;

public:
    WS2812Strip(CRGB *ledArray, int numleds);
    ~WS2812Strip();

    void SetState(States state);
    
};

WS2812Strip::WS2812Strip(CRGB *ledArray, int numleds)
{
    this->ledArray = ledArray;
    this->numleds = numleds;
    LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}

WS2812Strip::~WS2812Strip()
{
}

void WS2812Strip::ledAnimation(){
  Serial.println(stepinanimation);
  leds[stepinanimation - 2].setRGB(0, 0, 0);
  leds[stepinanimation].setRGB(255, 255, 0);
  FastLED.show();
}

void WS2812Strip::SetState(States state)
{
    currentMillis = millis();
    if (currentMillis - startMillis >= period) {
        startMillis = currentMillis;

        calmCounter += 1;

        if (state == CALM || state == UNINITIALIZED)
        {
            ledAnimation();
            if(calmCounter >= 4){
              calmCounter = 0;
              stepinanimation += 1;
            }
        }
        else if (state == RESTLESS1)
        {
          ledAnimation();
            if(calmCounter >= 3){
              calmCounter = 0;
              stepinanimation += 1;
            }
        }
        else if (state == RESTLESS2)
        {
          ledAnimation();
            if(calmCounter >= 2){
              calmCounter = 0;
              stepinanimation += 1;
            }
        }
        else if (state == RESTLESS3)
        {
            ledAnimation();
            if(calmCounter >= 1){
              calmCounter = 0;
              stepinanimation += 1;
            }
        }
        else if (state == OUT)
        {
            //Serial.println("OUT");
        }

        if (stepinanimation >= NUM_LEDS){
          stepinanimation = 0;
        }
  }

    ledArray[1] = CRGB(255, 255, 0);
    FastLED.show(); //do stuff
}
