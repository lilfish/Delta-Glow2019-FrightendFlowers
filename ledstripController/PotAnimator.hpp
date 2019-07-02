#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PotAnimator : IAnimator
{
private:
    ILedstrip *strip;
    int stripSize;

    unsigned long fade_timer = 0;
    //fade counters
    int fadeEffect_counter = 0;
    int fadeIn_counter = 0;
    int fadeOut_counter = 0;
    // fade speed = for fadeIn and fadeOut
    #ifdef DEBUG
    int fade_speed = 20;
    #else
    int fade_speed = 3000;
    #endif
    // fade_effect_speed = for fadeEffect
    #ifdef DEBUG
    int fade_effect_speed = 20;
    #else
    int fade_effect_speed = 1000;
    #endif
    float max_brightness = 255;

    // Private fade effect functions
    void FadeEffect();
    void FadeOut();
    void FadeIn();

    // Bools to check wether fade in or fade out effects are done
    bool StartFadeIn_Bool = false;
    bool StartFadeOut_Bool = false;
    bool StartFadeEffect_Bool = false;
    
    // Easing function (penners formula)
    float SinEasingFunction(float t, float b, float c, float d);

public:
    PotAnimator(ILedstrip *strip);
    ~PotAnimator();

    void Update();
    void TurnOffLeds();
    void TurnOnLeds(int r, int g, int b);

    void StartFadeIn();
    void StartFadeOut();
    void PulseEffect();
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
    FadeOut();
    FadeIn();
    FadeEffect();
}

void PotAnimator::PulseEffect()
{
    StartFadeEffect_Bool = true;
}

void PotAnimator::FadeEffect()
{
    if(StartFadeEffect_Bool){
        
        float brightness = 0;
        if (fadeEffect_counter != fade_speed)
        {
            fadeEffect_counter += 1;
            if (fadeEffect_counter <= fade_speed / 2)
            {
                brightness = max_brightness - SinEasingFunction(fadeEffect_counter, 0, max_brightness, fade_effect_speed);
            }
            else
            {
                brightness = SinEasingFunction(fadeEffect_counter, 0, max_brightness, fade_effect_speed);
            }

    #ifdef DEBUG
            Serial.println("fadeIn&out effect - counter:");
            Serial.println(fadeEffect_counter);
            Serial.print("Brightness is set to: ");
            Serial.println(brightness);
    #endif

            strip->SetBrightness(int(brightness));
        }
        else
        {
            fadeEffect_counter = 0;
            StartFadeEffect_Bool = false;
        }
    }
}

void PotAnimator::StartFadeOut()
{
    StartFadeOut_Bool = true;
}

void PotAnimator::FadeOut()
{
    if(StartFadeOut_Bool){
        if (fadeOut_counter != fade_speed)
        {
            fadeOut_counter += 1;
            float brightness = 0;

            brightness = max_brightness - SinEasingFunction(fadeOut_counter, 0, max_brightness, fade_speed);

    #ifdef DEBUG
            Serial.println("Fade out effect - counter 2:");
            Serial.println(fadeOut_counter);
            Serial.print("Brightness is set to: ");
            Serial.println(brightness);
    #endif
            strip->SetBrightness(int(brightness));
        }
        else if (fadeOut_counter >= fade_speed)
        {
            fadeOut_counter = 0;
            StartFadeOut_Bool = false;
        }
    }
}

void PotAnimator::StartFadeIn()
{
    StartFadeIn_Bool = true;
}

void PotAnimator::FadeIn()
{
    if (StartFadeIn_Bool)
    {

        if (fadeIn_counter != fade_speed)
        {
            fadeIn_counter += 1;
            float brightness = 0;

            brightness = SinEasingFunction(fadeIn_counter, 0, max_brightness, fade_speed);

#ifdef DEBUG
            Serial.print("Fade in effect - counter:");
            Serial.println(fadeIn_counter);
            Serial.print("Brightness is set to: ");
            Serial.println(brightness);
#endif
            strip->SetBrightness(int(brightness));
        }
        else
        {
            fadeIn_counter = 0;
            StartFadeIn_Bool = false;
        }
    }
}

void PotAnimator::TurnOffLeds()
{
    strip->TurnOffLeds();
}

void PotAnimator::TurnOnLeds(int r, int g, int b)
{
    strip->TurnOnLeds(r, g, b);
}

float PotAnimator::SinEasingFunction(float t, float b, float c, float d)
{
    return -c * cos(t / d * (PI / 2)) + c + b;
}