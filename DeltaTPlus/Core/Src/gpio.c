/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BOOT_MODE_GPIO_Port, BOOT_MODE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, TFT_RESET_Pin|TFT_CS_Pin|TFT_RS_Pin|TFT_WR_Pin
                          |TFT_RD_Pin|TEMP1_CS_Pin|TEMP2_CS_Pin|TFT_BACKLIGHT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB12_Pin|DB10_Pin|DB11_Pin|DB13_Pin
                          |DB14_Pin|DB15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BOOT_MODE_Pin */
  GPIO_InitStruct.Pin = BOOT_MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BOOT_MODE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_RESET_Pin TFT_CS_Pin TFT_RS_Pin TFT_WR_Pin
                           TFT_RD_Pin TEMP1_CS_Pin TEMP2_CS_Pin TFT_BACKLIGHT_Pin */
  GPIO_InitStruct.Pin = TFT_RESET_Pin|TFT_CS_Pin|TFT_RS_Pin|TFT_WR_Pin
                          |TFT_RD_Pin|TEMP1_CS_Pin|TEMP2_CS_Pin|TFT_BACKLIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DB12_Pin DB10_Pin DB11_Pin DB13_Pin
                           DB14_Pin DB15_Pin */
  GPIO_InitStruct.Pin = DB12_Pin|DB10_Pin|DB11_Pin|DB13_Pin
                          |DB14_Pin|DB15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
