#pragma once

#include "IDistanceSensor.hpp"
#include "Enums.hpp"

class UltrasonicDistanceSensor : public IDistanceSensor
{
private: //HIER STAAN JE VARIABELEN DIE OVER DE HELE CLASS BESCHIKBAAR MOETEN ZIJN, MAAR NIET ERBUITEN
    int trigPin;
    int echoPin;
    long duration;
    int distance;

    int restlesness = 0;
    int potPin = 2;

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

    /*
    Please don't kill me for this many if statements. 
    I really had to make this in a quick way, so sometimes 
    the quickest way is the most dirtiest.. 
    I'm very dissapointed in my self... so... 
    you don't have to, change it when we have more time :)
     */

    if(state == UNINITIALIZED){
        state = CALM;
    }
    if (current_detected_distance < 250 && restlesness <= 400)
    { // als er iemand te dicht bij is
        if (current_detected_distance <= 25)
        {
            if (state == CALM)
            {
                restlesness += 10;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 11;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 16;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 20;
            }
        }
        else if (current_detected_distance > 25 && current_detected_distance <= 50)
        {
            if (state == CALM)
            {
                restlesness += 7;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 9;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 14;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 17;
            }
        }
        else if (current_detected_distance > 50 && current_detected_distance <= 100)
        {
            if (state == CALM)
            {
                restlesness += 5;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 7;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 12;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 14;
            }
        }
        else if (current_detected_distance > 100 && current_detected_distance <= 150)
        {
            if (state == CALM)
            {
                restlesness += 3;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 6;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 9;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 10;
            }
        }
        else if (current_detected_distance > 150 && current_detected_distance <= 200)
        {
            if (state == CALM)
            {
                restlesness += 2;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 4;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 6;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 8;
            }
        }
        else if (current_detected_distance > 200 && current_detected_distance <= 250)
        {
            if (state == CALM)
            {
                restlesness += 1;
            }
            else if (state == RESTLESS1)
            {
                restlesness += 2;
            }
            else if (state == RESTLESS2)
            {
                restlesness += 4;
            }
            else if (state == RESTLESS3)
            {
                restlesness += 6;
            }
        }
    }
    else if (restlesness != 0)
    { // als er niemand dichtbij is
        Serial.println(state);
        if (state == (States)RESTLESS3)
        {
            restlesness -= 10;
        }
        else if (state == (States)RESTLESS2)
        {
            restlesness -= 5;
        }
        else if (state == (States)RESTLESS1)
        {
            restlesness -= 2;
        }
        else if (state == (States)CALM)
        {
            restlesness -= 1;
        }

        if (restlesness < 0)
        {
            restlesness = 0;
        }
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