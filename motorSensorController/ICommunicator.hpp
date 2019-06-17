#pragma once
#include "Enums.hpp"

class ICommunicator
{
public:
    virtual void SetState(States state) = 0;
    virtual States GetState() = 0;
    virtual ~ICommunicator() { }
};
