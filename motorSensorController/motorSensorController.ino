#include "Enums.hpp"

#include "IMotor.hpp"
#include "StepperMotor.hpp"

StepperMotor motor(200, 8, 9, 10, 11);

int maxHeight = 2700;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor.GoToHeight(maxHeight - 300);
}


void loop()
{
  motor.GoToHeight(maxHeight);
  delay(2000);
  motor.FallDown();
  motor.GoToHeight(maxHeight - 300);
  for (int i = 0; i < 40; i++)
  {
    motor.Shake(50);
  }
}
