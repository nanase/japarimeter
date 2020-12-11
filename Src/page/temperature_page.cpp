#include "bmp280_macros.hpp"
#include "fonts.h"
#include "page.hpp"
#include "ssd1306.h"

extern uint32_t fixed_temperature;
extern char buf[32];

extern const uint8_t image_temperature_icon[118];
extern const uint8_t image_temperature_value[2];

void TemperaturePage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 4);
  ssd1306_writeCompressedImage(image_temperature_icon, sizeof(image_temperature_icon));

  ssd1306_setCursor(116, 11);
  ssd1306_writeString("C", Font_11x18, ssd1306_white);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(112, 8);
  ssd1306_writeString("o", Font_7x10, ssd1306_white);

  ssd1306_setCursor(73, 11);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

void TemperaturePage::draw() {
  const uint8_t NumberYPosition = 5;

  float temperature            = fixedTemperatureToTemperature(fixed_temperature);
  float temperature_icon_value = temperature;

  if (temperature_icon_value > 40.0)
    temperature_icon_value = 40.0;

  if (temperature_icon_value < 0.0)
    temperature_icon_value = 0.0;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(7, 5);
  ssd1306_writeCompressedSlideImage((uint8_t)(17.0 - 17.0 * (temperature_icon_value / 40.0)), image_temperature_value,
                                    sizeof(image_temperature_value));

  if (temperature < 0.0) {
    ssd1306_setCursor(26, NumberYPosition);
    ssd1306_writeString("-", Font_16x26, ssd1306_white);
    temperature *= -1.0;
  }

  ssd1306_setCursor(43, NumberYPosition);
  sprintf(buf, "%2d", (uint8_t)temperature);
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);

  ssd1306_setCursor(80, NumberYPosition);
  sprintf(buf, "%02d", (int8_t)((temperature - (int16_t)temperature) * 100));
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);
}
