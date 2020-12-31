#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"
#include "japarimeter/version.h"

extern char buf[32];

void Version1Page::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(0, 0);
  cFont_writeString(&font_11x18, "JapariMeter");

  ssd1306_setCursor(0, 19);
  sprintf(buf, "v%s / %s", SOFTWARE_VERSION, HARDWARE_VERSION);
  cFont_writeString(&font_7x10, buf);
}

bool Version1Page::draw() {
  return false;
}
