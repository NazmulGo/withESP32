#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

#define DHTPIN 16
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Welcome Screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 10);
  display.println("DHT11 Sensor Ready");
  display.display();

  dht.begin();
  delay(2000);
}

void loop() {
  // Read sensor
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  // Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | ");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("--- ENVIRONMENT ---");

  if (isnan(humidity) || isnan(temp)) {

    display.setCursor(0, 14);
    display.println("Error: Check Sensor!");

  } else {

    // Temperature 
    display.setCursor(0, 14);
    display.print("Temp: ");
    display.print(temp, 1);
    display.println(" C");

    // Humidity 
    display.setCursor(0, 24);
    display.print("Hum:  ");
    display.print(humidity, 1);
    display.println(" %");
  }

  display.display();

  delay(2000);
}
