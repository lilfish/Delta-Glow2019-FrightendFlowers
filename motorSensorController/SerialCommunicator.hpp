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
    
    currentState = state;
    #ifdef DEBUG
    Serial.print("SetState @  Wanting to send this over rx & tx: ");
    Serial.print('s');
    Serial.println("");
    Serial.println(state);
    Serial.print("SetState @  currentState: ");
    Serial.println(currentState);
    Serial.println("");
    #else
    Serial.print('s');
    Serial.print(state);
    Serial.flush();
    #endif
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
        }
        #ifdef DEBUG
        char debug_readBuffer;
        debug_readBuffer += Serial.read();
        Serial.print("GetState @  debug_readBuffer: ");
        Serial.println(debug_readBuffer);
        Serial.println("");
        #endif
    }
    Serial.flush();

    givenState = (States)readString.toInt();

    
    if (givenState == CALM || givenState == RESTLESS1 || givenState == RESTLESS2 || givenState == RESTLESS3 || givenState == OUT)
    {
        currentState = (States)givenState;
    }

    return currentState;
}