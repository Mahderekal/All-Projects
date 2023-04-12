#include <Arduino.h>


//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor


//distance variables
const int trigPin = 6;
const int echoPin = 5;

int switchPin = 7;             //switch to turn the robot on and off

float distance = 0;            //variable to store the distance measured by the distance sensor

//robot behaviour variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up

int leftPR = A1;
int rightPR = A0;
int leftLight;
int rightLight;
int ltamb;
int rtamb;
int threshold = 700;

/********************************************************************************/
void setup()
{
  pinMode(trigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped


  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);                       //begin serial communication with the computer
  Serial.print("To infinity and beyond!");  //test the serial connection

  pinMode(leftPR, INPUT);
  pinMode(rightPR, INPUT);
  ltamb = analogRead(leftPR);
  rtamb = analogRead(rightPR);

    //read the brightness of the ambient light
  leftLight = analogRead(leftPR);
  rightLight = analogRead(rightPR);
  
  //set motors to excitatory
  int ltMotor = map(leftLight, ltamb, 1023, 0, 255);
  int rtMotor = map(rightLight, rtamb, 1023, 0, 255);

  //constrain motors to motor speeds
  ltMotor = constrain(ltMotor, 0, 255);
  rtMotor = constrain(rtMotor, 0, 255);

  //send speed to motors
  rightMotor(rtMotor);
  leftMotor(ltMotor);

}

void loop()
{
  // fear
  ltMotorSpeed = map(ltMinLight, ltMaxLight, ltMotorMinSpeed, ltMotorMaxSpeed);
  rtMotorSpeed = map(rtMinLight, rtMaxLight, rtMotorMinSpeed, rtMotorMaxSpeed);
  ltMotor = constrain(ltMotor, 0, 255);
  rtMotor = constrain(rtMotor, 0, 255);
  
  
  Serial.print("left PR reading: ");
  Serial.println(leftLight);
  Serial.print("right PR reading: ");
  Serial.println(rightLight);  
  delay(100);

    //light loving and fearing (changing between 255 and -255
  if (rightLight > threshold && leftLight > threshold) {
    rightMotor(-255);
    leftMotor(-255);
    //delay(500);
    } 
    else {
      rightMotor(0);
      leftMotor(0);
      //delay(500);
      }
   
    //aggression behavior: run towards the light aggressively 
    if (rightLight > threshold && rightLight > leftLight){
      rightMotor(255);
      leftMotor(100);
      delay(100);
      }  
      else if (leftLight > threshold && leftLight > rightLight) {
        rightMotor(100);
        leftMotor(255);
        delay(100);
        }
        else {
          rightMotor(0);
          leftMotor(0);
          delay(100);
          }

      //explorer
     if (rightLight > threshold && rightLight > leftLight){
      rightMotor(-100);
      leftMotor(-255);
      delay(100);
      }  
      else if (leftLight > threshold && leftLight > rightLight) {
        rightMotor(-255);
        leftMotor(-100);
        delay(100);
        }
        else {
          rightMotor(0);
          leftMotor(0);
          delay(100);
          }

  }

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}
