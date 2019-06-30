#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PotAnimator : IAnimator
{
private:
    ILedstrip* strip;
    int stripSize;
public:
    PotAnimator(ILedstrip* strip);
    ~PotAnimator();

    void Update();
    void FadeEffect();
    void FadeOut();
    void FadeIn();
};

PotAnimator::PotAnimator(ILedstrip* strip)
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
    FastLED.show();
}

void PotAnimator::FadeEffect()
{
    ;
}

void PotAnimator::FadeOut()
{
    ;
}
