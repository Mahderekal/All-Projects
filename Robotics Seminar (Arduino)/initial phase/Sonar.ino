const int trigPin = 11;
const int echoPin = 12;
float distance = 0;
int redPin


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

  if (distance <= 10){
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0); 
    } else if (10< distance && dist
    

}
