#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD uses 4 pins: GND, VCC, SDA, SCL
LiquidCrystal_I2C lcd(0x27, 16, 2);



const int echo = 13;
const int trig = 12;

int LED1 = 2;   // TOO CLOSE
int LED2 = 3;   // CLOSE
int LED3 = 4;   // YOU HAVE SPACE
int LED4 = 5;   // OPEN
int buzzer = 8;

int duration = 0;
int distance = 0;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {

  digitalWrite(trig, HIGH);
  delay(500);
  digitalWrite(trig, LOW);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 28.5;

  lcd.clear();
  lcd.setCursor(0, 0);

if (distance < 10) {
    // Alarm 1: Rapid beeping
    digitalWrite(LED1, HIGH);
    lcd.print("TOO CLOSE");

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
}

else if (distance >= 10 && distance <= 25) {
    // Alarm 2: Slow beeping
    digitalWrite(LED2, HIGH);
    lcd.print("CLOSE");

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(300);
}

else if (distance > 25 && distance < 75) {
    digitalWrite(LED3, HIGH);
    lcd.print("YOU HAVE SPACE");

    digitalWrite(buzzer, HIGH);   // No alarm
    delay(100);
    digitalWrite(buzzer, LOW);   // No alarm
    delay(1000);
}

else {
    digitalWrite(LED4, HIGH);
    lcd.print("OPEN");

    digitalWrite(buzzer, LOW);   // No alarm
}


  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");

  Serial.println(distance);

  

}
