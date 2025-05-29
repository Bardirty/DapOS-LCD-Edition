#pragma once
#include <LiquidCrystal_I2C.h>

void showVolumePanel(LiquidCrystal_I2C &lcd, int volume, int maxVolume);
void initializeVolumeChars(LiquidCrystal_I2C &lcd);
