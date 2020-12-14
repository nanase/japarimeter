#ifndef __C_IMAGE_H
#define __C_IMAGE_H

#include "stdint.h"

typedef struct {
  uint16_t size;
  const uint8_t *data;
} CImage;

void cImage_write(const CImage *image);
void cImage_writeSlide(const CImage *image, uint8_t slide);

#endif
