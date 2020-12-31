#include "japarimeter/bmp280.h"
#include "japarimeter/page_master.hpp"
#include "main.h"

#if defined(STM32F303x8)
extern TIM_HandleTypeDef htim6;
#elif defined(STM32G031xx)
extern TIM_HandleTypeDef htim16;
#endif

extern BMP280_HandleTypedef bmp280;

extern int32_t fixed_temperature;
extern uint32_t fixed_pressure;
extern uint32_t fixed_humidity;

extern PageMaster pageMaster;

volatile uint32_t button0_tick       = 0;
volatile uint32_t button1_tick       = 0;
volatile GPIO_PinState button0_state = GPIO_PIN_SET;
volatile GPIO_PinState button1_state = GPIO_PIN_SET;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (!bmp280_read_fixed(&bmp280, &fixed_temperature, &fixed_pressure, &fixed_humidity))
    Error_Handler();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  uint32_t tick       = HAL_GetTick();
  GPIO_PinState state = HAL_GPIO_ReadPin(GPIO_Pin == BUTTON0_Pin ? BUTTON0_GPIO_Port : BUTTON1_GPIO_Port, GPIO_Pin);

  if (GPIO_Pin == BUTTON0_Pin) {
    if (tick - button0_tick >= 100) {
      if (!state) {
        if (tick - button0_tick >= 1500)
          pageMaster.longPressMenuButton();
        else
          pageMaster.pressMenuButton();
      }

      button0_state = state;
    }

    button0_tick = tick;
  }

  if (GPIO_Pin == BUTTON1_Pin) {
    if (tick - button1_tick >= 100) {
      if (!state) {
        if (tick - button1_tick >= 1500)
          pageMaster.longPressNextButton();
        else
          pageMaster.pressNextButton();
      }

      button1_state = state;
    }

    button1_tick = tick;
  }
}

#if defined(STM32G031xx)
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}
#endif
