#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PulseAnimator : IAnimator
{
private:
    ILedstrip* strip;
    int stripSize;
public:
    PulseAnimator(ILedstrip* strip, int stripSize);
    ~PulseAnimator();

    void Update();
    void PulseLeft(int intensity);
    void PulseRight(int intensity);
};

PulseAnimator::PulseAnimator(ILedstrip* strip, int stripSize)
{
    this->strip = strip;
    this->stripSize = stripSize;
}

PulseAnimator::~PulseAnimator()
{
    delete strip;
}

void PulseAnimator::Update()
{
    ;
}

void PulseAnimator::PulseLeft(int intensity)
{
    ;
}

void PulseAnimator::PulseRight(int intensity)
{
    ;
}
