#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "LEDUtils.h"

class JosefGaming_ : public kaleidoscope::Plugin {
public:
  JosefGaming_(void) {}

  static uint8_t gamingLayer;
  static cRGB color;
  static cRGB highlightColor;
  static uint8_t lock_hue;

  kaleidoscope::EventHandlerResult onSetup(void);
  kaleidoscope::EventHandlerResult afterEachCycle();

private:
  static byte row, col;
  static bool cleanupDone;
  static bool originalNumLockState;
};

extern JosefGaming_ JosefGaming;
