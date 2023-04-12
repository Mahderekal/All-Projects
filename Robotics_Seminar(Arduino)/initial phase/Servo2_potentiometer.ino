#include <Servo.h>

Servo myservo;

int analogPin = A0;
int analogval;
int potposition;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogval = analogRead(analogPin);
  potposition = map(analogval, 0, 1023, 0, 180);

  myservo.write(potposition);

}
