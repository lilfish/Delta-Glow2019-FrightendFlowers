#include "Enums.hpp"

#include "ICommunicator.hpp"
#include "ILedstrip.hpp"

#include "SerialCommunicator.hpp"
#include "WS2812Strip.hpp"

ICommunicator* communicator;
ILedstrip* strip;

#define STRIP_SIZE 30
#define STRIP_PIN 12

int x = 0;

CRGB Leds[STRIP_SIZE];

void setup() {
  // put your setup code here, to run once:
  communicator = new SerialCommunicator(9600);
  FastLED.addLeds<WS2812B, STRIP_PIN, RGB>(Leds, STRIP_SIZE);
  strip = new WS2812Strip(Leds,STRIP_SIZE);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  States state = communicator->GetState();
  Serial.println(state);
  strip->SetState(state);

  /*
  This is a function that can change the led lights without a delay or a for loop. 
  This way we can still run the code that is written above. (kind of using
  the loop() as a for loop).
  --------------------------

  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
    startMillis = currentMillis;
    >>>>>>>>>>>>>>>>> (run function using int x & state) <<<<<<<<<<<<<
    
    if (++x >= STRIP_SIZE) x = 0;
  }

  ----------------------------
  Another way would be to just run an animation in the GetState() function.
  Depends on what you guys think is best.

   */
}
