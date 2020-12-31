#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"
#include "japarimeter/version.h"

extern char buf[32];

void Version2Page::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(0, 0);
  cFont_writeString(&font_7x10, "Manual:");

  ssd1306_setCursor(0, 11);
  cFont_writeString(&font_7x10, SUPPORT_SITE);
}

bool Version2Page::draw() {
  return false;
}
