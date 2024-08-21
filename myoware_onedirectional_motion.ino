#include <Servo.h>

//const byte servoPins[] = {3};
//const int buttonPin = 2;

Servo myservo1;
int Inpos;
const int sensorPin = A0;

//Servo servo[1];

//int servoPosition[] = {90};

int myfloor = 80;
int myroof = 900;

void setup() {
  Serial.begin(9600);
  delay(4000);
  myservo1.attach(6);
  Inpos = 0;

  //pinMode(buttonPin, INPUT_PULLUP);
  
  //for (int n = 0; n < 6; n++) {
    //servo[n].attach(servoPins[n]);
    //servo[n].write(servoPosition[n]);
  

  // Set the pin mode for the built-in LED
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {
  // Your loop code here

  float sensorVal = analogRead(sensorPin);
  float scaledVal = map(sensorVal, 0, 1000, 0, 180);

    
    //Serial.println(scaledVal);
    Serial.println(sensorVal);
    delay(50);


  if (sensorVal >= myfloor) {
  Inpos = Inpos + 1;
  myservo1.write(Inpos);
  
  }

  if (sensorVal >= myroof) {
  Inpos = Inpos + 5;
  myservo1.write(Inpos);
  }

  if (Inpos >= 90) {
    Inpos = 0;
    myservo1.write(Inpos);
  }
  



}
