#define DEBUG

#include "Enums.hpp"

#include "IMotor.hpp"
#include "IDistanceSensor.hpp"
#include "ICommunicator.hpp"

#include "UltrasonicDistanceSensor.hpp"
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
  sensor = new UltrasonicDistanceSensor(9, 10);
  motor = new StepperMotor(200, 8, 9, 10, 11);
}

void loop()
{
  
  // // put your main code here, to run repeatedly:
  if (state != (States)OUT)
  {
    restlesness = sensor->CalculateRestlesness(state);
  }

  //check what state it should be in
  if (restlesness > 0 && restlesness <= 100)
  {
    state = (States)CALM;
  }
  else if (restlesness > 100 && restlesness <= 200)
  {
    state = (States)RESTLESS1;
  }
  else if (restlesness > 200 && restlesness <= 300)
  {
    state = (States)RESTLESS2;
  }
  else if (restlesness > 300 && restlesness <= 400)
  {
    state = (States)RESTLESS3;
  }
  else if (restlesness > 400)
  {
    state = (States)OUT;
  }

  float motor_distance = motor->CalculateHeight(restlesness);
  
  communicator->SetState(state);
  
  delay(500);
}
