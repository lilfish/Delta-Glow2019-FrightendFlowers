#pragma once
#include "Enums.hpp"



class MotorSerialCommunicator
{
public:
    MotorSerialCommunicator(int baudrate);

    //assume strip data goes to left
    //left frame Serial1
    void SendPulseLeftFrame(int outgoingIntensity);
    bool GetPulseLeftFrame(int& incomingIntensity);

    //right frame Serial2
    void SendPulseRightFrame(int outgoingIntensity);
    bool GetPulseRightFrame(int& incomingIntensity);

    //ledstrip arduino Serial3
    void SendPulseRightStrip(int outgoingIntensity);
    void SendPulseLeftStrip(int outgoingIntensity);
    void SendMood(States mood);
};

MotorSerialCommunicator::MotorSerialCommunicator(int baudrate)
{
    Serial1.begin(baudrate);
    Serial2.begin(baudrate);
    Serial3.begin(baudrate);
}


void MotorSerialCommunicator::SendPulseLeftFrame(int outgoingIntensity)
{
    int intensityOut = map(outgoingIntensity, 0, 255, 128, 255);
    char buf[] = { 'p', intensityOut };
    Serial1.write(buf,2);
}

bool MotorSerialCommunicator::GetPulseLeftFrame(int& incomingIntensity)
{
    if (Serial2.available() > 1)
    {
        if (Serial.read() == 'p')
        {
            incomingIntensity = map(Serial2.read(), 128,255,0,255);
            return true;
        }
    }
    return false;
}

void MotorSerialCommunicator::SendPulseRightFrame(int outgoingIntensity)
{
    int intensityOut = map(outgoingIntensity, 0, 255, 128, 255);
    char buf[] = { 'p', intensityOut };
    Serial2.write(buf,2);
}

bool MotorSerialCommunicator::GetPulseRightFrame(int& incomingIntensity)
{
    if (Serial2.available() > 1)
    {
        if (Serial.read() == 'p')
        {
            incomingIntensity = map(Serial2.read(), 128,255,0,255);
            return true;
        }
    }
    return false;
}

void MotorSerialCommunicator::SendPulseRightStrip(int outgoingIntensity)
{
    int intensityOut = map(outgoingIntensity, 0, 255, 128, 255);
    char buf[] = { 'r', intensityOut };
    Serial3.write(buf,2);
}

void MotorSerialCommunicator::SendPulseLeftStrip(int outgoingIntensity)
{
    int intensityOut = map(outgoingIntensity, 0, 255, 128, 255);
    char buf[] = { 'l', intensityOut };
    Serial3.write(buf,2);
}

void MotorSerialCommunicator::SendMood(States mood)
{
    char buf[] = { 'm', mood };
    Serial3.write(buf,2);
}
