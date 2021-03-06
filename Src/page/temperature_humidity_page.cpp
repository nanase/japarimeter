#include "japarimeter/bmp280_macros.hpp"
#include "japarimeter/c_font.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"

extern int32_t fixed_temperature;
extern uint32_t fixed_humidity;
extern char buf[32];

void TemperatureHumidityPage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(52, 3);
  cFont_writeString(&font_7x10, "C");
  ssd1306_setFillMode(false);
  ssd1306_setCursor(53, 3);
  cFont_writeString(&font_7x10, "C");
  ssd1306_setCursor(46, 0);
  cFont_writeString(&font_7x10, "o");

  ssd1306_setFillMode(false);
  ssd1306_setCursor(33, 13);
  cFont_writeString(&font_11x18, ".");

  //

  ssd1306_setFillMode(true);
  ssd1306_setCursor(52 + 64, 3);
  cFont_writeString(&font_7x10, "%");

  ssd1306_setFillMode(false);
  ssd1306_setCursor(33 + 64, 13);
  cFont_writeString(&font_11x18, ".");
}

bool TemperatureHumidityPage::draw() {
  float temperature = fixedTemperatureToTemperature(fixed_temperature);
  float humidity    = fixedHumidityToHumidity(fixed_humidity);

  ssd1306_setFillMode(true);
  ssd1306_setCursor(5, 5);
  sprintf(buf, "%2d", (int16_t)temperature);
  cFont_writeString(&font_16x26, buf);

  ssd1306_setCursor(39, 12);
  sprintf(buf, "%02d", (int8_t)((temperature - (int16_t)temperature) * 100));
  cFont_writeString(&font_11x18, buf);

  //

  ssd1306_setFillMode(true);
  ssd1306_setCursor(64 + 5, 5);
  sprintf(buf, "%2d", (uint8_t)humidity);
  cFont_writeString(&font_16x26, buf);

  ssd1306_setCursor(39 + 64, 12);
  sprintf(buf, "%02d", (int8_t)((humidity - (int16_t)humidity) * 100));
  cFont_writeString(&font_11x18, buf);

  return false;
}
