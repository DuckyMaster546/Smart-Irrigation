#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Define the pin numbers for pump 1
const int IN1 = 13;
const int IN2 = 12;
const int ENA = 9;

const int IN3 = 4;
const int IN4 = 3;
const int ENB = 11;

int redPin = A2;
int greenPin = A3;

void Pump1_on(){
  Serial.println("-----------------------");
  Serial.println("Pumping on 1...");
  digitalWrite(IN1, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN2, LOW);    // Set IN2 to LO
}
void Pump1_off(){
  Serial.println("-----------------------");
  Serial.println("No water needed!");
  digitalWrite(IN1, LOW);   // Set IN1 to HIGH
  digitalWrite(IN2, LOW);    // Set IN2 to LOW
}
void Pump2_on(){
  Serial.println("-----------------------");
  Serial.println("Pumping on 2...");
  digitalWrite(IN3, HIGH);   // Set IN1 to HIGH
  digitalWrite(IN4, LOW);    // Set IN2 to LOW
}
void Pump2_off(){
  Serial.println("-----------------------");
  Serial.println("No water needed!");
  digitalWrite(IN3, LOW);   // Set IN1 to HIGH
  digitalWrite(IN4, LOW);    // Set IN2 to LOW
}
// void Pump3_on(){
//   Serial.println("-----------------------");
//   Serial.println("Pumping on 3...");
//   digitalWrite(IN5, HIGH);   // Set IN1 to HIGH
//   digitalWrite(IN6, LOW);    // Set IN2 to LOW
// }
// void Pump3_off(){
//   Serial.println("-----------------------");
//   Serial.println("No water needed!");
//   digitalWrite(IN5, LOW);   // Set IN1 to HIGH
//   digitalWrite(IN6, LOW);    // Set IN2 to LOW
// }
// void Pump4_on(){
//   Serial.println("-----------------------");
//   Serial.println("Pumping on 4...");
//   digitalWrite(IN7, HIGH);   // Set IN1 to HIGH
//   digitalWrite(IN8, LOW);    // Set IN2 to LOW
// }
// void Pump4_off(){
//   Serial.println("-----------------------");
//   Serial.println("No water needed!");
//   digitalWrite(IN7, LOW);   // Set IN1 to HIGH
//   digitalWrite(IN8, LOW);    // Set IN2 to LOW
// }

void setColor(int red, int green) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
}

int soilMoisture = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(soilMoisture, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // pinMode(IN5, OUTPUT);
  // pinMode(IN6, OUTPUT);
  // pinMode(IN7, OUTPUT);
  // pinMode(IN8, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.println("Setup is running");
  digitalWrite(ENA, HIGH);
  delay(800);
};

float hif;

void loop() {  

  int soilMoistData = analogRead(soilMoisture);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if (soilMoistData > 950) {
    Pump1_on();
    setColor(255, 0);
    Serial.println("Dry > Motor ON");
    Serial.println("-----------------------");
  } else if(soilMoistData >= 400 && soilMoistData <= 950) {
    Pump1_on();
    setColor(255, 0);
    Serial.println("Moist > Motor ON");
    Serial.println("-----------------------");
  } else if(soilMoistData < 400 ) {
    Pump1_on();
    setColor(255, 0);
    Serial.println("Wet > Motor ON");
    Serial.println("-----------------------");
  }

  delay(500);

  Serial.println("----------MORE INFO-------------");
  Serial.println("Temperature: " + String(f) + "°F");
  Serial.println("Humidity: " + String(h) + "%");
  Serial.println("-----------------------");


  delay(2000);

}