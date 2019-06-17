#include "Enums.hpp"

#include "IMotor.hpp"
#include "IDistanceSensor.hpp"
#include "ICommunicator.hpp"

#include "UltrasonicDistanceSensor.hpp"
#include "StepperMotor.hpp"
#include "SerialCommunicator.hpp"

IDistanceSensor* sensor;
IMotor* motor;
ICommunicator* communicator;

void setup() {
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(9600);
  sensor = new UltrasonicDistanceSensor(12,13);
  motor = new StepperMotor(200,8,9,10,11);
}

void loop() {
  // put your main code here, to run repeatedly:
  States x = sensor->GetState();
  motor->SetState(x);
  communicator->SetState(x);
}
