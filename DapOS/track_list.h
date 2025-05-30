#pragma once

const int maxTrack = 10;

const char* trackNames[maxTrack + 1] = {
  "", // Required placeholder: DFPlayer uses 1-based indexing, so element 0 is unused.
  // Unfortunately, DFPlayer doesn't support listing files directly from the SD card.
  // Therefore, we need to manually initialize track names with every update.
};


