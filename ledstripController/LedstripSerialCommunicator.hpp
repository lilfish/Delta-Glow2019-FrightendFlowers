#pragma once

class LedstripSerialCommunicator
{
public:
    LedstripSerialCommunicator(int baudrate);

    bool incomingPulseLeft(int& intensity);
    bool incomingPulseRight(int& intensity);
    bool incomingPulseCenter(int& intensity);
    void SendMood(States mood);
};

LedstripSerialCommunicator::LedstripSerialCommunicator(int baudrate)
{
    Serial.begin(baudrate);
}

bool LedstripSerialCommunicator::incomingPulseLeft(int& intensity)
{
    if (Serial.available() > 1)
    {
        if (Serial.read() == 'l')
        {
            int incomingVal = Serial.read();
            intensity = map(incomingVal, 128, 255, 0, 255);
            return true;
        }
    }
    return false;
}

bool LedstripSerialCommunicator::incomingPulseRight(int& intensity)
{
    if (Serial.available() > 1)
    {
        if (Serial.read() == 'r')
        {
            int incomingVal = Serial.read();
            intensity = map(incomingVal, 128, 255, 0, 255);
            return true;
        }
    }
    return false;
}

bool LedstripSerialCommunicator::incomingPulseCenter(int& intensity)
{
    if (Serial.available() > 1)
    {
        if (Serial.read() == 'c')
        {
            int incomingVal = Serial.read();
            intensity = map(incomingVal, 128, 255, 0, 255);
            return true;
        }
    }
    return false;
}

void LedstripSerialCommunicator::SendMood(States mood)
{
    char buf[] = { 'm', mood };
    Serial3.write(buf,2);
}