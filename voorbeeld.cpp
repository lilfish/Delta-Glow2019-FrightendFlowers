
int arrSize = 20;

int pulsesForwards[arrSize];
int pulsesBackwards[arrSize];
int stripsize = 30;

CRGB leds[stripsize];

newPulseForward()
{
    for (size_t i = 0; i < arrSize; i++)
    {
        if (pulseForward[i] >= stripsize)
        {
            pulseForward[i] = 0;
        }
    }
}

update()
{
    for (size_t i = 0; i < arrSize; i++)
    {
        if (pulsesForwards[i] <= stripsize)
        {
            int position = pulsesForwards[i];
            CRGB currentColor = leds[position];

            leds[position] = CRGB(0,0,0);
            leds[position + 1] = currentColor; 

            pulsesForwards[i] += 1;
        }
        if (pulsesBackwards[i] > 0)
        {
            int position = pulsesForwards[i];
            CRGB currentColor = leds[position];
            leds[position] = CRGB(0,0,0);
            leds[position - 1] = currentColor;

            pulsesBackwards -= 1;
        }
    }
    
    FastLED.show();
}