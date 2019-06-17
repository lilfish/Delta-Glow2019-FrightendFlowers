#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>


class WS2812Strip : public ILedstrip
{
private:
    CRGB* ledArray;
    int numleds;
public:
    WS2812Strip(CRGB* ledArray, int numleds);
    ~WS2812Strip();

    void SetState(States state);
};

WS2812Strip::WS2812Strip(CRGB* ledArray, int numleds)
{
    this->ledArray = ledArray;
    this->numleds = numleds;
}

WS2812Strip::~WS2812Strip()
{
}

void WS2812Strip::SetState(States state)
{
    ledArray[1] = CRGB(255,255,0);
    FastLED.show();//do stuff
}