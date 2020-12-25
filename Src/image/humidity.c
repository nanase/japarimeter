#include "c_image.h"
#include "stdint.h"

static const uint8_t image_humidity_icon_data[42] = {
  0x72, 0xe2, 0xd1, 0x21, 0xc1, 0x21, 0xb1, 0x41, 0xa1, 0x41, 0x91, 0x61, 0x81, 0x61,
  0x71, 0x81, 0x61, 0x81, 0x51, 0xa1, 0x41, 0xa1, 0x31, 0xc1, 0x21, 0xc1, 0x11, 0xe2,
  0xe2, 0xe2, 0xe2, 0xe1, 0x11, 0xc1, 0x21, 0xc1, 0x31, 0xa1, 0x52, 0x62, 0x86, 0x50,
};

static const uint8_t image_humidity_value_data[22] = {
  0x62, 0xc2, 0xb4, 0xa4, 0x96, 0x86, 0x78, 0x68, 0x5a, 0x4a, 0x3c,
  0x2c, 0x1f, 0x0f, 0x0f, 0x0f, 0x0a, 0x1c, 0x2c, 0x3a, 0x66, 0x40,
};

const CImage image_humidity_icon  = { 42, 16, image_humidity_icon_data };
const CImage image_humidity_value = { 22, 14, image_humidity_value_data };
