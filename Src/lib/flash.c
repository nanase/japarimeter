#include "flash.h"

bool flash_erase_page(uint8_t page_number)
{
  FLASH_EraseInitTypeDef erase;
  erase.TypeErase = FLASH_TYPEERASE_PAGES;
  erase.PageAddress = FLASH_BASE + FLASH_PAGE_SIZE * page_number;
  erase.NbPages = 1;

  uint32_t page_error = 0;

  if (!IS_FLASH_PROGRAM_ADDRESS(erase.PageAddress))
    return false;

  HAL_FLASH_Unlock();
  HAL_FLASHEx_Erase(&erase, &page_error);
  HAL_FLASH_Lock();

  return (bool)(page_error == 0);
}

bool flash_write16(uint8_t page_number, uint16_t offset, uint16_t value)
{
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return false;

  HAL_FLASH_Unlock();
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, value);
  HAL_FLASH_Lock();

  return true;
}

bool flash_write32(uint8_t page_number, uint16_t offset, uint32_t value)
{
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return false;

  HAL_FLASH_Unlock();
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, value);
  HAL_FLASH_Lock();

  return true;
}

bool flash_write64(uint8_t page_number, uint16_t offset, uint64_t value)
{
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return false;

  HAL_FLASH_Unlock();
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, value);
  HAL_FLASH_Lock();

  return true;
}

int16_t flash_write(uint8_t page_number, uint16_t offset, const void *source, uint16_t size)
{
  uint32_t address = FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset;

  if (!IS_FLASH_PROGRAM_ADDRESS(address))
    return -1;

  HAL_FLASH_Unlock();

  for (uint16_t i = 0; i < (size & 0xFFFE); i += sizeof(uint16_t))
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address + i, *((uint8_t *)source + i) << 8 | *((uint8_t *)source + i + 1));

  if ((size % 2) == 1)
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address + size - 1, *((uint8_t *)source + size - 1) << 8);

  HAL_FLASH_Lock();

  return (int16_t)size;
}

uint16_t flash_read16(uint8_t page_number, uint16_t offset)
{
  return *(uint16_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset);
}

uint32_t flash_read32(uint8_t page_number, uint16_t offset)
{
  return *(uint32_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset);
}

uint64_t flash_read64(uint8_t page_number, uint16_t offset)
{
  return *(uint64_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset);
}

void flash_read(uint8_t page_number, uint16_t offset, void *destination, uint16_t size)
{
  for (uint16_t i = 0; i < (size & 0xFFFE); i += sizeof(uint16_t))
  {
    uint16_t value = *(uint16_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset + i);
    *(uint8_t *)(destination + i) = value >> 8;
    *(uint8_t *)(destination + i + 1) = (uint8_t)(value & 0x00FF);
  }

  if ((size % 2) == 1)
  {
    *(uint8_t *)(destination + size - 1) = *(uint16_t *)(FLASH_BASE + FLASH_PAGE_SIZE * page_number + offset + size - 1) >> 8;
  }
}
