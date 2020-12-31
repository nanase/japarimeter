#ifndef __C_FONT_H
#define __C_FONT_H

#include "stdint.h"

typedef struct {
  const char code;
  const uint8_t size;
  const uint8_t *data;
} CGlyph;

typedef struct {
  const uint8_t width;
  const uint8_t height;
  const uint8_t glyphNumber;
  const CGlyph *glyphs;
} CFont;

void cFont_write(const CFont *font, char c);
void cFont_writeString(const CFont *font, const char *str);

extern const CFont font_7x10;
extern const CFont font_11x18;
extern const CFont font_16x26;

#endif
