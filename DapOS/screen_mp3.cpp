#include "screen_mp3.h"
#include "screen_volume.h"
#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>

static int track = 1;
static int volume = 10;
static bool playing = true;

enum Mode { MODE_TRACK, MODE_VOLUME };
static Mode currentMode = MODE_TRACK;

const int maxTrack = 10;
const int maxVolume = 30;

SoftwareSerial mp3Serial(10, 11);
DFPlayerMini_Fast mp3;

void updateScreenMP3(LiquidCrystal_I2C &lcd) {
  static bool initialized = false;
  static unsigned long lastPress = 0;
  static int lastTrack = -1;
  static int lastVolume = -1;
  static bool lastPlaying = !playing;
  static Mode lastMode = MODE_TRACK;

  unsigned long now = millis();

  if (!initialized) {
    mp3Serial.begin(9600);
    if (mp3.begin(mp3Serial)) {
      mp3.volume(volume);
      mp3.play(track);
    }
    lcd.clear();
    initializeVolumeChars(lcd);  // ← Инициализация блоков
    initialized = true;
  }

  // Переключение режима FN
  if (now - lastPress > 200 && !digitalRead(6)) {
    currentMode = (currentMode == MODE_TRACK) ? MODE_VOLUME : MODE_TRACK;
    lcd.clear();
    lastPress = now;
    delay(200);
  }

  // Управление кнопками
  if (now - lastPress > 200) {
    if (!digitalRead(2)) {
      if (currentMode == MODE_VOLUME && volume > 0) {
        volume--;
        mp3.volume(volume);
      } else if (currentMode == MODE_TRACK) {
        track = (track <= 1) ? maxTrack : track - 1;
        mp3.play(track);
      }
      lastPress = now;
    } else if (!digitalRead(3)) {
      if (currentMode == MODE_VOLUME && volume < maxVolume) {
        volume++;
        mp3.volume(volume);
      } else if (currentMode == MODE_TRACK) {
        track = (track >= maxTrack) ? 1 : track + 1;
        mp3.play(track);
      }
      lastPress = now;
    } else if (!digitalRead(4)) {
      playing = !playing;
      playing ? mp3.play(track) : mp3.pause();
      lastPress = now;
    }
  }

  // Вывод
  if (currentMode == MODE_VOLUME) {
    showVolumePanel(lcd, volume, maxVolume);
  } else if (track != lastTrack || playing != lastPlaying || currentMode != lastMode) {
    lcd.setCursor(0, 0);
    lcd.print(playing ? "PLAY " : "PAUSE");
    lcd.print("trk:");
    if (track < 10) lcd.print(" ");
    lcd.print(track);
    lcd.print("   ");

    lcd.setCursor(0, 1);
    lcd.print("FN = Volume Mode");

    lastTrack = track;
    lastPlaying = playing;
    lastMode = currentMode;
  }

  if (currentMode == MODE_TRACK)
    lastVolume = -1;  // Сброс, чтобы показать панель при возврате
}
