#include "bmp280_macros.hpp"
#include "c_image.h"
#include "fonts.h"
#include "page.hpp"
#include "ssd1306.h"

extern uint32_t fixed_humidity;
extern char buf[32];

extern const CImage image_humidity_icon;
extern const CImage image_humidity_value;

void HumidityPage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(8, 4);
  cImage_write(&image_humidity_icon);

  ssd1306_setCursor(116, 11);
  ssd1306_writeString("%", Font_11x18, ssd1306_white);

  ssd1306_setCursor(73, 11);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

bool HumidityPage::draw() {
  const uint8_t NumberYPosition = 5;

  float humidity = fixedHumidityToHumidity(fixed_humidity);

  ssd1306_setFillMode(true);
  ssd1306_setCursor(9, 6);
  cImage_writeSlide(&image_humidity_value, (uint8_t)(21.0 - 21.0 * (humidity / 100.0)));

  if (fixed_humidity == BMP280_MAX_HUMIDITY) {
    ssd1306_setCursor(26, NumberYPosition);
    ssd1306_writeString("100", Font_16x26, ssd1306_white);

    ssd1306_setCursor(80, NumberYPosition);
    ssd1306_writeString("00", Font_16x26, ssd1306_white);
  } else {
    ssd1306_setCursor(43, NumberYPosition);
    sprintf(buf, "%2d", (uint8_t)humidity);
    ssd1306_writeString(buf, Font_16x26, ssd1306_white);

    ssd1306_setCursor(80, NumberYPosition);
    sprintf(buf, "%02d", (int8_t)((humidity - (int16_t)humidity) * 100));
    ssd1306_writeString(buf, Font_16x26, ssd1306_white);
  }

  return false;
}
