#include "Enums.hpp"
#include "MotorSerialCommunicator.hpp"

MotorSerialCommunicator com(115200);

void setup()
{

}

int buffer;
void loop()
{  
    if (com.GetPulseLeftFrame(buffer))
    {
        com.SendPulseLeftStrip(buffer);
    }
}
