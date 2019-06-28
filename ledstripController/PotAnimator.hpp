#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PotAnimator : IAnimator
{
private:
    ILedstrip* strip;
    int stripSize;
public:
    PotAnimator(ILedstrip* strip, int stripSize);
    ~PotAnimator();

    void Update();
    void FadeEffect(int intensity);
    void FadeOut(int intensity);
};

PotAnimator::PotAnimator(ILedstrip* strip, int stripSize)
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
    ;
}

void PotAnimator::FadeEffect(int intensity)
{
    ;
}

void PotAnimator::FadeOut(int intensity)
{
    ;
}
