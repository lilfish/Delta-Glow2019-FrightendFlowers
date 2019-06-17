#pragma once
#include "Enums.hpp"

class IMotor
{
public:
    virtual void SetState(States state) = 0;
    virtual void Update() = 0;
    virtual ~IMotor() {}
};

