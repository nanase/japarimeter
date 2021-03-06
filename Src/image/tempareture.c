#include "japarimeter/c_image.h"
#include "stdint.h"

static const uint8_t image_temperature_icon_data[59] = {
  0x24, 0x61, 0x41, 0x13, 0x11, 0x41, 0x51, 0x41, 0x12, 0x21, 0x41, 0x51, 0x41, 0x12, 0x21,
  0x41, 0x51, 0x41, 0x12, 0x21, 0x41, 0x51, 0x41, 0x13, 0x11, 0x41, 0x51, 0x41, 0x12, 0x21,
  0x41, 0x51, 0x41, 0x12, 0x21, 0x41, 0x51, 0x41, 0x12, 0x21, 0x41, 0x51, 0x41, 0x14, 0x22,
  0x21, 0x31, 0x14, 0x11, 0x31, 0x14, 0x11, 0x31, 0x22, 0x21, 0x41, 0x41, 0x64, 0x50,
};

static const uint8_t image_temperature_value_data[3] = {
  0x0f,
  0x0f,
  0x04,
};

const CImage image_temperature_icon  = { 59, 11, image_temperature_icon_data };
const CImage image_temperature_value = { 3, 2, image_temperature_value_data };
