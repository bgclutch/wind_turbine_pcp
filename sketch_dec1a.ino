#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

const int lightPin = A2;
const int batteryPin = A1;
const int ledPin = 13;

const int threshold = 400;
const float dividerRatio = 3.0; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(lightPin, INPUT);
  pinMode(batteryPin, INPUT);

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
  int lightValue = analogRead(lightPin);
  int voltRaw = analogRead(batteryPin);
  Serial.println(lightValue);
  Serial.println(voltRaw);
  Serial.println();
  
  float voltage = ((float)voltRaw / 1023.0) * 5 * dividerRatio;
  
  int percent = map(voltage * 100, 1100, 1450, 0, 100);
  
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;

  bool isLedOn = false;
  if (lightValue > threshold) {
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