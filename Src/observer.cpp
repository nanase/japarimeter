#include "bmp280.h"
#include "bmp280_macros.hpp"
#include "board_config.h"
#include "flash.h"
#include "fonts.h"
#include "main.h"
#include "page.hpp"
#include "ssd1306.h"

BMP280_HandleTypedef bmp280;
char buf[32];
const uint8_t contrasts[5] = { 0x01, 0x10, 0x20, 0x40, 0x8f };
uint8_t contrast_index     = 4;
uint8_t page_index         = 0;
uint8_t old_page_index     = 0;
Page *page;
int32_t fixed_temperature;
uint32_t fixed_pressure;
uint32_t fixed_humidity;

volatile uint32_t button0_tick       = 0;
volatile uint32_t button1_tick       = 0;
volatile GPIO_PinState button0_state = GPIO_PIN_SET;
volatile GPIO_PinState button1_state = GPIO_PIN_SET;

extern TIM_HandleTypeDef htim6;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (!bmp280_read_fixed(&bmp280, &fixed_temperature, &fixed_pressure, &fixed_humidity))
    Error_Handler();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  uint32_t tick       = HAL_GetTick();
  GPIO_PinState state = HAL_GPIO_ReadPin(GPIO_Pin == BUTTON0_Pin ? BUTTON0_GPIO_Port : BUTTON1_GPIO_Port, GPIO_Pin);

  if (GPIO_Pin == BUTTON0_Pin) {
    if (tick - button0_tick >= 100) {
      if (!state /*&& page_index < 1*/) {
        page_index++;
        page_index = (page_index + 3) % 3;
      }

      button0_state = state;
    }

    button0_tick = tick;
  }

  if (GPIO_Pin == BUTTON1_Pin) {
    if (tick - button1_tick >= 100) {
      if (!state /*&& page_index > 0*/) {
        page_index--;
        page_index = (page_index + 3) % 3;
      }

      button1_state = state;
    }

    button1_tick = tick;
  }
}

void setup() {
  bmp280_init_default_params(&bmp280.params);
  bmp280.addr = BMP280_I2C_ADDRESS_0;
  bmp280.i2c  = &hi2c1;
  // bmp280.params.mode = BMP280_MODE_NORMAL;
  bmp280.params.filter                   = BMP280_FILTER_OFF;
  bmp280.params.oversampling_pressure    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_temperature = BMP280_ULTRA_LOW_POWER;
  bmp280.params.oversampling_humidity    = BMP280_ULTRA_LOW_POWER;
  bmp280.params.standby                  = BMP280_STANDBY_125;

  ssd1306_initialize();
  ssd1306_fill(ssd1306_black);
  ssd1306_updateScreen();

  BoardConfig config;
  flash_read(31, 0, &config, sizeof(BoardConfig));
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
    ssd1306_writeString(buf, Font_11x18, ssd1306_white);
    ssd1306_setCursor(0, 18);
    sprintf(buf, "%ld", fixed_pressure);
    ssd1306_writeString(buf, Font_7x10, ssd1306_white);

    ssd1306_updateScreen();

    HAL_Delay(1000);
  } while (1);

  HAL_TIM_Base_Start_IT(&htim6);

  // if (config.magic_number != 0x7F01CF42)
  // {
  //   ssd1306_setFillMode(true);
  //   ssd1306_fill(ssd1306_black);
  //   ssd1306_setCursor(5, 5);
  //   ssd1306_writeString("erase", Font_16x26, ssd1306_white);
  //   ssd1306_updateScreen();
  //   HAL_Delay(1000);

  //   flash_erase_page(31);
  //   config.magic_number = 0x7F01CF42;
  //   config.count = 0;
  //   flash_write(31, 0, &config, sizeof(BoardConfig));
  // }
  // else
  // {
  //   config.count++;
  //   flash_erase_page(31);
  //   flash_write(31, 0, &config, sizeof(BoardConfig));
  // }

  // flash_read(31, 0, &config, sizeof(BoardConfig));

  // ssd1306_setFillMode(true);
  // ssd1306_fill(ssd1306_black);
  // ssd1306_setCursor(5, 5);
  // sprintf(buf, "%d", config.count);
  // ssd1306_writeString(buf, Font_16x26, ssd1306_white);
  // ssd1306_updateScreen();
  // HAL_Delay(2000);

  page = new HumidityPage();
  page->initialize();
}

void loop() {
  ssd1306_setContrast(contrasts[contrast_index]);

  if (page_index != old_page_index) {
    delete page;

    switch (page_index) {
      case 0:
        page = new TemperatureHumidityPage();
        break;

      case 1:
        page = new HumidityPage();
        break;

      case 2:
        page = new PressurePage();
        break;

      default:
        break;
    }

    old_page_index = page_index;
    page->initialize();
  } else {
    page->update();
  }

  HAL_Delay(250);
}
