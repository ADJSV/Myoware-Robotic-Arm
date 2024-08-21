#include <Servo.h>

//Pin Assignment
  //Servos
  const byte servoPins[]= {3, 5, 6, 9, 10, 11};
  //Sensor and Button
  const int buttonPin=2;
  const int sensorPin=A0;

//Create Servo Objects
Servo servo[6];

//Initial Pos Motors
volatile int servoPosition[] = {90, 90, 90, 90, 90, 90};

//Initialize variables
int servoSelect=0;
int buttonVal=HIGH;

//Assign Thresholds after testing sensors
int myfloor=220;
int myroof=500;

//Storing max and min range
int mini=0;
int maxi=180;

//test
float forceVal=250;

void setup() {
  Serial.begin(9600);
  //Wait 4s to start, usually to manually turn on arm
  delay(4000);
  pinMode(buttonPin, INPUT_PULLUP);//Set button to change servos
  //Attach Pins to Servos and set them to initial pos
  for(int n = 0; n < 6; n++){
    servo[n].attach(servoPins[n]);
    if (n>0){servo[n].write(servoPosition[n]);}
    else {servo[0].write(servoPosition[n]);}
  }
  digitalWrite(LED_BUILTIN, HIGH);//Turn on LED to indicate running
}

void loop() {
  //Read sensor and button
  //float sensorVal= analogRead(sensorPin);
  float sensorVal=forceVal;
  //float scaledVal= map(sensorVal, 0, 1000, 0, 180 );
  buttonVal=digitalRead(buttonPin);
  //Serial.print("Sensor Value:");
 // Serial.println(sensorVal);

//If the button is pressed switch to next servo
  if (buttonVal==LOW){
    servoSelect=servoSelect+1;
    servoSelect=(servoSelect==1)? 2 : servoSelect;
    servoSelect=(servoSelect>5)? 0 : servoSelect;
    Serial.print("Selected Servo: ");
    Serial.println(servoSelect);

    //Wait for release of the button before proceeding. Only 1 change per press
    while(buttonVal==LOW){
      buttonVal=digitalRead(buttonPin);
    }
  }

  //moveMotor(sensorVal, servoSelect);
  oneDirection(sensorVal, servoSelect);
  //test(servoSelect-1);
  delay(50);

}

void moveMotor(float sensorVal, int selection){
  if ((sensorVal>=myfloor) && (sensorVal <=myroof-1)){
    if(servoPosition[selection]>=mini){
      servoPosition[selection]=servoPosition[selection]-5;
      servo[selection].write(servoPosition[selection]);
    }
  }
  if (sensorVal>=myroof){
    if(servoPosition[selection]<=maxi){
      servoPosition[selection]=servoPosition[selection]+5;
      servo[selection].write(servoPosition[selection]);
    }
  }
}

void oneDirection(float sensorVal, int selection){
  if (sensorVal>=myfloor){
    servoPosition[selection]=(servoPosition[selection]==maxi)? minim:servoPosition[selection];
    if(servoPosition[selection]<=maxi){
      servoPosition[selection]=servoPosition[selection]+5;
      servo[selection].write(servoPosition[selection]);
      Serial.println(servo[selection].read());
    }
  }
}

void test(int index){
  for (int pos = mini; pos <= maxi; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo[index].write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (int pos = maxi; pos >= mini; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo[index].write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

//Changes global vars mini and maxi to adjust range depending on servo
voidRangeSelector(int selection){
  switch(selection){
    case 1:
      mini=0;
      maxi=0;
      break;
    case 2:
      mini=0;
      maxi=90;
      break;
    case 3:
      mini=0;
      maxi=120;
      break;
    case 4:
      mini=0;
      maxi=90;
      break;
    case 5:
      mini=0;
      maxi=180;
      break;            
    default:
      mini=75;
      maxi=110;
      break;      
  }
}