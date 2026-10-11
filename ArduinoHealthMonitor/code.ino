#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 2000

LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseOximeter pox;

uint32_t lastReport = 0;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("MAX30100 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(1500);

  if (!pox.begin()) {
    Serial.println("MAX30100 initialization failed!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring");

    while (1) {
      delay(100);
    }
  }

  Serial.println("MAX30100 initialized successfully!");
  Serial.println("Place your finger on the sensor.");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place your");
  lcd.setCursor(0, 1);
  lcd.print("finger on sensor");
}

void loop() {
  pox.update();

  if (millis() - lastReport >= REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // Display on LCD
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Heart: ");
    if (heartRate > 0) {
      lcd.print(heartRate, 0);
      lcd.print(" BPM");
    } else {
      lcd.print("-- BPM");
    }

    lcd.setCursor(0, 1);
    lcd.print("SpO2: ");
    if (spo2 > 0) {
      lcd.print(spo2, 0);
      lcd.print("%");
    } else {
      lcd.print("-- %");
    }

    // Display on Serial Monitor
    Serial.print("Heart Rate: ");
    Serial.print(heartRate, 1);
    Serial.print(" BPM | SpO2: ");
    Serial.print(spo2, 1);
    Serial.println("%");

    lastReport = millis();
  }
}
