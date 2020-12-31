#include <stdlib.h>

#include "japarimeter/bmp280.h"
#include "japarimeter/bmp280_macros.hpp"
#include "japarimeter/c_font.h"
#include "japarimeter/c_image.h"
#include "japarimeter/page_master.hpp"
#include "japarimeter/ssd1306.h"
#include "main.h"

BMP280_HandleTypedef bmp280;
char buf[32];

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

  bmp280.params.filter                   = BMP280_FILTER_OFF;
  bmp280.params.oversampling_pressure    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_temperature = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_humidity    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.standby                  = BMP280_STANDBY_125;

  ssd1306_initialize();
  ssd1306_setContrast(0x40);
  ssd1306_fill(ssd1306_black);
  ssd1306_updateScreen();

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
    cFont_writeString(&font_7x10, "Error:");
    ssd1306_setFillMode(false);
    ssd1306_setCursor(1, 0);
    cFont_writeString(&font_7x10, "Error:");

    ssd1306_setFillMode(true);
    ssd1306_setCursor(0, 11);
    cFont_writeString(&font_7x10, "Sensor connection");
    ssd1306_updateScreen();

    HAL_Delay(1000);
  } while (1);

#if defined(STM32F303x8)
  HAL_TIM_Base_Start_IT(&htim6);
#elif defined(STM32G031xx)
  HAL_TIM_Base_Start_IT(&htim16);
#endif

  pageMaster.initialize();
}

void loop() {
  pageMaster.update();

  HAL_Delay(250);
}
