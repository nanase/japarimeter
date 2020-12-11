#include "page.hpp"

#include "fonts.h"
#include "ssd1306.h"

void Page::initialize() {
  ssd1306_fill(ssd1306_black);
  this->drawWholeScreen();
  this->update();
}

void Page::update() {
  this->draw();
  ssd1306_updateScreen();
}
