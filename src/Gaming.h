#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"


#define GAMING_LOWLIGHT_COUNT 20
#define GAMING_HIGHLIGHT_COUNT 6
#define ARROW_HIGHLIGHT_COUNT 6

class JosefGaming_ : public kaleidoscope::Plugin {
public:
  JosefGaming_(void) {}

  static uint8_t gamingLayer;
  static uint8_t arrowLayer;
  static cRGB color;
  static cRGB highlightColor;
  static cRGB arrowColor;
  static uint8_t lock_hue;

  kaleidoscope::EventHandlerResult onSetup(void);
  kaleidoscope::EventHandlerResult afterEachCycle();
  void scan();

private:
  static bool gamingWasActive;
  static bool arrowWasActive;
  static KeyAddr gamingLowlight[GAMING_LOWLIGHT_COUNT];
  static uint8_t gamingLowlightCount;
  static KeyAddr gamingHighlight[GAMING_HIGHLIGHT_COUNT];
  static uint8_t gamingHighlightCount;
  static KeyAddr arrowHighlight[ARROW_HIGHLIGHT_COUNT];
  static uint8_t arrowHighlightCount;
};

extern JosefGaming_ JosefGaming;
