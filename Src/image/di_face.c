#include "japarimeter/c_image.h"
#include "stdint.h"

static const uint8_t image_di_face1_data[66] = {
  0xf0, 0xf0, 0xf0, 0xc6, 0xf0, 0x12, 0x62, 0xc2, 0xa2, 0x91, 0xe1, 0x81, 0xe1, 0x71, 0x41, 0x61, 0x41,
  0x61, 0x41, 0x61, 0x41, 0x51, 0x51, 0x61, 0x51, 0x41, 0x51, 0x61, 0x51, 0x41, 0xf0, 0x31, 0x41, 0xf0,
  0x31, 0x41, 0xf0, 0x31, 0x41, 0xf0, 0x31, 0x51, 0x31, 0x81, 0x31, 0x61, 0x31, 0x81, 0x31, 0x71, 0x31,
  0x61, 0x31, 0x81, 0x46, 0x41, 0x92, 0xa2, 0xc2, 0x62, 0xf0, 0x16, 0xf0, 0xf0, 0xf0, 0xc0,
};
static const uint8_t image_di_face2_data[62] = {
  0xf0, 0xf0, 0xf0, 0xc6, 0xf0, 0x12, 0x62, 0xc2, 0xa2, 0x91, 0xe1, 0x81, 0xe1, 0x71, 0x41, 0x61,
  0x41, 0x61, 0x41, 0x61, 0x41, 0x51, 0x51, 0x61, 0x51, 0x41, 0x51, 0x61, 0x51, 0x41, 0xf0, 0x31,
  0x41, 0xf0, 0x31, 0x41, 0xf0, 0x31, 0x41, 0xf0, 0x31, 0x51, 0xf0, 0x11, 0x61, 0xf0, 0x11, 0x71,
  0x46, 0x41, 0x81, 0xe1, 0x92, 0xa2, 0xc2, 0x62, 0xf0, 0x16, 0xf0, 0xf0, 0xf0, 0xc0,
};
static const uint8_t image_di_face3_data[69] = {
  0xf0, 0xf0, 0xf0, 0xc6, 0xc1, 0x32, 0x62, 0xa1, 0x12, 0xa2, 0x71, 0x11, 0xe1, 0x61, 0x11, 0xe1, 0x51, 0x31,
  0x21, 0x61, 0x41, 0x41, 0x31, 0x21, 0x61, 0x41, 0x41, 0x31, 0x21, 0x61, 0x51, 0x43, 0x31, 0x61, 0x51, 0x41,
  0xf0, 0x31, 0x41, 0xf0, 0x31, 0x41, 0xf0, 0x31, 0x41, 0xf0, 0x31, 0x51, 0xf0, 0x11, 0x61, 0x56, 0x51, 0x71,
  0x31, 0x61, 0x31, 0x81, 0xe1, 0x92, 0xa2, 0xc2, 0x62, 0xf0, 0x16, 0xf0, 0xf0, 0xf0, 0xc0,
};
static const uint8_t image_di_face4_data[73] = {
  0xf0, 0xf0, 0xf0, 0xc6, 0xc1, 0x32, 0x62, 0xa1, 0x12, 0xa2, 0x71, 0x11, 0xe1, 0x61, 0x11, 0xf1, 0x41, 0x31, 0x21,
  0x61, 0x41, 0x41, 0x31, 0x21, 0x61, 0x31, 0x11, 0x31, 0x31, 0x21, 0x61, 0x31, 0x11, 0x43, 0x31, 0x61, 0x21, 0x31,
  0x31, 0xf1, 0x31, 0x31, 0xf1, 0x31, 0x31, 0xf0, 0x13, 0x41, 0xf0, 0x31, 0x51, 0x56, 0x51, 0x61, 0x41, 0x61, 0x41,
  0x71, 0x21, 0x81, 0x21, 0x81, 0xe1, 0x92, 0xa2, 0xc2, 0x62, 0xf0, 0x16, 0xf0, 0xf0, 0xf0, 0xc0,
};

const CImage image_di_face1 = { 66, 24, image_di_face1_data };
const CImage image_di_face2 = { 62, 24, image_di_face2_data };
const CImage image_di_face3 = { 69, 24, image_di_face3_data };
const CImage image_di_face4 = { 73, 24, image_di_face4_data };