#pragma once

#include "IDistanceSensor.hpp"
#include "Enums.hpp"

class UltrasonicDistanceSensor : public IDistanceSensor
{
private: //HIER STAAN JE VARIABELEN DIE OVER DE HELE CLASS BESCHIKBAAR MOETEN ZIJN, MAAR NIET ERBUITEN
    int trigPin;
    int echoPin;

    int sensitivity = 5;

    int restlessness = 0;

    float y;

    States oldState;
    

  
    States calculateState();
    int getDistance();

public: // HIER STAAND DE VARIABELEN DIE ZOWEL BINNEN ALS BUITEN DE CLASS BESCHIKBAAR MOETEN ZIJN
    int UpdateRestlessness(int distance);
    States GetState();
    UltrasonicDistanceSensor(int trigPin, int echoPin);
    ~UltrasonicDistanceSensor(); // <-- NEGEER DEZE MAAR VINCENT

};

UltrasonicDistanceSensor::UltrasonicDistanceSensor(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    oldState = UNINITIALIZED;
}

UltrasonicDistanceSensor::~UltrasonicDistanceSensor() {} // <-- NEGEER DEZE OOK MAAR VINCENT

int UltrasonicDistanceSensor::getDistance()
{
    //States currentState = CALM;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // DO STUFF
    long measuredDuration = pulseIn(echoPin, HIGH);

    float measuredDistance = measuredDuration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    return (int)measuredDistance;
}


int UltrasonicDistanceSensor::UpdateRestlessness(int distance)
{   // SEE WIKI FOR EXPLANATION: https://git.fhict.nl/I393504/glow-2019/wikis/%5BPROGRAMMING%5D-How-the-sensor-calculates-the-state
    if(oldState == UNINITIALIZED)
    {
        oldState = CALM;
    }

    if (distance <= 250)
    {
        y = sensitivity - (float(sensitivity) / 250 * distance);

        if (oldState == CALM)
        {
            restlessness += y;
        }
        else if (oldState == RESTLESS1)
        {
            restlessness += (y + 1);
        }
        else if (oldState == RESTLESS2)
        {
            restlessness += (y + 2);
        }
        else if (oldState == RESTLESS3)
        {
            restlessness += (y + 3);
        }
    }
    else if (restlessness > 0)
    {
        restlessness -= 4;
    }
    if (restlessness < 0)
    {
        restlessness = 0;
    }
    
    #ifdef DEBUG
    Serial.print("Calculaterestlessness @  restlessness: ");
    Serial.println(restlessness);
    Serial.print("Calculaterestlessness @  distance: ");
    Serial.println(distance);
    Serial.print("Calculaterestlessness @  state: ");
    Serial.println((States)oldState);
    Serial.println("");
    #endif

    return restlessness;
}

States UltrasonicDistanceSensor::calculateState()
{   // SEE WIKI FOR EXPLANATION: https://git.fhict.nl/I393504/glow-2019/wikis/%5BPROGRAMMING%5D-How-the-sensor-calculates-the-state

    if (restlessness < 0)
    {
        return CALM;
    }

    States newState = CALM;

    if (restlessness > 0 && restlessness <= 100)
    {
        newState = (States)CALM;
    }
    else if (restlessness > 100 && restlessness <= 200)
    {
        newState = (States)RESTLESS1;
    }
    else if (restlessness > 200 && restlessness <= 300)
    {
        newState = (States)RESTLESS2;
    }
    else if (restlessness > 300 && restlessness <= 400)
    {
        newState = (States)RESTLESS3;
    }
    else if (restlessness > 400)
    {
        newState = (States)OUT;
    }

    oldState = newState;
    return newState;
}

States UltrasonicDistanceSensor::GetState()
{
    int distance = getDistance();
    UpdateRestlessness(distance);
    // private restlessness is updated and used by calculateState
    States state = calculateState();
    return state;
}