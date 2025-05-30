#include "screen_mp3.h"
#include "screen_volume.h"
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
#include "track_list.h"
#include "pins.h"

static int track = 1;
static int volume = 10;
static bool playing = true;
static bool paused = false;

enum Mode { MODE_TRACK, MODE_VOLUME };
static Mode currentMode = MODE_TRACK;

const int maxVolume = 30;

SoftwareSerial mp3Serial(MP3_RX, MP3_TX);
DFRobotDFPlayerMini mp3;

void initializeMP3Player(LiquidCrystal_I2C &lcd) {
  pinMode(PIN_BUSY, INPUT);
  mp3Serial.begin(9600);
  if (mp3.begin(mp3Serial)) {
    mp3.EQ(DFPLAYER_EQ_NORMAL);
    mp3.volume(volume);
    mp3.play(track);
    playing = true;
    paused = false;
  }

  byte playChar[8] = {
    B00000, B00100, B00110, B00111,
    B00111, B00110, B00100, B00000
  };
  byte pauseChar[8] = {
    B00000, B01010, B01010, B01010,
    B01010, B01010, B01010, B00000
  };
  lcd.createChar(6, playChar);
  lcd.createChar(7, pauseChar);

  lcd.clear();
}

void handleButtons(unsigned long now, unsigned long &lastPress) {
  if (now - lastPress < 200) return;

  if (!digitalRead(2)) {
    if (currentMode == MODE_VOLUME && volume > 0) {
      volume--;
      mp3.volume(volume);
    } else if (currentMode == MODE_TRACK) {
      track = (track <= 1) ? maxTrack : track - 1;
      mp3.play(track);
      playing = true;
      paused = false;
    }
    lastPress = now;

  } else if (!digitalRead(3)) {
    if (currentMode == MODE_VOLUME && volume < maxVolume) {
      volume++;
      mp3.volume(volume);
    } else if (currentMode == MODE_TRACK) {
      track = (track >= maxTrack) ? 1 : track + 1;
      mp3.play(track);
      playing = true;
      paused = false;
    }
    lastPress = now;

  } else if (!digitalRead(4)) {
    if (!paused) {
      mp3.pause();
      paused = true;
    } else {
      mp3.start();
      paused = false;
    }
    lastPress = now;
  }
}

void checkAutoNextTrack() {
  static bool wasBusy = false;
  bool isBusy = digitalRead(PIN_BUSY) == LOW;

  if (currentMode == MODE_TRACK && playing && !paused) {
    if (wasBusy && !isBusy) {
      track = (track >= maxTrack) ? 1 : track + 1;
      mp3.play(track);
    }
    wasBusy = isBusy;
  }
}

void renderVolumeScreen(LiquidCrystal_I2C &lcd) {
  showVolumePanel(lcd, volume, maxVolume);
}

void renderTrackScreen(LiquidCrystal_I2C &lcd, unsigned long now) {
  static int scrollIndex = 0;
  static unsigned long lastScroll = 0;
  const int scrollDelay = 300;

  lcd.setCursor(2, 1);
  lcd.print("|");
  lcd.write(!paused ? 6 : 7);
  lcd.print(" track:");
  if (track < 10) lcd.print("0");
  lcd.print(track);
  lcd.print("|");

  const char* title = trackNames[track];
  int len = strlen(title);
  if (len > 16 && now - lastScroll > scrollDelay) {
    scrollIndex = (scrollIndex + 1) % (len - 15);
    lastScroll = now;
  } else if (len <= 16) {
    scrollIndex = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print(String(title).substring(scrollIndex, scrollIndex + 16));
}

void updateScreenMP3(LiquidCrystal_I2C &lcd) {
  static bool initialized = false;
  static unsigned long lastPress = 0;
  static unsigned long lastModeChange = 0;

  unsigned long now = millis();

  if (!initialized) {
    initializeMP3Player(lcd);
    initialized = true;
  }

  if (now - lastPress > 200 && !digitalRead(6)) {
    currentMode = (currentMode == MODE_TRACK) ? MODE_VOLUME : MODE_TRACK;
    lcd.clear();
    lastPress = now;
    delay(200);
  }
  checkAutoNextTrack();
  handleButtons(now, lastPress);

  if (currentMode == MODE_VOLUME) {
    renderVolumeScreen(lcd);
  } else {
    renderTrackScreen(lcd, now);
  }
}
