#include "japarimeter/bmp280_macros.hpp"
#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"

extern uint32_t fixed_humidity;
extern uint32_t fixed_temperature;
extern char buf[32];

extern const CImage image_di_face1;
extern const CImage image_di_face2;
extern const CImage image_di_face3;
extern const CImage image_di_face4;

void DIPage::drawWholeScreen() {
  ssd1306_setFillMode(true);

  ssd1306_setCursor(73, 11);
  cFont_writeString(&font_11x18, ".");
}

bool DIPage::draw() {
  const uint8_t NumberYPosition = 5;

  float humidity    = fixedHumidityToHumidity(fixed_humidity);
  float temperature = fixedTemperatureToTemperature(fixed_temperature);
  float di          = 0.81 * temperature + 0.01 * humidity * (0.99 * temperature - 14.3) + 46.3;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 4);

  if (di < 70.0) {
    cImage_write(&image_di_face1);
  } else if (di < 75.0) {
    cImage_write(&image_di_face2);
  } else if (di < 80.0) {
    cImage_write(&image_di_face3);
  } else {
    cImage_write(&image_di_face4);
  }

  ssd1306_setFillMode(false);
  ssd1306_setCursor(3, 4);

  if (di < 70.0) {
    cImage_write(&image_di_face1);
  } else if (di < 75.0) {
    cImage_write(&image_di_face2);
  } else if (di < 80.0) {
    cImage_write(&image_di_face3);
  } else {
    cImage_write(&image_di_face4);
  }

  ssd1306_setFillMode(true);
  ssd1306_setCursor(27, NumberYPosition);
  sprintf(buf, "%3d", (uint8_t)di);
  cFont_writeString(&font_16x26, buf);

  ssd1306_setCursor(80, NumberYPosition);
  sprintf(buf, "%02d", (int8_t)((di - (int16_t)di) * 100));
  cFont_writeString(&font_16x26, buf);

  return false;
}
