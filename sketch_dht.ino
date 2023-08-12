#include <DHT.h>
#include <DHT_U.h>

#include <DHT.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Define pins
#define DHTPIN 2   // DHT11 data pin
#define HC05_RX 8  // Bluetooth module RX pin
#define HC05_TX 9  // Bluetooth module TX pin

// Define DHT type
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Initialize Bluetooth
SoftwareSerial bt(HC05_RX, HC05_TX);
void setup() {
  Serial.begin(9600);
  bt.begin(9600);

  lcd.begin(16, 2);
  
  dht.begin();
}
void loop() {
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();

    if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("% Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

if (!isnan(temperature) && !isnan(humidity)) {
    // Display temperature on LCD
    lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(10, 0);
    lcd.print(11);
    lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
    lcd.setCursor(10, 1);
    lcd.print(22);
    lcd.print("%");
  
if(humidity>60){
  bt.print("Alert! High Humidity: ");
  bt.print(humidity);
  bt.print("%\n");
  }
  else{
    // Send data to Bluetooth
    bt.print("Humidity: ");
    bt.print(humidity);
    bt.print("%\n");
  }

  if(temperature>30 || temperature<20){
  bt.print("Alert! Extereme Temperature: ");
  bt.print(temperature);
  bt.print(" C\n");
  }
  else{
    // Send data to Bluetooth
    bt.print("Temperature: ");
    bt.print(temperature);
    bt.print(" C");
  }

  } else {
    // Display error message on LCD
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring");
    bt.print("Failed");
  }

  delay(2000); // Delay between readings
  lcd.clear();
}
