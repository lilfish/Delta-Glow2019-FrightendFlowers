#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>
#include <Arduino.h>

// information about this class and its functions can be found here:
// https://git.fhict.nl/I393504/glow-2019/wikis/%5BPROGRAMMING%5D-How-The-WS2812Strip-Class-Works

class WS2812Strip : public ILedstrip
{
private:
    CRGB *ledArray;
    int amountOfLeds;

public:
    WS2812Strip(CRGB *ledArray, int numleds, uint8_t brightness);
    ~WS2812Strip();

    int GetSize();
    void ClearStrip();
    void SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b);
    void SetBrightness(int brightness);
    void Update();
    void TurnOffLeds();
    void TurnOnLeds(int r, int g, int b);
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

int WS2812Strip::GetSize()
{
    return amountOfLeds;
}

void WS2812Strip::SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b)
{
    //make sure that the pos is not out of range
    if (pos == amountOfLeds)
    {
        pos -= 1;
    }
    //sed the color for that position
    ledArray[pos] = CRGB(r, g, b);
#ifdef DEBUG
    Serial.print("Led array - " + String(r) + String(g) + String(b) + " : ");
    for (size_t i = 0; i < amountOfLeds; i++)
    {
        Serial.print(ledArray[i]);
        Serial.print("  ");
    }
    Serial.print(" --------- ");
    Serial.println(amountOfLeds);
    delay(1);
#endif
}

void WS2812Strip::ClearStrip()
{
    fill_solid(ledArray, amountOfLeds, CRGB::Black);
}

void WS2812Strip::Update()
{
    FastLED.show();
}

void WS2812Strip::SetBrightness(int brightness)
{
    FastLED.setBrightness(brightness);
}

void WS2812Strip::TurnOffLeds()
{
    fill_solid(ledArray, amountOfLeds, CRGB::Black);
    FastLED.show();
}
void WS2812Strip::TurnOnLeds(int r, int g, int b)
{
    fill_solid(ledArray, amountOfLeds, CRGB(r, g, b));
    FastLED.show();
}