#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 10;
const int ledLockedPin = 3;
const int ledUnlockedPin = 4;
const int servoPin = 5;

char d;
int pos = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 1);
  lcd.print("Facelocking: on");

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledLockedPin, OUTPUT);
  pinMode(ledUnlockedPin, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(pos);
}

void loop() {
  if (Serial.available()) {
    d = Serial.read();
    if (d == 'a') {
      lcd.setCursor(0, 0);
      lcd.clear();  
      lcd.print("Unlocked");
      lcd.setCursor(0, 1);
      lcd.print("Facelocking: on");

      digitalWrite(ledLockedPin, LOW);
      digitalWrite(ledUnlockedPin, HIGH);

//                    volume, durasi
      tone(buzzerPin, 1000,   1000);
      delay(1000);

      for (pos = 0; pos <= 90; pos += 5) {
        myservo.write(pos);
        delay(20);
      }

      delay(5000);

      for (pos = 90; pos >= 0; pos -= 5) {
        myservo.write(pos);
        delay(20);

        lcd.setCursor(0, 0);
        lcd.clear();  
        lcd.print("locked");
        lcd.setCursor(0, 1);
        lcd.print("Facelocking: on");

        digitalWrite(ledLockedPin, HIGH);
        digitalWrite(ledUnlockedPin, LOW);
      }
      noTone(buzzerPin);

    } 
  }
  d="";
}
