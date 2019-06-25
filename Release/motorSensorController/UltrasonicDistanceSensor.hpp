#pragma once

#include "IDistanceSensor.hpp"
#include "Enums.hpp"

class UltrasonicDistanceSensor : public IDistanceSensor
{
private: //HIER STAAN JE VARIABELEN DIE OVER DE HELE CLASS BESCHIKBAAR MOETEN ZIJN, MAAR NIET ERBUITEN
    int trigPin;
    int echoPin;
    long duration;
    float distance;

    int restlesness = 0;
    int speed = 5;

    float y;

    States new_state;

public: // HIER STAAND DE VARIABELEN DIE ZOWEL BINNEN ALS BUITEN DE CLASS BESCHIKBAAR MOETEN ZIJN


    int GetDistance();
    int PotentioSetDistance();
    int CalculateRestlesness(States state);
    UltrasonicDistanceSensor(int trigPin, int echoPin);
    ~UltrasonicDistanceSensor(); // <-- NEGEER DEZE MAAR VINCENT
};

UltrasonicDistanceSensor::UltrasonicDistanceSensor(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

UltrasonicDistanceSensor::~UltrasonicDistanceSensor() {} // <-- NEGEER DEZE OOK MAAR VINCENT

int UltrasonicDistanceSensor::GetDistance()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //States currentState = CALM;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // DO STUFF
    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    return distance;
}

int UltrasonicDistanceSensor::PotentioSetDistance()
{
    distance = analogRead(potPin);
    distance = (float(250)/1023)*distance;

    // Prints the distance on the Serial Monitor
    return distance;
}

int UltrasonicDistanceSensor::CalculateRestlesness(States state)
{
    // int current_detected_distance = PotentioSetDistance(); //For testing purposes only
    int current_detected_distance = GetDistance();

    if(state == UNINITIALIZED){
        state = CALM;
    }

    if (current_detected_distance <= 250)
    {
        y = speed - (float(speed) / 250 * current_detected_distance);

        if (state == CALM)
        {
            restlesness += y;
        }
        else if (state == RESTLESS1)
        {
            restlesness += (y + 1);
        }
        else if (state == RESTLESS2)
        {
            restlesness += (y + 2);
        }
        else if (state == RESTLESS3)
        {
            restlesness += (y + 3);
        }
    }
    else if (restlesness > 0)
    {
        restlesness -= 4;
    }
    if (restlesness < 0)
    {
        restlesness = 0;
    }
    
    #ifdef DEBUG
    Serial.print("CalculateRestlesness @  restlesness: ");
    Serial.println(restlesness);
    Serial.print("CalculateRestlesness @  distance: ");
    Serial.println(distance);
    Serial.print("CalculateRestlesness @  current_detected_distance: ");
    Serial.println(current_detected_distance);
    Serial.print("CalculateRestlesness @  state: ");
    Serial.println((States)state);
    Serial.println("");
    #endif
    return restlesness;
}
