#include "page.hpp"
#include "ssd1306.h"
#include "fonts.h"

extern float pressure;
extern char buf[32];

void PressurePage::drawWholeScreen()
{
  ssd1306_setFillMode(true);
  ssd1306_setCursor(103, 3);
  ssd1306_writeString("hPa", Font_7x10, ssd1306_white);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(97, 13);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

void PressurePage::draw()
{
  float pressure_hpa = pressure / 100.0;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(37, 5);
  sprintf(buf, "%04d", (uint16_t)(pressure_hpa));
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);

  ssd1306_setFillMode(true);
  ssd1306_setCursor(103, 12);
  sprintf(buf, "%02d", (int8_t)((pressure_hpa - (int16_t)pressure_hpa) * 100));
  ssd1306_writeString(buf, Font_11x18, ssd1306_white);
}
