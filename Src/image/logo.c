#include "c_image.h"
#include "stdint.h"

static const uint8_t image_logo_data[370] = {
  0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f,
  0x0f, 0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f,
  0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f, 0x0f,
  0x0f, 0x07, 0xf0, 0xf0, 0xf0, 0xf0, 0x1f, 0x0f, 0x0f, 0x0c, 0x28, 0xf0, 0xf0, 0xf0, 0xf0, 0x13, 0x3f, 0x0f, 0x0f,
  0x05, 0x46, 0x12, 0xa2, 0xf0, 0xf0, 0xf0, 0x23, 0x3f, 0x0f, 0x0f, 0x06, 0x27, 0x13, 0x92, 0xf0, 0x23, 0xf0, 0xc3,
  0x3f, 0x0f, 0x0f, 0x0f, 0x14, 0x73, 0xf0, 0x23, 0xf0, 0xc3, 0x3f, 0x0f, 0x0f, 0x0f, 0x15, 0x54, 0xf0, 0x23, 0xf0,
  0xc3, 0x35, 0x56, 0x21, 0x57, 0x55, 0x23, 0x31, 0x46, 0x15, 0x45, 0x65, 0x47, 0x65, 0x52, 0x33, 0x13, 0x34, 0x84,
  0x95, 0x83, 0x31, 0x41, 0x45, 0x26, 0x35, 0x58, 0x27, 0x58, 0x33, 0x14, 0x13, 0x33, 0xa3, 0xa3, 0xa2, 0x81, 0x45,
  0x27, 0x16, 0x49, 0x28, 0x39, 0x38, 0x13, 0x34, 0x14, 0x43, 0x34, 0x43, 0x14, 0x42, 0x63, 0x44, 0x33, 0x1a, 0x34,
  0x34, 0x33, 0x54, 0x34, 0x26, 0x33, 0x3a, 0x33, 0x34, 0x49, 0x32, 0x45, 0x44, 0x33, 0x25, 0x13, 0x33, 0x53, 0x33,
  0x53, 0x53, 0x24, 0x53, 0x35, 0x83, 0x35, 0x34, 0x82, 0x45, 0x44, 0x33, 0x33, 0x23, 0x3b, 0x33, 0x5b, 0x24, 0x53,
  0x34, 0x93, 0x35, 0x33, 0x92, 0x45, 0x43, 0x43, 0x33, 0x23, 0x3b, 0x33, 0x5b, 0x24, 0x53, 0x33, 0x34, 0x33, 0x34,
  0x42, 0x34, 0x32, 0x45, 0x43, 0x43, 0x83, 0x33, 0xb3, 0x53, 0xa4, 0x53, 0x33, 0x33, 0x43, 0x34, 0x42, 0x33, 0x42,
  0x45, 0x42, 0x53, 0x83, 0x34, 0x52, 0x33, 0x54, 0x52, 0x24, 0x53, 0x33, 0xa3, 0xa3, 0xa2, 0x45, 0x42, 0x53, 0x83,
  0x4a, 0x36, 0x3a, 0x24, 0x51, 0x54, 0x93, 0x95, 0x92, 0x45, 0x41, 0x63, 0x83, 0x58, 0x46, 0x48, 0x34, 0x51, 0x46,
  0x42, 0x23, 0x31, 0x47, 0x42, 0x22, 0x45, 0x41, 0x63, 0x83, 0x75, 0x75, 0x55, 0x44, 0x52, 0x2f, 0x03, 0x3f, 0x0f,
  0x05, 0xf0, 0xf0, 0xf0, 0xf0, 0x8f, 0x07, 0x3f, 0x0f, 0x04, 0xf0, 0xf0, 0xf0, 0xf0, 0x9f, 0x07, 0x3f, 0x0f, 0x03,
  0xf0, 0xf0, 0xf0, 0xf0, 0xaf, 0x07, 0x3f, 0x0f, 0x02, 0xf0, 0xf0, 0xf0, 0xf0, 0xbf, 0x07, 0x3f, 0x0f, 0x01, 0xf0,
  0xf0, 0xf0, 0xf0, 0xcf, 0x0f, 0x0f, 0x0a, 0xf0, 0xf0, 0xf0, 0xf0, 0xdf, 0x0f, 0x0f, 0x09, 0xf0, 0xf0, 0xf0, 0xf0,
  0xef, 0x0f, 0x0f, 0x08, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
};
const CImage image_logo = { 370, 128, image_logo_data };
