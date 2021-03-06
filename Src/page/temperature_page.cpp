#include "japarimeter/bmp280_macros.hpp"
#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"

extern uint32_t fixed_temperature;
extern char buf[32];

extern const CImage image_temperature_icon;
extern const CImage image_temperature_value;

void TemperaturePage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(12, 4);
  cImage_write(&image_temperature_icon);

  ssd1306_setCursor(116, 11);
  cFont_writeString(&font_11x18, "C");

  ssd1306_setFillMode(false);
  ssd1306_setCursor(112, 8);
  cFont_writeString(&font_7x10, "o");

  ssd1306_setCursor(73, 11);
  cFont_writeString(&font_11x18, ".");
}

bool TemperaturePage::draw() {
  const uint8_t NumberYPosition = 5;

  float temperature            = fixedTemperatureToTemperature(fixed_temperature);
  float temperature_icon_value = temperature;

  if (temperature_icon_value > 40.0)
    temperature_icon_value = 40.0;

  if (temperature_icon_value < 0.0)
    temperature_icon_value = 0.0;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(15, 5);
  cImage_writeSlide(&image_temperature_value, (uint8_t)(17.0 - 17.0 * (temperature_icon_value / 40.0)));

  if (temperature < 0.0) {
    ssd1306_setCursor(26, NumberYPosition);
    cFont_writeString(&font_16x26, "-");
    temperature *= -1.0;
  }

  ssd1306_setCursor(43, NumberYPosition);
  sprintf(buf, "%2d", (uint8_t)temperature);
  cFont_writeString(&font_16x26, buf);

  ssd1306_setCursor(80, NumberYPosition);
  sprintf(buf, "%02d", (int8_t)((temperature - (int16_t)temperature) * 100));
  cFont_writeString(&font_16x26, buf);

  return false;
}
