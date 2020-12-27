#include "flash.h"

#include "string.h"

bool flash_erase_page(uint8_t page_number) {
  uint32_t page_error = 0;
  FLASH_EraseInitTypeDef erase;
  erase.TypeErase = FLASH_TYPEERASE_PAGES;
  erase.NbPages   = 1;

#if defined(STM32F303x8)
  erase.PageAddress = FLASH_BASE + FLASH_PAGE_SIZE * page_number;

  if (!IS_FLASH_PROGRAM_ADDRESS(erase.PageAddress))
    return false;
#elif defined(STM32G031xx)
  erase.Page = page_number;

  if (!IS_FLASH_PAGE(erase.Page))
    return false;
#endif

  HAL_FLASH_Unlock();
  HAL_FLASHEx_Erase(&erase, &page_error);
  HAL_FLASH_Lock();

  return (bool)(page_error == 0);
}

bool flash_write64(uint8_t page_number, uint16_t offset, uint64_t value) {
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return false;

  HAL_FLASH_Unlock();
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, value);
  HAL_FLASH_Lock();

  return true;
}

int16_t flash_write(uint8_t page_number, uint16_t offset, const void *source, uint16_t size) {
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;
  uint16_t remains = size;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return -1;

  HAL_FLASH_Unlock();

  for (uint16_t i = 0; remains >= sizeof(uint64_t); i++, remains -= sizeof(uint64_t)) {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + i * sizeof(uint64_t),
                      *((uint64_t *)((uint8_t *)source + i * sizeof(uint64_t))));
  }

  if (remains > 0) {
    uint64_t value = 0;
    memcpy((uint8_t *)&value, (uint8_t *)source + size - remains, remains);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + (size - remains) * sizeof(uint64_t), value);
  }

  HAL_FLASH_Lock();

  return (int16_t)size;
}

uint64_t flash_read64(uint8_t page_number, uint16_t offset) {
  return *(uint64_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset);
}

void flash_read(uint8_t page_number, uint16_t offset, void *destination, uint16_t size) {
  for (uint16_t i = 0; i < (size & 0xFFFE); i += sizeof(uint16_t)) {
    uint16_t value                    = *(uint16_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset + i);
    *(uint8_t *)(destination + i)     = (uint8_t)(value & 0x00FF);
    *(uint8_t *)(destination + i + 1) = value >> 8;
  }

  if ((size % 2) == 1) {
    *(uint8_t *)(destination + size - 1) =
        *(uint16_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset + size - 1) >> 8;
  }
}
