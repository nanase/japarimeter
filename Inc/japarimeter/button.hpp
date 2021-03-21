#ifndef __BUTTON_H
#define __BUTTON_H

#include <stdint.h>

#include "config/config.h"

class Button {
 public:
  Button();

  uint32_t getLastPressTime();
  bool isPressed();

  bool checkClicked();
  bool checkLongPressed(uint32_t tick);

  void update(uint32_t tick, bool state);

 private:
  uint32_t tick;
  uint32_t lastPressTick;
  bool pressed;
  bool clickUnprocessed;
  bool eventProcessed;
};

#endif
