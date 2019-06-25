int sensorPin = A0;    // select the input pin for the potentiometer      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
float distance;

// the speed to change the restlessness
int speed = 5;

float y;
float restlessness = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
  //the distance should be maximal 2.5meter which is 250 cm.
  distance = float(300)/1023*sensorValue;
  Serial.println(distance);
  
  if (distance <= 250){
    y = speed-(float(speed)/250*distance);
    Serial.println(y);
    if (restlessness < 100){
      restlessness += y;
    } else if(restlessness >= 100 && restlessness < 200){
      restlessness += (y + 1);
    } else if(restlessness >= 200 && restlessness < 300){
      restlessness += (y + 2);
    } else if(restlessness >= 300){
      restlessness += (y + 3);
    }
  } else if(restlessness > 0) {
    restlessness -= 4;
  }
  if (restlessness < 0) {
    restlessness = 0;
  }
  
  Serial.println(restlessness);
  delay(300);
}