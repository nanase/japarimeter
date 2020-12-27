#include <stdlib.h>

#include "bmp280.h"
#include "bmp280_macros.hpp"
#include "board_config.h"
#include "c_font.h"
#include "c_image.h"
#include "flash.h"
#include "main.h"
#include "page_master.hpp"
#include "ssd1306.h"

BMP280_HandleTypedef bmp280;
char buf[32];
const uint8_t contrasts[5] = { 0x01, 0x10, 0x20, 0x40, 0x8f };
uint8_t contrast_index     = 3;

// int8_t page_index          = 0;
// uint8_t old_page_index     = 0;
// Page *page;

PageMaster pageMaster;

int32_t fixed_temperature;
uint32_t fixed_pressure;
uint32_t fixed_humidity;

#if defined(STM32F303x8)
extern TIM_HandleTypeDef htim6;
#elif defined(STM32G031xx)
extern TIM_HandleTypeDef htim16;
#endif

void setup() {
  bmp280_init_default_params(&bmp280.params);
  bmp280.addr = BMP280_I2C_ADDRESS_0;

#if defined(STM32F303x8)
  bmp280.i2c = &hi2c1;
#elif defined(STM32G031xx)
  bmp280.i2c = &hi2c2;
#endif

  // bmp280.params.mode = BMP280_MODE_NORMAL;
  bmp280.params.filter                   = BMP280_FILTER_OFF;
  bmp280.params.oversampling_pressure    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_temperature = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_humidity    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.standby                  = BMP280_STANDBY_125;

  ssd1306_initialize();
  ssd1306_fill(ssd1306_black);
  ssd1306_updateScreen();

  uint16_t error = 1;

  do {
    if (!bmp280_init(&bmp280, &bmp280.params))
      Error_Handler();

    HAL_Delay(130);

    if (!bmp280_read_fixed(&bmp280, &fixed_temperature, &fixed_pressure, &fixed_humidity))
      Error_Handler();

    if (fixed_pressure <= 1100 * 25600 && fixed_pressure >= 300 * 25600)
      break;

    ssd1306_fill(ssd1306_black);

    ssd1306_setFillMode(true);
    ssd1306_setCursor(0, 0);
    sprintf(buf, "error %d", error++);
    cFont_writeString(&font_11x18, buf);
    ssd1306_setCursor(0, 18);
    sprintf(buf, "%ld", fixed_pressure);
    cFont_writeString(&font_11x18, buf);

    ssd1306_updateScreen();

    HAL_Delay(1000);
  } while (1);

#if defined(STM32F303x8)
  HAL_TIM_Base_Start_IT(&htim6);
#elif defined(STM32G031xx)
  HAL_TIM_Base_Start_IT(&htim16);
#endif

  BoardConfig config;
  flash_read(CONFIG_PAGE, 0, &config, sizeof(BoardConfig));

  if (config.magic_number != CONFIG_MAGICNUMBER) {
    ssd1306_setFillMode(true);
    ssd1306_fill(ssd1306_black);
    ssd1306_setCursor(5, 5);
    cFont_writeString(&font_16x26, "erase");
    // ssd1306_writeString("erase", Font_16x26, ssd1306_white);
    ssd1306_updateScreen();
    HAL_Delay(1000);

    flash_erase_page(CONFIG_PAGE);
    config.magic_number = CONFIG_MAGICNUMBER;
    config.count        = 0;
    flash_write(CONFIG_PAGE, 0, &config, sizeof(BoardConfig));
  } else {
    config.count++;
    flash_erase_page(CONFIG_PAGE);
    flash_write(CONFIG_PAGE, 0, &config, sizeof(BoardConfig));
  }

  flash_read(CONFIG_PAGE, 0, &config, sizeof(BoardConfig));

  ssd1306_setFillMode(true);
  ssd1306_fill(ssd1306_black);
  ssd1306_setCursor(5, 5);
  sprintf(buf, "%d", config.count);
  cFont_writeString(&font_16x26, buf);
  // ssd1306_writeString(buf, Font_16x26, ssd1306_white);
  ssd1306_updateScreen();
  HAL_Delay(2000);

  pageMaster.initialize();
}

void loop() {
  ssd1306_setContrast(contrasts[contrast_index]);

  // if (page_index != old_page_index) {
  //   delete page;

  //   switch (page_index) {
  //     case 0:
  //       page = new TemperatureHumidityPage();
  //       break;

  //     case 1:
  //       page = new HumidityPage();
  //       break;

  //     case 2:
  //       page = new TemperaturePage();
  //       break;

  //     case 3:
  //       page = new PressurePage();
  //       break;

  //     default:
  //       break;
  //   }

  //   old_page_index = page_index;
  //   page->initialize();
  // } else {
  //   page->update();
  // }

  pageMaster.update();

  HAL_Delay(250);
}
