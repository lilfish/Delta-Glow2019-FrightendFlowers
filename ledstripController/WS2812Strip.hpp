#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>

class WS2812Strip : public ILedstrip
{
private:
    CRGB *ledArray;
    int numleds;
    States old_state;

    int stepinanimation;
    int calmCounter;
    void ledAnimation();

public:
    WS2812Strip(CRGB *ledArray, int numleds);
    ~WS2812Strip();

    void SetState(States state);
};

WS2812Strip::WS2812Strip(CRGB *ledArray, int numleds)
{
    this->ledArray = ledArray;
    this->numleds = numleds;
}

WS2812Strip::~WS2812Strip()
{
}

void ledAnimation(){
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

        if (state == CALM)
        {
            ledAnimation();
            if(calmCounter => 4){
              calmCounter = 0;
              stepinanimation += 1
            }
        }
        else if (state == RESTLESS1)
        {
          ledAnimation();
            if(calmCounter => 3){
              calmCounter = 0;
              stepinanimation += 1
            }
        }
        else if (state == RESTLESS2)
        {
          ledAnimation();
            if(calmCounter => 2){
              calmCounter = 0;
              stepinanimation += 1
            }
        }
        else if (state == RESTLESS3)
        {
            ledAnimation();
            if(calmCounter => 1){
              calmCounter = 0;
              stepinanimation += 1
            }
        }
        else if (state == OUT)
        {
            //Serial.println("OUT");
        }

        if (stepinanimation >= STRIP_SIZE){
          stepinanimation = 0;
        }
  }

    ledArray[1] = CRGB(255, 255, 0);
    FastLED.show(); //do stuff
}
