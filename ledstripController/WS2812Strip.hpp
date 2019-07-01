#pragma once
#include "ILedstrip.hpp"
#include <FastLED.h>
#include <Arduino.h>
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 34
#define LED_PIN 7
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];

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
};

WS2812Strip::WS2812Strip(CRGB *ledArray, int amountOfLeds, uint8_t brightness)
{
    this->ledArray = ledArray;
    this->amountOfLeds = amountOfLeds;
    FastLED.setBrightness(brightness);
    // fill_solid( ledArray, amountOfLeds, CRGB::Red);
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
    ledArray[pos] = CRGB(r, g, b);
#ifdef DEBUG
    Serial.print("Led array - " + String(r) + String(g) + String(b) + " : ");
    for (size_t i = 0; i < amountOfLeds; i++)
    {
        Serial.print(ledArray[i]);
        Serial.print("  ");
    }
    Serial.println(" --------- ");
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