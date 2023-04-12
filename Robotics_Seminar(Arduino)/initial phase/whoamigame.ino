#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int buttonPin = 2;
int buzzerPin = 6;
int buttonPressTime = 0;

long timeLimit = 15000;
long startTime = 0;
int roundNumber = 0;
const int arraySize = 25;

const char * words[arraySize] = {"moose", "beaver", "bear", "goose", "dog", "cat", "squirrel", "bird", "elephant", "horse", 
                                  "giraffe", "seal", "bat", "skunk", "turtle", "whale", "rhino", "lion", "monkey", "frog", "alligator",
                                  "kangaroo", "hippo", "rabbit"};
int sequence[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.begin(16, 2);

//  generateRandomOrder();

//  showStartSequence();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < arraySize; i++){
    lcd.clear();

    roundNumber = i+1;
    lcd.print(roundNumber);
    lcd.print(": ");
    lcd.print(words[sequence[i]]);

    startTime = millis();

    while (digitalRead(buttonPin) == HIGH){
      int roundedTime = round((timeLimit - (millis() - startTime)) / 1000);
      lcd.setCursor(14,1);
      lcd.print(" ");
      lcd.setCursor(14,1);
      lcd.print(roundedTime);
      delay(15);

      if (millis() - startTime > timeLimit){
//        gameOver();
        }

      if (digitalRead(buttonPin) == LOW) {
        tone(buzzerPin, 272, 10);
        }
      }
    delay(500);
    }
    
}
