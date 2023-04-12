#include <Servo.h>

const int trigPin = 11;
const int echoPin = 12;
float distance = 0;
int counter;


Servo alerttime;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  alerttime.attach(9);

}
float getdistance(){
  float echoTime;
  float calculatedDistance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn (echoPin, HIGH);

  calculatedDistance = echoTime / 148.0;
  return calculatedDistance;
  }

void loop() {
  // put your main code here, to run repeatedly:
  distance = getdistance();

  Serial.print(distance);
  Serial.println(" in");

  if (distance <=50){
    for (counter = 0; counter <= 180; counter ++){
      alerttime.write(counter);
      delay(15);
      }
    for (counter = 180; counter >= 0; counter --){
      alerttime.write(counter);
      delay(15);
      }
    for (counter = 0; counter <= 180; counter ++){
      alerttime.write(counter);
      delay(15);
      }
    for (counter = 180; counter >= 0; counter --){
      alerttime.write(counter);
      delay(15);
      }
    }
}
