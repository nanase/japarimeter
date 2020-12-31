#include "japarimeter/bmp280_macros.hpp"
#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page.hpp"
#include "japarimeter/ssd1306.h"

extern uint32_t fixed_pressure;
extern char buf[32];

extern const CImage image_altitude_icon;
extern const CImage image_altitude_value;

float sqrt2(float x) {
  float a = x;

  for (uint8_t i = 0; i < 8; i++) { a = (a * a + x) / (2.0 * a); }

  return a;
}

float sqrt4(float x) {
  float a = x;

  for (uint8_t i = 0; i < 16; i++) { a = (3.0 * a) / 4.0 + x / (4.0 * a * a * a); }

  return a;
}

float sqrt8(float x) {
  float a = x;

  for (uint8_t i = 0; i < 24; i++) { a = (7.0 * a) / 8.0 + x / (8.0 * a * a * a * a * a * a * a); }

  return a;
}

float pow1902(float x) {
  float p8    = sqrt8(x);
  float p16   = sqrt2(p8);
  float p512  = sqrt8(sqrt4(p16));
  float p2048 = sqrt4(p512);

  return p8 * p16 * p512 * p2048 * sqrt2(p2048);
}

void AltitudePage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 4);
  cImage_write(&image_altitude_icon);

  ssd1306_setCursor(114, -3);
  cFont_writeString(&font_11x18, "m");

  ssd1306_setFillMode(false);
  ssd1306_setCursor(97, 13);
  cFont_writeString(&font_11x18, ".");
}

bool AltitudePage::draw() {
  float pressure_hpa = fixedPressureToHectoPa(fixed_pressure);

  if (pressure_hpa >= 460.0) {
    // ref: altitude = -44330.77 * (pow(pressure_hpa / 1013.25, 0.190263) - 1.0);
    float altitude = -44330.77 * (pow1902(pressure_hpa / 1013.25) - 1.0);
    float altitude_icon;

    if (altitude < 0.0) {
      altitude      = 0.0;
      altitude_icon = 0.0;
    } else if (altitude > 2000.0)
      altitude_icon = 2000.0;
    else if (altitude > 9999.99) {
      altitude      = 9999.99;
      altitude_icon = 2000.0;
    } else
      altitude_icon = altitude;

    ssd1306_setFillMode(true);
    ssd1306_setCursor(5, 10);
    cImage_writeSlide(&image_altitude_value, (uint8_t)(15.0 - 15.0 * (altitude_icon / 2000.0)));

    ssd1306_setCursor(37, 5);
    sprintf(buf, "%4d", (uint16_t)altitude);
    cFont_writeString(&font_16x26, buf);

    ssd1306_setCursor(103, 12);
    sprintf(buf, "%02d", (int16_t)((altitude - (int16_t)altitude) * 100));
    cFont_writeString(&font_11x18, buf);
  } else {
    ssd1306_setFillMode(true);
    ssd1306_setCursor(5, 10);
    cImage_writeSlide(&image_altitude_value, 0);

    ssd1306_setCursor(37, 5);
    cFont_writeString(&font_16x26, "----");

    ssd1306_setCursor(103, 12);
    cFont_writeString(&font_11x18, "--");
  }

  return false;
}
