/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BOOT_MODE_Pin GPIO_PIN_3
#define BOOT_MODE_GPIO_Port GPIOH
#define TFT_RESET_Pin GPIO_PIN_0
#define TFT_RESET_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_1
#define TFT_CS_GPIO_Port GPIOA
#define TFT_RS_Pin GPIO_PIN_2
#define TFT_RS_GPIO_Port GPIOA
#define TFT_WR_Pin GPIO_PIN_3
#define TFT_WR_GPIO_Port GPIOA
#define TFT_RD_Pin GPIO_PIN_4
#define TFT_RD_GPIO_Port GPIOA
#define TEMP1_CS_Pin GPIO_PIN_8
#define TEMP1_CS_GPIO_Port GPIOA
#define TEMP2_CS_Pin GPIO_PIN_9
#define TEMP2_CS_GPIO_Port GPIOA
#define DB12_Pin GPIO_PIN_2
#define DB12_GPIO_Port GPIOB
#define DB10_Pin GPIO_PIN_0
#define DB10_GPIO_Port GPIOB
#define DB11_Pin GPIO_PIN_1
#define DB11_GPIO_Port GPIOB
#define TFT_BACKLIGHT_Pin GPIO_PIN_10
#define TFT_BACKLIGHT_GPIO_Port GPIOA
#define DB13_Pin GPIO_PIN_3
#define DB13_GPIO_Port GPIOB
#define DB14_Pin GPIO_PIN_4
#define DB14_GPIO_Port GPIOB
#define DB15_Pin GPIO_PIN_5
#define DB15_GPIO_Port GPIOB
#define DB16_Pin GPIO_PIN_6
#define DB16_GPIO_Port GPIOB
#define DB17_Pin GPIO_PIN_7
#define DB17_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
