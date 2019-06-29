#pragma once

#include "Enums.hpp"
#include <Stepper.h>

class StepperMotor
{
private:
    Stepper* stepper;
    int currentHeight;
public:
    StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b);
    void Update();
    void SetState(States state);
    float CalculateHeight(float restlesness);
    ~StepperMotor();

    bool GoToHeight(int height);
    int CurrentHeight();
    bool Shake(int intensity);
    void FallDown();
};

StepperMotor::StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b) : IMotor()
{
    stepper = new Stepper(stepsPerRev, m1a, m1b, m2a, m2b);
    stepper.SetSpeed(60);

    pinMode(m1a, OUTPUT);
    pinMode(m1b, OUTPUT);
    pinMode(m2a, OUTPUT);
    pinMode(m2b, OUTPUT);

    state = CALM;
}

StepperMotor::~StepperMotor()
{
    delete stepper;
}

bool StepperMotor::GoToHeight(int height)
{
    int posToMove = currentHeight + height;
    stepper.step(posToMove);
    return true;
}

bool StepperMotor::Shake(int intensity)
{
    stepper.step(intensity);
    stepper.step(-1 * intensity);
    return true;
}

int StepperMotor::CurrentHeight()
{
    return currentHeight;
}

void StepperMotor::FallDown()
{
    digitalWrite(m1a,LOW);
    digitalWrite(m1b,LOW);
    digitalWrite(m2a,LOW);
    digitalWrite(m2b,LOW);
}