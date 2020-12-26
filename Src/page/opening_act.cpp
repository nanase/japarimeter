#include "c_font.h"
#include "c_image.h"
#include "page.hpp"
#include "ssd1306.h"

extern const CImage image_logo;

void OpeningActPage::drawWholeScreen() {
  ssd1306_setCursor(0, 0);
  cImage_write(&image_logo);
}

bool OpeningActPage::draw() {
  static uint8_t count = 0;

  if (count < 8)
    count++;

  return count >= 8;
}
