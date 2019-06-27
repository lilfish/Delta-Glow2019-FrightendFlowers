// #define DEBUG

#include "Enums.hpp"

#include "IMotor.hpp"
#include "ICommunicator.hpp"

#include "StepperMotor.hpp"
#include "SerialCommunicator.hpp"

IDistanceSensor *sensor;
IMotor *motor;
ICommunicator *communicator;
States state = UNINITIALIZED;

int restlesness = 0;

void setup()
{
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(9600);
  motor = new StepperMotor(200, 8, 9, 10, 11);
}

void loop()
{
  
  // // put your main code here, to run repeatedly:
  States state = communicator->GetState();
  
  communicator->SetState(state);
  
  delay(500);
}
