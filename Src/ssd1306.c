#include "ssd1306.h"

// Screenbuffer
static uint8_t ssd1306_buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Screen object
static SSD1306_t SSD1306;

//
// Send a byte to the command register
//
static void ssd1306_writeCommand(uint8_t command)
{
  HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x00, 1, &command, 1, 10);
}

//
// Initialize the oled screen
//
uint8_t ssd1306_initialize(void)
{
  // Wait for the screen to boot
  HAL_Delay(100);

  ssd1306_displayOff();

  ssd1306_writeCommand(SSD1306_MEMORYMODE);

  // 0x00: Horizontal Addressing Mode
  // 0x01: Vertical Addressing Mode
  // 0x10: Page Addressing Mode (RESET)
  // 0x11: Invalid
  ssd1306_writeCommand(0x10);

  ssd1306_writeCommand(SSD1306_SETSTARTPAGE);
  ssd1306_writeCommand(SSD1306_COMSCANDEC);
  ssd1306_writeCommand(SSD1306_SETLOWCOLUMN);
  ssd1306_writeCommand(SSD1306_SETHIGHCOLUMN);
  ssd1306_writeCommand(SSD1306_SETSTARTLINE);

  ssd1306_writeCommand(0xA1); // set segment re-map 0 to 127
  ssd1306_writeCommand(SSD1306_NORMALDISPLAY);

  ssd1306_writeCommand(SSD1306_SETMULTIPLEX);
  ssd1306_writeCommand(0x1F); // height 32 (0x1f)

  ssd1306_writeCommand(SSD1306_DISPLAYALLON_RESUME);

  ssd1306_writeCommand(SSD1306_SETDISPLAYOFFSET);
  ssd1306_writeCommand(0x00); // not offset

  ssd1306_writeCommand(SSD1306_SETDISPLAYCLOCKDIV);
  ssd1306_writeCommand(0xF0); // set divide ratio
  ssd1306_writeCommand(SSD1306_SETPRECHARGE);
  ssd1306_writeCommand(0x22);

  ssd1306_writeCommand(SSD1306_SETCOMPINS);
  ssd1306_writeCommand(0x02); // 0x02: 128x32, 0x12: 128x64

  ssd1306_setContrast(0x8f); // 0x8f: 128x32, 0xcf: 128x64 (max)

  ssd1306_writeCommand(SSD1306_SETVCOMDETECT);
  ssd1306_writeCommand(0x20); // 0x20: 0.77xVcc

  ssd1306_writeCommand(SSD1306_CHARGEPUMP);
  ssd1306_writeCommand(0x14);

  ssd1306_fill(ssd1306_black);
  ssd1306_updateScreen();
  ssd1306_displayOn();

  // Set default values for screen object
  SSD1306.currentX = 0;
  SSD1306.currentY = 0;

  SSD1306.fillMode = false;

  return 1;
}

//
// Fill the whole screen with the given color
//
void ssd1306_fill(SSD1306_COLOR color)
{
  for (uint32_t i = 0; i < sizeof(ssd1306_buffer); i++)
    ssd1306_buffer[i] = (color == ssd1306_black) ? 0x00 : 0xFF;
}

//
// Write the screenbuffer with changed to the screen
//
void ssd1306_updateScreen(void)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    ssd1306_writeCommand(SSD1306_SETSTARTPAGE + i);
    ssd1306_writeCommand(0x00);
    ssd1306_writeCommand(0x10);

    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, SSD1306_SETSTARTLINE, 1, &ssd1306_buffer[SSD1306_WIDTH * i], SSD1306_WIDTH, 100);
  }
}

// Draw one pixel in the screenbuffer
// X => X Coordinate
// Y => Y Coordinate
// color => Pixel color
//
void ssd1306_drawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color)
{
  if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
  {
    // Don't write outside the buffer
    return;
  }

  // Draw in the right color
  if (color == ssd1306_white)
  {
    ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
  }
  else if (SSD1306.fillMode)
  {
    ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
  }
}

//
// Draw 1 char to the screen buffer
// ch    => char om weg te schrijven
// Font  => Font waarmee we gaan schrijven
// color => ssd1306_black or ssd1306_white
//
char ssd1306_writeChar(char ch, FontDef Font, SSD1306_COLOR color)
{
  // Check remaining space on current line
  if (SSD1306_WIDTH <= (SSD1306.currentX + Font.FontWidth) ||
      SSD1306_HEIGHT <= (SSD1306.currentY + Font.FontHeight))
  {
    // Not enough space on current line
    return 0;
  }

  // Use the font to write
  for (uint32_t i = 0; i < Font.FontHeight; i++)
  {
    uint32_t b = Font.data[(ch - 32) * Font.FontHeight + i];

    for (uint32_t j = 0; j < Font.FontWidth; j++)
    {
      if ((b << j) & 0x8000)
      {
        ssd1306_drawPixel(SSD1306.currentX + j, (SSD1306.currentY + i), (SSD1306_COLOR)color);
      }
      else
      {
        ssd1306_drawPixel(SSD1306.currentX + j, (SSD1306.currentY + i), (SSD1306_COLOR)!color);
      }
    }
  }

  // The current space is now taken
  SSD1306.currentX += Font.FontWidth;

  // Return written char for validation
  return ch;
}

//
// Write full string to screenbuffer
//
char ssd1306_writeString(const char *str, FontDef Font, SSD1306_COLOR color)
{
  // Write until null-byte
  while (*str)
  {
    if (ssd1306_writeChar(*str, Font, color) != *str)
    {
      // Char could not be written
      return *str;
    }

    // Next char
    str++;
  }

  // Everything ok
  return *str;
}

//
// Position the cursor
//
void ssd1306_setCursor(uint8_t x, uint8_t y)
{
  SSD1306.currentX = x;
  SSD1306.currentY = y;
}

void ssd1306_setContrast(uint8_t contrast)
{
  ssd1306_writeCommand(0x81);
  ssd1306_writeCommand(contrast);
}

void ssd1306_setFillMode(bool fill)
{
  SSD1306.fillMode = fill;
}

void ssd1306_displayOn()
{
  ssd1306_writeCommand(SSD1306_DISPLAYON);
}

void ssd1306_displayOff()
{
  ssd1306_writeCommand(SSD1306_DISPLAYOFF);
}
