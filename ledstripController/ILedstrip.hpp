#pragma once
#include "Enums.hpp"

class ILedstrip
{
public:
    virtual void SetState(States state) = 0;
    virtual void ledAnimation() = 0;
    virtual ~ILedstrip() {}
};
