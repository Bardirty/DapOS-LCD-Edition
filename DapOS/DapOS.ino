#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "screen_logo.h"
#include "screen_mp3.h"
#include "screen_menu.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
DapScreen currentScreen = SCREEN_BOOT;

void setup() {
  lcd.begin();
  lcd.backlight();

  pinMode(2, INPUT_PULLUP); // prev
  pinMode(3, INPUT_PULLUP); // next
  pinMode(4, INPUT_PULLUP); // play/pause / enter
  pinMode(5, INPUT_PULLUP); // back
  pinMode(6, INPUT_PULLUP); // fn

  pinMode(8, INPUT_PULLUP); // детекция наушников
  pinMode(9, OUTPUT);

  showSquirrelLogo(lcd);
  currentScreen = SCREEN_MENU;
}

void loop() {
  if (digitalRead(8) == LOW) {
    digitalWrite(9, LOW); // отключаем динамик
  } else {
    digitalWrite(9, HIGH); // включаем или тестовый сигнал
  }
  if (!digitalRead(5)) {
    currentScreen = SCREEN_MENU;
    delay(250);
  }

  switch (currentScreen) {
    case SCREEN_MENU:
      updateMenu(lcd, currentScreen);
      break;
    case SCREEN_MP3:
      updateScreenMP3(lcd);
      break;
  }
}
