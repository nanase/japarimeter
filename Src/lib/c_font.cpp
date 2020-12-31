#include "japarimeter/c_font.h"

#include "japarimeter/ssd1306.h"

extern SSD1306_t SSD1306;

const CGlyph *cFont_getGlyph(const CFont *font, char c) {
  for (uint16_t i = 0; i < font->glyphNumber; i++) {
    if (font->glyphs[i].code == c)
      return &font->glyphs[i];
  }

  return nullptr;
}

void cFont_write(const CFont *font, char c) {
  uint8_t b_count     = 0;
  uint8_t w_count     = 0;
  uint8_t x_cur       = 0;
  uint8_t y_cur       = 0;
  const CGlyph *glyph = cFont_getGlyph(font, c);

  if (glyph == nullptr)
    return;

  for (uint16_t i = 0; i < glyph->size; i++) {
    b_count = glyph->data[i] >> 4;
    w_count = glyph->data[i] & 0x0f;

    for (uint8_t j = 0; j < b_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);
      x_cur++;

      if (x_cur >= font->width) {
        x_cur = 0;
        y_cur++;
      }
    }

    for (uint8_t j = 0; j < w_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_white);
      x_cur++;

      if (x_cur >= font->width) {
        x_cur = 0;
        y_cur++;
      }
    }
  }

  SSD1306.currentX += font->width;
}

void cFont_writeString(const CFont *font, const char *str) {
  while (*str) {
    cFont_write(font, *str);
    str++;
  }
}
