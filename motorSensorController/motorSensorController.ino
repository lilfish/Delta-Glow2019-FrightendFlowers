// #define DEBUG

#include "Enums.hpp"

#include "IMotor.hpp"
#include "ICommunicator.hpp"

#include "SerialCommunicator.hpp"

IMotor *motor;
ICommunicator *communicator;
States state = UNINITIALIZED;

int restlesness = 0;

void setup()
{
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(9600);

}

void loop()
{
  
  // // put your main code here, to run repeatedly:
  States state = communicator->GetState();
  
  communicator->SetState(state);
  
  delay(500);
}
