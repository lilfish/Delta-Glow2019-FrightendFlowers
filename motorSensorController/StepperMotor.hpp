#pragma once
#include "IMotor.hpp"
#include "Enums.hpp"
#include <Stepper.h>

class StepperMotor : public IMotor
{
private:
    Stepper* stepper;
    States state;
public:
    StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b);
    void Update();
    void SetState(States state);
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
    ;
}