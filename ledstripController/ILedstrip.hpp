#pragma once
#include "Enums.hpp"

class ILedstrip
{
public:
    virtual void SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void Update() = 0;
    virtual void ClearStrip() = 0;
    virtual int GetSize() = 0;
    virtual void SetBrightness(int brightness) = 0;
    virtual ~ILedstrip() {}
};
