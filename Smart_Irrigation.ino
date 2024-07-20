#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Define the pin numbers for pump 1
const int IN1 = 6;
const int IN2 = 7;

// Define the pin numbers for pump 2
const int IN3 = 10;
const int IN4 = 11;

// Define the pin numbers for pump 3
const int IN5 = 8;
const int IN6 = 9;

// Define the pin numbers for pump 4
const int IN7 = 3;
const int IN8 = 4;

void Pump1_on(){
  lcd.setCursor(0, 0);
  lcd.print("Pumping on 1...");
  digitalWrite(IN1, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN2, LOW);    // Set IN2 to LOW
}
void Pump1_off(){
  lcd.setCursor(0, 0);
  lcd.print("No water needed!");
  digitalWrite(IN1, LOW);   // Set IN1 to HIGH
  digitalWrite(IN2, LOW);    // Set IN2 to LOW
}
void Pump2_on(){
  lcd.setCursor(0, 0);
  lcd.print("Pumping on 2...");
  digitalWrite(IN3, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN4, LOW);    // Set IN2 to LOW
}
void Pump2_off(){
  lcd.setCursor(0, 0);
  lcd.print("No water needed!");
  digitalWrite(IN3, LOW);   // Set IN1 to HIGH
  digitalWrite(IN4, LOW);    // Set IN2 to LOW
}
void Pump3_on(){
  lcd.setCursor(0, 0);
  lcd.print("Pumping on 3...");
  digitalWrite(IN5, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN6, LOW);    // Set IN2 to LOW
}
void Pump3_off(){
  lcd.setCursor(0, 0);
  lcd.print("No water needed!");
  digitalWrite(IN5, LOW);   // Set IN1 to HIGH
  digitalWrite(IN6, LOW);    // Set IN2 to LOW
}
void Pump4_on(){
  lcd.setCursor(0, 0);
  lcd.print("Pumping on 4...");
  digitalWrite(IN7, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN8, LOW);    // Set IN2 to LOW
}
void Pump4_off(){
  lcd.setCursor(0, 0);
  lcd.print("No water needed!");
  digitalWrite(IN7, LOW);   // Set IN1 to HIGH
  digitalWrite(IN8, LOW);    // Set IN2 to LOW
}


int soilMoisture = A0;

void setup() {
  Serial.begin(9600);
  pinMode(soilMoisture, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, i);
    lcd.print(".");
    delay(500); // Add a delay to show the dots one by one
  }
};

void loop() {

  int soilMoistData = analogRead(soilMoisture);
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);


  if (soilMoistData > 950) {
    Pump1_on();
    lcd.setCursor(0, 1);
    lcd.print("Dry > Motor ON");
  } else if(soilMoistData >= 400 && soilMoistData <= 950) {
    Pump1_on();
    lcd.setCursor(0, 1);
    lcd.print("Moist > Motor OFF");
  } else if(soilMoistData < 400 ) {
    Pump1_off();
    lcd.setCursor(0, 1);
    lcd.print("Wet > Motor OFF");
  }

  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("Temperature: " + String(f) + "°F");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(h) + "%");

  delay(500);

}