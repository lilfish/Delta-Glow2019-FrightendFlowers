#pragma once
#include "Enums.hpp"

class ICommunicator
{
public:
    virtual void SetState(States state) = 0;
    virtual States GetState() = 0;
    virtual ~ICommunicator() { }

    virtual void SendPulseLeftFrame(uint8_t intensity) = 0;
    virtual void SendPulseRightFrame(uint8_t intensity) = 0;
    virtual uint8_t GetPulseFromLeftFrame() = 0;
    virtual uint8_t GetPulseFromRightFrame() = 0;

    virtual int GetPulseFromStrip(uint8_t intensity) = 0;
};
