#include "screen_logo.h"
#include <Arduino.h>

// Пользовательские символы для белки (в профиль, разбита на 4 части)
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

  lcd.setCursor(6, 0);
  lcd.write(byte(0));
  delay(150);
  lcd.setCursor(7, 0);
  lcd.write(byte(1));
  delay(150);
  lcd.setCursor(6, 1);
  lcd.write(byte(2));
  delay(150);
  lcd.setCursor(7, 1);
  lcd.write(byte(3));
  delay(3000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Danil OS");
  delay(3000);
}
