#pragma once

#include "IDistanceSensor.hpp"
#include "Enums.hpp"

class UltrasonicDistanceSensor : public IDistanceSensor
{
private:  //HIER STAAN JE VARIABELEN DIE OVER DE HELE CLASS BESCHIKBAAR MOETEN ZIJN, MAAR NIET ERBUITEN
    int out;
    int in;
public: // HIER STAAND DE VARIABELEN DIE ZOWEL BINNEN ALS BUITEN DE CLASS BESCHIKBAAR MOETEN ZIJN
    States GetState();
    UltrasonicDistanceSensor(int out, int in);
    ~UltrasonicDistanceSensor(); // <-- NEGEER DEZE MAAR VINCENT
};

UltrasonicDistanceSensor::UltrasonicDistanceSensor(int out, int in)
{
    this->out = out;
    this->in = in;
}

UltrasonicDistanceSensor::~UltrasonicDistanceSensor() {}  // <-- NEGEER DEZE OOK MAAR VINCENT

States UltrasonicDistanceSensor::GetState()
{
    //States currentState = CALM;

    // DO STUFF


    //return currentState;
}