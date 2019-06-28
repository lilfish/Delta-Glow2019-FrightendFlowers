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


    void SendPulseLeftFrame(uint8_t intensity);
    void SendPulseRightFrame(uint8_t intensity);
    uint8_t GetPulseFromLeftFrame();
    uint8_t GetPulseFromRightFrame();

    bool GetPulseFromStrip(bool& goesLeft, int& intensity);
};

SerialCommunicator::SerialCommunicator(int baudrate)
{
    Serial1.begin(baudrate);
    Serial2.begin(baudrate);
    Serial3.begin(baudrate);
    currentState = UNINITIALIZED;
}

SerialCommunicator::~SerialCommunicator()
{

}

void SerialCommunicator::SetState(States state)
{   
    currentState = state;

    Serial.print('s');
    Serial.print(state);
    Serial.flush();
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

void SerialCommunicator::SendPulseLeftFrame(uint8_t intensity)
{
    uint8_t toSend = map(intensity, 0, 255, 128, 255);
    char buf[] = { 'l', toSend };
    Serial2.write(buf,2);
}
void SerialCommunicator::SendPulseRightFrame(uint8_t intensity)
{
    uint8_t toSend = map(intensity, 0, 255, 128, 255);
    char buf[] = { 'r', toSend };
    Serial1.write(buf,2);
}

uint8_t SerialCommunicator::GetPulseFromLeftFrame()
{
    uint8_t incomingVal = 0;
    while (Serial2.available() > 0)
    {
        if (Serial2.read() == 'r')
        {
            incomingVal = Serial2.read();
            incomingVal = map(incomingVal, 128, 255, 0, 255);
            break;
        }
    }

    return incomingVal;
}
uint8_t SerialCommunicator::GetPulseFromRightFrame()
{
    uint8_t incomingVal = 0;
    while (Serial1.available() > 0)
    {
        if (Serial1.read() == 'r')
        {
            incomingVal = Serial1.read();
            incomingVal = map(incomingVal, 128, 255, 0, 255);
            break;
        }
    }

    return incomingVal;
}

bool SerialCommunicator::GetPulseFromStrip(bool& goesLeft, int& intensity)
{
    uint8_t incomingVal = 0;
    bool succes = false;

    while (Serial3.available() > 1)
    {
        if (Serial3.read() == 'l')
        {
            goesLeft = true;
            incomingVal = map(Serial3.read(), 128, 255, 0, 255);
            succes = true;
            break;
        }
        if (Serial3.read() == 'r')
        {
            goesLeft = false;
            incomingVal = map(Serial3.read(), 128, 255, 0, 255);
            succes = true;
            break;
        }
    }
    return succes;
}
