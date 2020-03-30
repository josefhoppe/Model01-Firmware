#include "Gaming.h"
#include "Kaleidoscope.h"

uint8_t JosefGaming_::gamingLayer;
uint8_t JosefGaming_::arrowLayer;
bool JosefGaming_::gamingWasActive = false;
bool JosefGaming_::arrowWasActive = false;
KeyAddr JosefGaming_::gamingLowlight[GAMING_LOWLIGHT_COUNT];
uint8_t JosefGaming_::gamingLowlightCount = 0;
KeyAddr JosefGaming_::gamingHighlight[GAMING_HIGHLIGHT_COUNT];
uint8_t JosefGaming_::gamingHighlightCount = 0;
KeyAddr JosefGaming_::arrowHighlight[ARROW_HIGHLIGHT_COUNT];
uint8_t JosefGaming_::arrowHighlightCount = 0;
cRGB JosefGaming_::color = CRGB(255, 0, 0);
cRGB JosefGaming_::highlightColor = CRGB(0, 0, 255);
cRGB JosefGaming_::arrowColor = CRGB(255, 0, 255);
uint8_t JosefGaming_::lock_hue = 170;

void JosefGaming_::scan() {
  for (auto key_addr : KeyAddr::all()) {
    Key gaming_layer_key = Layer.getKey(gamingLayer, key_addr);
    Key arrow_layer_key = Layer.getKey(arrowLayer, key_addr);
    Key k = Layer.getKey(0, key_addr);

    if (k == LockLayer(gamingLayer)) {
      gamingHighlight[gamingHighlightCount] = key_addr;
      gamingHighlightCount++;
    }

    if (k == LockLayer(arrowLayer)) {
      arrowHighlight[arrowHighlightCount] = key_addr;
      arrowHighlightCount++;
    }

    if(gaming_layer_key != Key_NoKey && gaming_layer_key != Key_Transparent) {
      if (gaming_layer_key == Key_W || gaming_layer_key == Key_A || gaming_layer_key == Key_S || gaming_layer_key == Key_D) {
        if(gamingHighlightCount < GAMING_HIGHLIGHT_COUNT) {
          gamingHighlight[gamingHighlightCount] = key_addr;
          gamingHighlightCount++;
        }
      } else {
        if(gamingLowlightCount < GAMING_LOWLIGHT_COUNT) {
          gamingLowlight[gamingLowlightCount] = key_addr;
          gamingLowlightCount++;
        }
      }
    }

    if(arrow_layer_key != Key_NoKey && arrow_layer_key != Key_Transparent && arrowHighlightCount < ARROW_HIGHLIGHT_COUNT) {
      if(arrow_layer_key == Key_UpArrow || arrow_layer_key == Key_DownArrow || arrow_layer_key == Key_RightArrow || arrow_layer_key == Key_LeftArrow) {
          arrowHighlight[arrowHighlightCount] = key_addr;
          arrowHighlightCount++;
      }
    }
  }
}

kaleidoscope::EventHandlerResult JosefGaming_::onSetup(void) {
  return kaleidoscope::EventHandlerResult::OK;
}

kaleidoscope::EventHandlerResult JosefGaming_::afterEachCycle() {
  bool gamingIsActive = Layer.isActive(gamingLayer);
  bool arrowIsActive = Layer.isActive(arrowLayer);

  if(gamingIsActive != gamingWasActive || arrowIsActive != arrowWasActive) {
    LEDControl.set_mode(LEDControl.get_mode_index());
  }

  gamingWasActive = gamingIsActive;
  arrowWasActive = arrowIsActive;

  if(gamingIsActive) {
    for(uint8_t i = 0; i < gamingHighlightCount; i++) {
      LEDControl.setCrgbAt(gamingHighlight[i], highlightColor);
    }
    for(uint8_t i = 0; i < gamingLowlightCount; i++) {
      LEDControl.setCrgbAt(gamingLowlight[i], color);
    }
  }

  if(arrowIsActive) {
    for(uint8_t i = 0; i < arrowHighlightCount; i++) {
      LEDControl.setCrgbAt(arrowHighlight[i], arrowColor);
    }
  }

  return kaleidoscope::EventHandlerResult::OK;
}

JosefGaming_ JosefGaming;
