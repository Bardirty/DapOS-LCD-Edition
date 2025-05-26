#pragma once
#include <LiquidCrystal_I2C.h>
#include "screen_mp3.h"

enum DanilScreen { SCREEN_BOOT, SCREEN_MENU, SCREEN_MP3 };

void updateMenu(LiquidCrystal_I2C &lcd, DanilScreen &currentScreen);
