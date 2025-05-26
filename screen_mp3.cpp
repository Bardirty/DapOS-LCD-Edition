#include "screen_mp3.h"
#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>

static int track = 1;
static int volume = 10;
static bool playing = true;
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

  unsigned long now = millis();

  if (!initialized) {
    mp3Serial.begin(9600);
    if (mp3.begin(mp3Serial)) {
      mp3.volume(volume);
      mp3.play(track);
    }
    lcd.clear();
    initialized = true;
  }

  bool fn = !digitalRead(6);

  if (digitalRead(7) == HIGH && playing) {
    track = (track >= maxTrack) ? 1 : track + 1;
    mp3.play(track);
    delay(200);
  }

  if (now - lastPress > 200) {
    if (!digitalRead(2) && fn && volume > 0) {
      volume--;
      mp3.volume(volume);
      lastPress = now;
      delay(200);
    } else if (!digitalRead(3) && fn && volume < maxVolume) {
      volume++;
      mp3.volume(volume);
      lastPress = now;
      delay(200);
    } else if (!digitalRead(2)) {
      track = (track <= 1) ? maxTrack : track - 1;
      mp3.play(track);
      lastPress = now;
      delay(200);
    } else if (!digitalRead(3)) {
      track = (track >= maxTrack) ? 1 : track + 1;
      mp3.play(track);
      lastPress = now;
      delay(200);
    } else if (!digitalRead(4)) {
      playing = !playing;
      playing ? mp3.play(track) : mp3.pause();
      lastPress = now;
      delay(200);
    }
  }

  if (track != lastTrack || playing != lastPlaying) {
    lcd.setCursor(0, 0);
    lcd.print(playing ? "PLAY " : "PAUSE");
    lcd.print("trk:");
    if (track < 10) lcd.print(" ");
    lcd.print(track);
    lcd.print("  ");
    lastTrack = track;
    lastPlaying = playing;
  }

  if (volume != lastVolume) {
    lcd.setCursor(0, 1);
    lcd.print("vol:");
    if (volume < 10) lcd.print(" ");
    lcd.print(volume);
    lcd.print("     ");
    lastVolume = volume;
  }
}
