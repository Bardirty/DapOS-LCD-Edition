#include "screen_logo.h"
#include <Arduino.h>

byte squirrel0[8] = {
  B00000,
  B01111,
  B11111,
  B11111,
  B11111,
  B10111,
  B00111,
  B00111
};

byte squirrel1[8] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000
};

byte squirrel2[8] = {
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00111,
  B00011,
  B00001
};

byte squirrel3[8] = {
  B01000,
  B01110,
  B01110,
  B01100,
  B01111,
  B11100,
  B11110,
  B11111
};

/*
  Squirell look
  ..........
  .####.....
  #####.....
  ######....
  ######....
  #.####....
  ..####....
  ..###.....
  ..###.#...
  ..###.###.
  ..###.###.
  ..###.##..
  ..###.####
  ..######..
  ...######.
  ....######
*/
void showSquirrelLogo(LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.createChar(0, squirrel0);
  lcd.createChar(1, squirrel1);
  lcd.createChar(2, squirrel2);
  lcd.createChar(3, squirrel3);

  drawSquirell(6, 150, lcd);
  delay(3000);
  lcd.clear();
  drawSquirell(4, 0, lcd);
  lcd.setCursor(7, 1);
  lcd.print("DapOS");
  delay(3000);
}


void drawSquirell(int offset, int appearingDelay, LiquidCrystal_I2C &lcd) {
  lcd.setCursor(offset, 0);
  lcd.write(byte(0));
  delay(appearingDelay);
  lcd.setCursor(offset + 1, 0);
  lcd.write(byte(1));
  delay(appearingDelay);
  lcd.setCursor(offset, 1);
  lcd.write(byte(2));
  delay(appearingDelay);
  lcd.setCursor(offset + 1, 1);
  lcd.write(byte(3));
}