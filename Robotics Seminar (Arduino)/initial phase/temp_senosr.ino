#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

float voltage = 0;
float degreesC = 0;
float degreesF = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  voltage = analogRead(A0) * 0.004882813;
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Degrees C: ");
  lcd.print(degreesC);

  lcd.setCursor(0,1);
  lcd.print("Degrees F: ");
  lcd.print(degreesF);
  
  delay(1000);
}
