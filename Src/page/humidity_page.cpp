#include "bmp280_macros.hpp"
#include "fonts.h"
#include "page.hpp"
#include "ssd1306.h"

extern uint32_t fixed_humidity;
extern char buf[32];

extern const uint8_t image_humidity_icon[84];
extern const uint8_t image_humidity_value[36];

void HumidityPage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 4);
  ssd1306_writeCompressedImage(image_humidity_icon, sizeof(image_humidity_icon));

  ssd1306_setCursor(116, 11);
  ssd1306_writeString("%", Font_11x18, ssd1306_white);

  ssd1306_setCursor(73, 11);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

void HumidityPage::draw() {
  const uint8_t NumberYPosition = 5;

  float humidity = fixedHumidityToHumidity(fixed_humidity);

  ssd1306_setFillMode(true);
  ssd1306_setCursor(5, 6);
  ssd1306_writeCompressedSlideImage((uint8_t)(21.0 - 21.0 * (humidity / 100.0)), image_humidity_value,
                                    sizeof(image_humidity_value));

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
}
