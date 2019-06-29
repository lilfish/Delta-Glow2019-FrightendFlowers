#define DEBUG

#include "Enums.hpp"

#include "LedstripSerialCommunicator.hpp"

LedstripSerialCommunicator com(115200);

void setup() {

}

int incomingVal;
void loop() {
    if (com.incomingPulseCenter(incomingVal))
    {
        //animator.animatecenter(incomingVal);
    }
}
