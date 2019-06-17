#pragma once
#include "IMotor.hpp"
#include "Enums.hpp"
#include <Stepper.h>

class StepperMotor : public IMotor
{
private:
    Stepper* stepper;
    States state;
    float stepper_height;
public:
    StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b);
    void Update();
    void SetState(States state);
    float CalculateHeight(float restlesness);
    ~StepperMotor();
};

StepperMotor::StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b) : IMotor()
{
    stepper = new Stepper(stepsPerRev, m1a, m1b, m2a, m2b);
    state = CALM;
}

StepperMotor::~StepperMotor()
{
    //REMOVE STEPPER*;
}

void StepperMotor::Update()
{
    //MOVETOPOS;
}

void StepperMotor::SetState(States state)
{
    
}

float StepperMotor::CalculateHeight(float restlesness)
{
    /*
    My calculations:
    The frame is around 220cm
    the plant will hang at around 110cm (the center)
    there are 4 states which are devided by a restlesness of 0-400

    that means we can devide 110/400*restlesness to get the actual height of the plant.
    If restlesness > 400, drop dead.
     */
    stepper_height = (float)110 / 400;
    stepper_height = stepper_height * restlesness;

    #ifdef DEBUG
    Serial.print("CalculateHeight @  restlesness: ");
    Serial.println(restlesness);
    Serial.print("CalculateHeight @  stepper_height: ");
    Serial.println(stepper_height);
    Serial.println("");
    #endif

    return stepper_height;
}