#ifndef __FLASH_H
#define __FLASH_H

#include <stdbool.h>
#include <stdint.h>

#if defined(STM32F303x8)
#include "stm32f3xx_hal.h"
#elif defined(STM32G031xx)
#include "stm32g0xx_hal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool flash_erase_page(uint8_t page_number);

bool flash_write16(uint8_t page_number, uint16_t offset, uint16_t value);
bool flash_write32(uint8_t page_number, uint16_t offset, uint32_t value);
bool flash_write64(uint8_t page_number, uint16_t offset, uint64_t value);
int16_t flash_write(uint8_t page_number, uint16_t offset, const void *source, uint16_t size);

uint16_t flash_read16(uint8_t page_number, uint16_t offset);
uint32_t flash_read32(uint8_t page_number, uint16_t offset);
uint64_t flash_read64(uint8_t page_number, uint16_t offset);
void flash_read(uint8_t page_number, uint16_t offset, void *destination, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif
