#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

const int sensorPin = A0;
const int ledPin = 13;
const int threshold = 260;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  lcd.init();          
  lcd.backlight();     
  
  lcd.setCursor(0, 0); 
  lcd.print("Wind Generator");
  lcd.setCursor(0, 1); 
  lcd.print("System Check...");
  delay(1500);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  float voltage = sensorValue * (5.0 / 1023.0);
  
  int percent = map(sensorValue, 0, 1023, 0, 100);

  bool isLedOn = false;
  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH);
    isLedOn = true;
  } else {
    digitalWrite(ledPin, LOW);
    isLedOn = false;
  }

  lcd.setCursor(0, 0); 
  lcd.print("V:"); 
  lcd.print(voltage, 1);
  lcd.print("v  ");     
  
  lcd.print("Bat:"); 
  lcd.print(percent);
  lcd.print("% ");

  lcd.setCursor(0, 1); 
  lcd.print("Light: ");
  if(isLedOn) {
    lcd.print("ON [X]");
  } else {
    lcd.print("OFF[ ]");
  }

  delay(300);
}