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
    int amountOfLeds;

public:
    WS2812Strip(CRGB *ledArray, int numleds, uint8_t brightness);
    ~WS2812Strip();

    bool SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b);
    void Update();
};

WS2812Strip::WS2812Strip(CRGB *ledArray, int amountOfLeds, uint8_t brightness)
{
    this->ledArray = ledArray;
    this->amountOfLeds = amountOfLeds;
    FastLED.setBrightness(brightness);
}

WS2812Strip::~WS2812Strip()
{
    
}

bool WS2812Strip::SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b)
{
    if (pos >= amountOfLeds || pos < 0)
    {
        return false;
    }
    ledArray[pos] = CRGB(r,g,b);
}

void WS2812Strip::Update()
{
    FastLED.show();
}