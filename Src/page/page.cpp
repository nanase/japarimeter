#include "japarimeter/page.hpp"

#include "japarimeter/ssd1306.h"

void Page::initialize() {
  ssd1306_fill(ssd1306_black);
  this->drawWholeScreen();
  this->update();
}

bool Page::update() {
  bool nextPage = this->draw();
  ssd1306_updateScreen();

  return nextPage;
}
