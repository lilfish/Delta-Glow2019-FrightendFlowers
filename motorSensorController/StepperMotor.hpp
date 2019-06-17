#pragma once
#include "IMotor.hpp"
#include "Enums.hpp"
#include <Stepper.h>

#define STEPPER_MAX 950

class StepperMotor : public IMotor
{
private:
    Stepper* stepper;
    States state;
    int currentPos;

    int m1a;
    int m1b; 
    int m2a; 
    int m2b;
public:
    StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b);
    void Update();
    void SetState(States state);
    void GoToPosition(int pos);
    void FallDown();
    ~StepperMotor();
};

StepperMotor::StepperMotor(int stepsPerRev, int m1a, int m1b, int m2a, int m2b) : IMotor()
{
    stepper = new Stepper(stepsPerRev, m1a, m1b, m2a, m2b);
    stepper->setSpeed(60);
    state = CALM;
    this->m1a = m1a;
    this->m1b = m1b; 
    this->m2a = m2a; 
    this->m2b = m2b;
    currentPos = 0;
}

StepperMotor::~StepperMotor()
{
    delete stepper;
}

void StepperMotor::GoToPosition(int pos)
{
    if (pos <= 0 || pos > STEPPER_MAX)
    {
        return;
    }
    stepper->step(pos - currentPos);
    currentPos = pos;
}

void StepperMotor::FallDown()
{
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    currentPos = 0;
}

void StepperMotor::Update()
{
    int posToMoveTo = 0;
    switch (state)
    {
        case CALM:
            posToMoveTo = 700;
            break;
        case RESTLESS1:
            posToMoveTo = 750;
            break;
        case RESTLESS2:
            posToMoveTo = 800;
            break;
        case RESTLESS3:
            posToMoveTo = 850;
            break;
        case OUT:
            FallDown();
            break;
        default:
            break;
    }
    Serial.println("postomoc");
    Serial.println(posToMoveTo);

    Serial.println("stepstotake");
    int stepsToTake = posToMoveTo - currentPos;
    Serial.println(stepsToTake);
    stepper->step(stepsToTake);
    currentPos = currentPos + stepsToTake;
}

void StepperMotor::SetState(States state)
{
    this->state = state;
}
