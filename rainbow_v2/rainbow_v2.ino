#include <FastLED.h>

#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100
int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness1 = 0; 

CRGB leds1[51];
CRGB leds2[34];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
CLEDController *controllers[2];
unsigned long previousMillis = 0; 
unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0; 
int state = 1;

void setup() {
    delay( 3000 ); // power-up safety delay
    controllers[0]= &FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds1, 51).setCorrection( TypicalLEDStrip );
    controllers[1] = &FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds2, 34).setCorrection( TypicalLEDStrip );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    fill_solid(leds1, 51, CRGB::Black);
    controllers[0]->showLeds();
    fill_solid(leds2, 34, CRGB::Black);
    controllers[1]->showLeds();
    FastLED.setBrightness(  BRIGHTNESS );
}

int count = 0;
void loop()
{
  ChangePalettePeriodically();
    update_Rainbow();
    update_FlowerColor();
}
int indexStrip1 = 0;
int indexStrip2 = 0;
static uint8_t startIndex = 1;

void update_Rainbow()
{
  unsigned long currentMillis = millis();
  if(indexStrip1 < 51)
  {
    if (currentMillis - previousMillis2 >= 1) {
    previousMillis2 = currentMillis;
    FillLEDsFromPaletteColors(indexStrip1);
    }
    controllers[0]->showLeds();
    indexStrip1++;
  }
  else
  {
    if (currentMillis - previousMillis >= 1000/UPDATES_PER_SECOND) {
    previousMillis = currentMillis;
    indexStrip1 = 0;
    startIndex = 1;
    }
  }
}

void update_FlowerColor()
{
  unsigned long currentMillis = millis();
  if(indexStrip2 < 34)
  {
    GetFlowerColor(indexStrip2);
    indexStrip2++;
  }
  else
  {
    if (currentMillis - previousMillis1 >= 1000) {
    previousMillis1 = currentMillis;
    controllers[1]->showLeds();
    indexStrip2 = 0;
    }
  }
}
void FillLEDsFromPaletteColors(int ledindex)
{
  uint8_t brightness = 255;
  leds1[ledindex] = ColorFromPalette(currentPalette, startIndex, brightness, currentBlending);
  startIndex += 3;
}

void GetFlowerColor(int ledindex)
{
     leds2[ledindex].setRGB(255,255,0);  // Set Color HERE!!!
     leds2[ledindex].fadeLightBy(brightness1);
    //controllers[1]->showLeds();
    brightness1 = brightness1 + fadeAmount;
    // reverse the direction of the fading at the ends of the fade: 
    if(brightness1 == 0 || brightness1 == 255)
    {
      fadeAmount = -fadeAmount ; 
    }    
    //delay(40);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND;  }
       }
}


void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 5; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}


void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}
