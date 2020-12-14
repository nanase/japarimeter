#include "bmp280_macros.hpp"
#include "c_image.h"
#include "fonts.h"
#include "page.hpp"
#include "ssd1306.h"

extern uint32_t fixed_pressure;
extern char buf[32];

extern const CImage image_pressure_icon;
extern const CImage image_pressure_value;

void PressurePage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 4);
  cImage_write(&image_pressure_icon);

  ssd1306_setCursor(103, 3);
  ssd1306_writeString("hPa", Font_7x10, ssd1306_white);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(97, 13);
  ssd1306_writeString(".", Font_11x18, ssd1306_white);
}

void PressurePage::draw() {
  float pressure_hpa        = fixedPressureToHectoPa(fixed_pressure);
  float pressure_icon_value = pressure_hpa;

  if (pressure_icon_value > 1025.0)
    pressure_icon_value = 1025.0;

  if (pressure_icon_value < 990.0)
    pressure_icon_value = 990.0;

  pressure_icon_value -= 990.0;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(5, 5);
  cImage_writeSlide(&image_pressure_value, (uint8_t)(12.0 - 12.0 * (pressure_icon_value / 35.0)));

  ssd1306_setFillMode(true);
  ssd1306_setCursor(37, 5);
  sprintf(buf, "%4d", (uint16_t)(pressure_hpa));
  ssd1306_writeString(buf, Font_16x26, ssd1306_white);

  ssd1306_setFillMode(true);
  ssd1306_setCursor(103, 12);
  sprintf(buf, "%02d", (int8_t)((pressure_hpa - (int16_t)pressure_hpa) * 100));
  ssd1306_writeString(buf, Font_11x18, ssd1306_white);
}
