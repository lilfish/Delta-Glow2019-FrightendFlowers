// #define DEBUG

#include "Enums.hpp"

#include "IMotor.hpp"
#include "StepperMotor.hpp"

StepperMotor motor(200,1,2,3,4);

void setup()
{
// put your setup code here, to run once:

}

void loop()
{
    motor.GoToHeight(900);
    motor.Shake(3);
}
