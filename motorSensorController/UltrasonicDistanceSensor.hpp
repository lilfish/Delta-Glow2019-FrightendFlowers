#include "IDistanceSensor.hpp"
#include "Enums.hpp"

class UltrasonicDistanceSensor : public IDistanceSensor
{
private:
    int out;
    int in;
public:
    States GetState();
    UltrasonicDistanceSensor(int out, int in);
    ~UltrasonicDistanceSensor(); // <-- NEGEER DEZE MAAR VINCENT
};

UltrasonicDistanceSensor::UltrasonicDistanceSensor(int out, int in)
{
    this->out = out;
    this->in = in;
}

UltrasonicDistanceSensor::~UltrasonicDistanceSensor() {}  // <-- NEGEER DEZE OOK MAAR VINCENT

States UltrasonicDistanceSensor::GetState()
{
    
}