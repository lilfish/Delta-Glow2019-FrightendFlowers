#pragma once
#include "Enums.hpp"

class ILedstrip
{
public:
    virtual bool SetPixel(int pos, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void Update();
    virtual ~ILedstrip() {}
};
