#pragma once
#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PulseAnimator : IAnimator
{
private:
    ILedstrip* strip;
    int stripSize;
public:
    PulseAnimator(ILedstrip* strip);
    ~PulseAnimator();

    void Update();
    void PulseLeft(int intensity);
    void PulseRight(int intensity);
};

PulseAnimator::PulseAnimator(ILedstrip* strip)
{
    this->strip = strip;
    this->stripSize = strip->GetSize();
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
