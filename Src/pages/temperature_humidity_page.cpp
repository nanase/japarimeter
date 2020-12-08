#include "page.hpp"
#include "ssd1306.h"
#include "fonts.h"

extern float pressure, temperature, humidity;
extern char buf[32];

void TemperatureHumidityPage::drawWholeScreen()
{
  ssd1306_setFillMode(true);
  ssd1306_setCursor(52, 3);
  ssd1306_writeString("C", Font_7x10, ssd1306_white);
  ssd1306_setFillMode(false);
  ssd1306_setCursor(53, 3);
  ssd1306_writeString("C", Font_7x10, ssd1306_white);
  ssd1306_setCursor(46, 0);
  ssd1306_writeString("o", Font_7x10, ssd1306_white);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(33, 13);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);

  //

  ssd1306_setFillMode(true);
  ssd1306_setCursor(52 + 64, 3);
  ssd1306_writeString("%", Font_7x10, ssd1306_white);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(33 + 64, 13);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

void TemperatureHumidityPage::draw()
{
  ssd1306_setFillMode(true);
  ssd1306_setCursor(5, 5);
  sprintf(buf, "%2d", (int16_t)temperature);
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);

  ssd1306_setCursor(39, 12);
  sprintf(buf, "%02d", (int8_t)((temperature - (int16_t)temperature) * 100));
  ssd1306_writeString(buf, Font_11x18, ssd1306_white);

  //

  ssd1306_setFillMode(true);
  ssd1306_setCursor(64 + 5, 5);
  sprintf(buf, "%2d", (uint8_t)humidity);
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);

  ssd1306_setCursor(39 + 64, 12);
  sprintf(buf, "%02d", (int8_t)((humidity - (int16_t)humidity) * 100));
  ssd1306_writeString(buf, Font_11x18, ssd1306_white);
}
