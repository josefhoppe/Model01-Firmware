#include "Gaming.h"
#include "Kaleidoscope.h"
#include "LEDUtils.h"
#include "layers.h"

byte JosefGaming_::row = 255, JosefGaming_::col = 255;
uint8_t JosefGaming_::gamingLayer;
uint8_t JosefGaming_::arrowLayer;
bool JosefGaming_::cleanupDone = true;
bool JosefGaming_::originalNumLockState = false;
cRGB JosefGaming_::color = CRGB(255, 0, 0);
cRGB JosefGaming_::highlightColor = CRGB(0, 0, 255);
cRGB JosefGaming_::arrowColor = CRGB(255, 0, 255);
uint8_t JosefGaming_::lock_hue = 170;

kaleidoscope::EventHandlerResult JosefGaming_::onSetup(void) {
  originalNumLockState =
      !!(kaleidoscope::hid::getKeyboardLEDs() & LED_NUM_LOCK);
  return kaleidoscope::EventHandlerResult::OK;
}

kaleidoscope::EventHandlerResult JosefGaming_::afterEachCycle() {
  if (!Layer.isOn(gamingLayer)) {
    if (!cleanupDone) {
      LEDControl.set_mode(LEDControl.get_mode_index());
      cleanupDone = true;
    }
    return kaleidoscope::EventHandlerResult::OK;
  }

  cleanupDone = false;

  LEDControl.set_mode(LEDControl.get_mode_index());

  for (uint8_t r = 0; r < ROWS; r++) {
    for (uint8_t c = 0; c < COLS; c++) {
      Key k = Layer.lookupOnActiveLayer(r, c);
      Key layer_key = Layer.getKey(gamingLayer, r, c);
      Key arrow_layer_key = Layer.getKey(arrowLayer, r, c);

      if (k == LockLayer(gamingLayer)) {
        row = r;
        col = c;
      }

      if ((k != layer_key) || (k == Key_NoKey) || (k.flags != KEY_FLAGS)) {
        LEDControl.refreshAt(r, c);
      } else {
        if (k == Key_W || k == Key_A || k == Key_S || k == Key_D) {
          LEDControl.setCrgbAt(r, c, highlightColor);
        } else if(k == Key_UpArrow || k == Key_DownArrow || k == Key_RightArrow || k == Key_LeftArrow || k == LockLayer(arrowLayer)) {
          LEDControl.setCrgbAt(r, c, arrowColor);
        } else {
          LEDControl.setCrgbAt(r, c, color);
        }
      }
    }
  }

  if (row > ROWS || col > COLS)
    return kaleidoscope::EventHandlerResult::OK;

  cRGB lock_color = breath_compute(lock_hue);
  LEDControl.setCrgbAt(row, col, lock_color);

  return kaleidoscope::EventHandlerResult::OK;
}

JosefGaming_ JosefGaming;
