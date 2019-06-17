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
            readSomething = true;
        }
    }
    Serial.flush();

    givenState = readString.toInt();

    // to be removed
    Serial.print("Given state: ");
    Serial.println(givenState);
    
        
    if (givenState == (CALM || RESTLESS1 || RESTLESS2 || RESTLESS3 || OUT))
    {
        currentState = (States)givenState;
    }

    // to be removed
    Serial.print("currentState: ");
    Serial.println(currentState);
    
    return currentState;
}