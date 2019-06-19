#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    100
//#define ROOT-1LEDS  0 - 100
//#define ROOT-2LEDS  101 - 200
//#define PPOT-1LEDS  100
        //Root #1 -  0 / ??
        //Root #2 - ?? / ??
        //PPot #1 - ?? / ??
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  34

CRGB leds[NUM_LEDS];
int randNumber;
int state;

void setup() {
  Serial.begin(9600);
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

// UNINTIALISED (NOT NEEDED IN ANIMATIONS) = 0
// RESTLESS 3   = 1
// RESTLESS 2   = 2
// RESTLESS 1   = 3
// CALM         = 4
// OUT          = 5

void loop()
{
  state = (1);

  if (state == 1){
  delay(10);
    // first led strip
    // send communication forward
    for (int i = 0; i < NUM_LEDS; i++) {
      randNumber = random(2, 4);
      leds[i - 2].setRGB(0, 0, 0);
      leds[i].setRGB(255, 255, 0);
      FastLED.show();
      delay(10);
   }
//    // second led strip
//    // send communication forward
//    for (int i = 0; i < NUM_LEDS; i++) {
//      randNumber = random(2, 4);
//      leds[i - 2].setRGB(0, 0, 0);
//      leds[i].setRGB(0, 0, 255);
//      FastLED.show();
//      delay(20);    
//    }
//
//
//
//    //Janes pot animation
//    //
//    //      code
//    //
//    
 }
  
  if (state == 2){ //slow
  // Serial.println("startloop");
  delay(500);
  //  randNumber = random(1, 3);
  // Serial.println(randNumber);

  // send communication forward
  for (int i = 0; i < NUM_LEDS; i++) {
    randNumber = random(2, 4);
    leds[i - 2].setRGB(0, 0, 0);
    leds[i].setRGB(255, 255, 0);
    FastLED.show();
    delay(400);
    // Serial.println(randNumber);
    }
  }
  if (state == 3){ //slower
  // Serial.println("startloop");
  delay(1000);
  //  randNumber = random(1, 3);
  // Serial.println(randNumber);

  // send communication forward
  for (int i = 0; i < NUM_LEDS; i++) {
    randNumber = random(2, 4);
    leds[i - 2].setRGB(0, 0, 0);
    leds[i].setRGB(255, 255, 0);
    FastLED.show();
    delay(80);
    // Serial.println(randNumber);
    }
  }

  if (state == 4){ //super slow
  // Serial.println("startloop");
  delay(2000);
  //  randNumber = random(1, 3);
  // Serial.println(randNumber);

  // send communication forward
  for (int i = 0; i < NUM_LEDS; i++) {
    randNumber = random(2, 4);
    leds[i - 2].setRGB(0, 0, 0);
    leds[i].setRGB(255, 255, 0);
    FastLED.show();
    delay(100);
    // Serial.println(randNumber);
      }
    }
  
  if (state == 5){ //dead
  }
    for (int i = 0; i < NUM_LEDS; i++) {
    randNumber = random(2, 4);
    leds[i].setRGB(0, 0, 0);
    FastLED.show();
    delay(20);
  }
   

//  //Serial.println("afterfirstloop");
//  //send communication backwards
//  for (int i = NUM_LEDS; i > 0; i--) {
//    randNumber = random(1, 3);
//    leds[i + 2].setRGB(0, 0, 0);
//    leds[i].setRGB(0, 0, 255);
//    FastLED.show();
//    delay(20);
//    
//    // Serial.println(randNumber);
//  }
//  Serial.println("loopdone");

 }
