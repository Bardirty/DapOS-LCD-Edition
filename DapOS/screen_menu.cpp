#include "screen_menu.h"
#include <Arduino.h>


void updateMenu(LiquidCrystal_I2C &lcd, DapScreen &currentScreen) {
  static bool firstDraw = true;

  if (firstDraw) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("> MP3 Player");
    lcd.setCursor(0, 1);
    lcd.print("DapOS LCD v1.2");
    firstDraw = false;
  }

  if (!digitalRead(4)) {
    currentScreen = SCREEN_MP3;
    firstDraw = true;
    delay(250);
  }
}
