#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PotAnimator : IAnimator
{
private:
    ILedstrip *strip;
    int stripSize;

    unsigned long fade_timer = 0;
    int fade_counter = 0;
    int fade_speed = 60;
    float max_brightness = 255;

    // virtual float easeIn() = 0;

public:
    PotAnimator(ILedstrip *strip);
    ~PotAnimator();

    void Update();
    void FadeEffect();
    bool FadeOut();
    bool FadeIn();

    float SinEasingFunction(float t, float b, float c, float d);
};

PotAnimator::PotAnimator(ILedstrip *strip)
{
    this->strip = strip;
    this->stripSize = stripSize;
}

PotAnimator::~PotAnimator()
{
    delete strip;
}

void PotAnimator::Update()
{
    strip->Update();
}

void PotAnimator::FadeEffect()
{
    ;
}

bool PotAnimator::FadeOut()
{
    if (millis() > fade_timer + 50)
    {
        fade_timer = millis();
        fade_counter += 1;

        float brightness = max_brightness - SinEasingFunction(fade_counter, 0, max_brightness, fade_speed);

#ifdef DEBUG
        Serial.println("Fade out effect - Millis passed: ");
        Serial.println(fade_counter);
        Serial.print("Brightness is set to: ");
        Serial.println(brightness);
#endif
        strip->SetBrightness(int(brightness));

        if (fade_counter == fade_speed)
        {
            fade_counter = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PotAnimator::FadeIn()
{
    if (millis() > fade_timer + 50)
    {
        fade_timer = millis();
        fade_counter += 1;

        float brightness = SinEasingFunction(fade_counter, 0, max_brightness, fade_speed);
        
#ifdef DEBUG
        Serial.println("Fade out effect - Millis passed: ");
        Serial.println(fade_counter);
        Serial.print("Brightness is set to: ");
        Serial.println(brightness);
#endif
        strip->SetBrightness(int(brightness));

        if (fade_counter == fade_speed)
        {
            fade_counter = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

float PotAnimator::SinEasingFunction(float t, float b, float c, float d)
{
    return -c * cos(t / d * (PI / 2)) + c + b;
}