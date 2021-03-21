#include "japarimeter/button.hpp"

Button::Button() {
  this->tick             = 0;
  this->lastPressTick    = 0;
  this->pressed          = false;
  this->clickUnprocessed = false;
  this->eventProcessed   = false;
}

uint32_t Button::getLastPressTime() {
  return this->lastPressTick;
}

bool Button::isPressed() {
  return this->pressed;
}

bool Button::checkClicked() {
  if (this->clickUnprocessed) {
    this->clickUnprocessed = false;
    this->eventProcessed   = true;
    return true;
  }

  return false;
}

bool Button::checkLongPressed(uint32_t tick) {
  if (!this->pressed)
    return false;

  if (!this->clickUnprocessed) {
    if (tick - this->tick >= BUTTON_LONG_LOW_TIME) {
      this->clickUnprocessed = false;
      this->eventProcessed   = true;
      return true;
    }
  }

  return false;
}

void Button::update(uint32_t tick, bool state) {
  if (state == this->pressed)
    return;

  if (state) {
    // OFF -> ON (HIGH -> LOW)

    if (tick - this->tick < BUTTON_MIN_HIGH_TIME)
      return;

    // press down
    this->pressed          = true;
    this->tick             = tick;
    this->lastPressTick    = tick;
    this->clickUnprocessed = false;
    this->eventProcessed   = false;
  } else {
    // ON -> OFF (LOW -> HIGH)

    if (tick - this->tick < BUTTON_MIN_LOW_TIME)
      return;

    // press up
    this->pressed          = false;
    this->tick             = tick;
    this->clickUnprocessed = !this->eventProcessed;
  }
}
