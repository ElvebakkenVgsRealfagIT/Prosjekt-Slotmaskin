#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "SlowSoftI2CMaster.h"


SlowSoftI2CMaster sw(A0, A1, true); // Bruk A0 og A1 som SDA og SCL-porter

hd44780_I2Cexp lcd(0x27, 16, 2);  // Addresse, kolonner, rader
hd44780_I2Cexp lcd2(0x32, 16, 2); // TODO: finn addresse 2



int sekunder;

void setup() {
  sekunder = 0;
  lcd.begin(16, 2);    // Starter LCDen
  lcd.clear();         // LCD.clear() tømmer skjermen og syncer den med arduinoen
  lcd.setBacklight(1); // Lyset som gjør teksten hvit
  lcd.print("Hallo!");
}

void loop() {
  lcd.clear();
  lcd.setBacklight(1);
  lcd.print("Hallo!");
  lcd.setCursor(0, 1);
  lcd.print(sekunder);
  delay(500);
  sekunder += 1;
}