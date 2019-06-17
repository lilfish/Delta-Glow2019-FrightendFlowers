#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  34

CRGB leds[NUM_LEDS];
int randNumber;

void setup() {
  Serial.begin(9600);
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

void loop()
{
  // Serial.println("startloop");
  delay(100);
  randNumber = random(1, 3);
  // Serial.println(randNumber);

  // send communication forward
  for (int i = 0; i < NUM_LEDS; i++) {
    randNumber = random(2, 4);
    leds[i - 2].setRGB(0, 0, 0);
    leds[i].setRGB(255, 255, 0);
    FastLED.show();
    delay(20);
    
    // Serial.println(randNumber);
  }
  //Serial.println("afterfirstloop");
  //send communication backwards
  for (int i = NUM_LEDS; i > 0; i--) {
    randNumber = random(1, 3);
    leds[i + 2].setRGB(0, 0, 0);
    leds[i].setRGB(0, 0, 255);
    FastLED.show();
    delay(20);
    
    // Serial.println(randNumber);
  }
  Serial.println("loopdone");
}
