#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

typedef struct __BOARD_CONFIG
{
  uint64_t magic_number;
  uint16_t count;
  uint8_t brightness;
} BoardConfig;

#endif
