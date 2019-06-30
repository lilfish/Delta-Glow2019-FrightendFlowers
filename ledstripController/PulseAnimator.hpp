#pragma once

#include "Enums.hpp"

#include "IAnimator.hpp"
#include "ILedstrip.hpp"

class PulseAnimator : IAnimator
{
private:
    ILedstrip *strip;
    int stripSize;

    States state = CALM;

    //array needed for pulse left and PulseRight
    //we allow maximal 50 pulses & set all on -1
    int pulseLeftArray[50];
    int pulseRightArray[50];
    int arraySizeLeft = 50;
    int arraySizeRight = 50;

    // for desiding the pulse length
    long randNumber;

public:
    PulseAnimator(ILedstrip *strip);
    ~PulseAnimator();

    void Update();
    void PulseLeft(int intensity);
    void PulseRight(int intensity);
};

PulseAnimator::PulseAnimator(ILedstrip *strip)
{
    this->strip = strip;
    this->stripSize = strip->GetSize();

    for (byte i = 0; i < arraySizeLeft; i++)
    {
        this->pulseLeftArray[i] = -1;
    }

    for (byte i = 0; i < arraySizeRight; i++)
    {
        this->pulseRightArray[i] = -1;
    }
}

PulseAnimator::~PulseAnimator()
{
    delete strip;
}

void PulseAnimator::Update()
{
#ifdef DEBUG
    boolean print_left = false;
    for (int i = 0; i < arraySizeLeft; i++)
    {
        if (pulseLeftArray[i] > -1)
        {
            print_left = true;
        }
    }
    if (print_left)
    {
        Serial.print("(LEFT)");
        Serial.print(arraySizeLeft);
        Serial.print(": ");
        Serial.print('[');
        for (int i = 0; i < arraySizeLeft; i++)
        {
            Serial.print(pulseLeftArray[i]);
            Serial.print(", ");
        }
        Serial.println(']');
    }
#endif

    // Pulse left going up 1 if it's not stripsize + 1
    for (int i = 0; i < arraySizeLeft; i++)
    {

        if (pulseLeftArray[i] >= stripSize)
        {
            strip->SetPixel(i, 0, 0, 0);
            pulseLeftArray[i] = -1;
#ifdef DEBUG
            Serial.println("(LEFT) Done playing a full strip");
#endif
        }
        else if (pulseLeftArray[i] >= 0)
        {
            strip->SetPixel(i, 0, 0, 0);
            strip->SetPixel((i + 1), 255, 0, 0);
            pulseLeftArray[i] += 1;
        }
    }

#ifdef DEBUG
    boolean print_right = false;
    for (int i = 0; i < arraySizeLeft; i++)
    {
        if (pulseRightArray[i] > -1)
        {
            print_right = true;
        }
    }
    if (print_right)
    {
        Serial.print("(RIGHT)");
        Serial.print(arraySizeRight);
        Serial.print(": ");
        Serial.print('[');
        for (int i = 0; i < arraySizeRight; i++)
        {
            Serial.print(pulseRightArray[i]);
            Serial.print(", ");
        }
        Serial.println(']');
    }
#endif

    // Pulse right going down 1 if it's not stripsize + 1
    for (int i = 0; i < arraySizeRight; i++)
    {
        if (pulseRightArray[i] == 0)
        {
            strip->SetPixel(i, 0, 0, 0);
            pulseRightArray[i] = -1;
#ifdef DEBUG
            Serial.println("(RIGHT) Done playing a full strip right side");
#endif
        }
        else if (pulseRightArray[i] != -1)
        {
            strip->SetPixel(i, 0, 0, 0);
            strip->SetPixel((i - 1), 255, 0, 0);
            pulseRightArray[i] -= 1;
        }
    }

    strip->Update(); //do stuff
}

void PulseAnimator::PulseLeft(int intensity)
{
    randNumber = random(1, 3);

#ifdef DEBUG
    Serial.print("(RIGHT) Adding a pulse to the  ledstrip - Pulse width: ");
    Serial.println(randNumber);
#endif

    bool left_done = false;
    int left_counter = 0;

#ifdef DEBUG
    Serial.print("adding numbers: ");
#endif
    for (size_t i = 0; i < arraySizeLeft; i++)
    {
        if (!left_done)
        {
            if (pulseLeftArray[i] == -1)
            {
                left_counter += 1;
                pulseLeftArray[i] = 0;
#ifdef DEBUG
                Serial.print(i);
                Serial.print(',');
#endif
                if (left_counter == randNumber)
                {
                    left_done = true;
                }
            }
        }
    }
#ifdef DEBUG
    Serial.println(" to the let ledstrip");
    Serial.print("Left counter: ");
    Serial.println(left_counter);
#endif
}

void PulseAnimator::PulseRight(int intensity)
{
    randNumber = random(1, 3);

#ifdef DEBUG
    Serial.print("(RIGHT) Adding a pulse to the  ledstrip - Pulse width: ");
    Serial.println(randNumber);
#endif

    bool right_done = false;
    int right_counter = 0;

#ifdef DEBUG
    Serial.print("adding numbers: ");
#endif
    for (size_t i = 0; i < arraySizeRight; i++)
    {
        if (!right_done)
        {
            if (pulseRightArray[i] == -1)
            {
                right_counter += 1;
                pulseRightArray[i] = stripSize;
#ifdef DEBUG
                Serial.print(i);
                Serial.print(',');
#endif
                if (right_counter == randNumber)
                {
                    right_done = true;
                }
            }
        }
    }
#ifdef DEBUG
    Serial.println(" to the let ledstrip");
    Serial.print("Right counter: ");
    Serial.println(right_counter);
#endif
}
