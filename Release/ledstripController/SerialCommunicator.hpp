#pragma once
#include "Enums.hpp"
#include "ICommunicator.hpp"


class SerialCommunicator : public ICommunicator
{
    private:
        States currentState;
    public:
        SerialCommunicator(int baudrate);
        States GetState();
        void SetState(States state);
        ~SerialCommunicator();
};

SerialCommunicator::SerialCommunicator(int baudrate)
{
    Serial.begin(baudrate);
    // Serial.begin(baudrate);

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
    States givenState;
    char readBuffer;
    String readString;

    while (Serial.available() > 0)
    {
        delay(3);
        if (Serial.read() == 's')
        {
            readBuffer = Serial.read();
            readString = readBuffer; 
            Serial.println(readString);
        }
    }
    Serial.flush();

    givenState = (States)readString.toInt();

    
    if (givenState == CALM || givenState == RESTLESS1 || givenState == RESTLESS2 || givenState == RESTLESS3 || givenState == OUT)
    {
        currentState = (States)givenState;
    }

    return currentState;
}