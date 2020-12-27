#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

typedef struct __BOARD_CONFIG {
  uint64_t magic_number;
  uint16_t count;
  uint8_t brightness;
} BoardConfig;

#define CONFIG_MAGICNUMBER 0x7F01CF42

#if defined(STM32F303x8)
#define CONFIG_PAGE 31
#elif defined(STM32G031xx)
#define CONFIG_PAGE (FLASH_PAGE_NB - 1)
#endif

#endif
