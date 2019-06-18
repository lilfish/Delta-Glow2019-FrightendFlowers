#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>

class WS2812Strip : public ILedstrip
{
private:
    CRGB *ledArray;
    int numleds;
    States old_state;

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

void WS2812Strip::SetState(States state)
{
    if (old_state != state)
    {
        old_state = state;

        if (state == CALM)
        {
            Serial.println("calm");
        }
        else if (state == RESTLESS1)
        {
            Serial.println("RESTLESS1");
        }
        else if (state == RESTLESS2)
        {
            Serial.println("RESTLESS2");
        }
        else if (state == RESTLESS3)
        {
            Serial.println("RESTLESS3");
        }
        else if (state == OUT)
        {
            Serial.println("OUT");
        }
    }

    ledArray[1] = CRGB(255, 255, 0);
    FastLED.show(); //do stuff
}