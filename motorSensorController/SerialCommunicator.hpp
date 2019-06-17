#pragma once
#include "Enums.hpp"
#include "ICommunicator.hpp"


class SerialCommunicator : public ICommunicator
{
private:
    States currentState;
    int readBuffer;
public:
    SerialCommunicator(int baudrate);
    States GetState();
    void SetState(States state);
    ~SerialCommunicator();
};

SerialCommunicator::SerialCommunicator(int baudrate)
{
    Serial.begin(baudrate);
    currentState = UNINITIALIZED;
}

SerialCommunicator::~SerialCommunicator()
{

}

void SerialCommunicator::SetState(States state)
{
    Serial.print('s');
    Serial.print(state);
    Serial.flush();
    currentState = state;
}

States SerialCommunicator::GetState()
{
    bool readSomething = false;
    while (Serial.available() > 0)
    {
        if (Serial.read() == 's')
        {
            readBuffer = Serial.read();
        }
    }
    if (readSomething)
    {
        Serial.flush();
        if (readBuffer == (CALM || RESTLESS1 || RESTLESS2 || RESTLESS3 || OUT))
        {
            currentState = (States)readBuffer;
        }
    }
    return currentState;
}