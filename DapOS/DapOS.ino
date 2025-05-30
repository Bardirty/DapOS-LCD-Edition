#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "screen_logo.h"
#include "screen_mp3.h"
#include "screen_menu.h"
#include "pins.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
DapScreen currentScreen = SCREEN_BOOT;

void setup() {
  lcd.begin();
  lcd.backlight();

  pinMode(PIN_PREV, INPUT_PULLUP);
  pinMode(PIN_NEXT, INPUT_PULLUP);
  pinMode(PIN_ENTER, INPUT_PULLUP);
  pinMode(PIN_FN, INPUT_PULLUP);

  pinMode(PIN_HEADPHONES, INPUT_PULLUP);
  pinMode(PIN_AUDIO_EN, OUTPUT);


  showSquirrelLogo(lcd);
  currentScreen = SCREEN_MENU;
}

void loop() {
  if (digitalRead(PIN_HEADPHONES) == LOW) {
    digitalWrite(PIN_AUDIO_EN, LOW);
  } else {
    digitalWrite(PIN_AUDIO_EN, HIGH);
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
