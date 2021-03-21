#include "japarimeter/bmp280.h"
#include "japarimeter/button.hpp"
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
extern Button buttonA;
extern Button buttonB;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (!bmp280_read_fixed(&bmp280, &fixed_temperature, &fixed_pressure, &fixed_humidity))
    Error_Handler();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  uint32_t tick       = HAL_GetTick();
  GPIO_PinState state = HAL_GPIO_ReadPin(GPIO_Pin == BUTTON0_Pin ? BUTTON0_GPIO_Port : BUTTON1_GPIO_Port, GPIO_Pin);

  if (GPIO_Pin == BUTTON0_Pin) {
    buttonA.update(tick, !state);
  }

  if (GPIO_Pin == BUTTON1_Pin) {
    buttonB.update(tick, !state);
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
