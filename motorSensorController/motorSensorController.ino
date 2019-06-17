#include "Enums.hpp"
#include "IMotor.hpp"
#include "IDistanceSensor.hpp"
#include "ICommunicator.hpp"

IDistanceSensor* sensor;
IMotor* motor;
ICommunicator* communicator;

void setup() {
  // put your setup code here, to run once:
  /*
  sensor = new UltrasonicDistanceSensor(12,13);

   */


}

void loop() {
  // put your main code here, to run repeatedly:
  // 
  States x = sensor->GetState();
  motor->SetState(x);
  communicator->SetState(x);
}
