#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "LEDUtils.h"

class Gaming_ : public kaleidoscope::Plugin {
public:
  Gaming_(void) {}

  static uint8_t gamingLayer;
  static cRGB color;
  static cRGB highlightColor;
  static uint8_t lock_hue;

  kaleidoscope::EventHandlerResult onSetup(void);
  kaleidoscope::EventHandlerResult afterEachCycle();

#if KALEIDOSCOPE_ENABLE_V1_PLUGIN_API
protected:
  void begin();
  static void legacyLoopHook(bool is_post_clear);
#endif

private:
  static byte row, col;
  static bool cleanupDone;
  static bool originalNumLockState;
};

extern Gaming_ Gaming;
