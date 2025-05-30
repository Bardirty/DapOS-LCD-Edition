#include "screen_volume.h"
#include <Arduino.h>

void showVolumePanel(LiquidCrystal_I2C &lcd, int volume, int maxVolume) {
  lcd.setCursor(0, 0);
  lcd.print("  VOLUME  MODE   ");

  lcd.setCursor(2, 1);
  lcd.print("-");

  int bars = map(volume, 0, maxVolume, 0, 10);
  for (int i = 0; i < 10; i++) {
    lcd.write(i < bars ? byte(255) : ' ');
  }

  lcd.print("+");
}
