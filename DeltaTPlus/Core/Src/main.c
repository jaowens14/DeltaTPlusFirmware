/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "ipcc.h"
#include "memorymap.h"
#include "rf.h"
#include "rtc.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "st7789s.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
char buff[64];
int buff_len;
uint16_t timer_val;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Config code for STM32_WPAN (HSE Tuning must be done before system clock configuration) */
  MX_APPE_Config();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* IPCC initialisation */
  MX_IPCC_Init();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USB_Device_Init();
  MX_RF_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  HAL_Delay(2000);



      #define FT5436_ADDR   (0x38 << 1)

      uint8_t treg = 0x03;
      uint8_t tdata[4];
      char tmsg[64];

      HAL_StatusTypeDef tstatus = HAL_I2C_Mem_Read(
          &hi2c1,
          FT5436_ADDR,
          treg,
          I2C_MEMADD_SIZE_8BIT,
          tdata,
          4,
          1000
      );


          uint16_t tx = ((tdata[0] & 0x0F) << 8) | tdata[1];
          uint16_t ty = ((tdata[2] & 0x0F) << 8) | tdata[3];
          snprintf(tmsg, sizeof(tmsg), "Touch X: %u, Y: %u\r\n", tx, ty);


      CDC_Transmit_FS((uint8_t*)tmsg, strlen(tmsg));






  HAL_Delay(2000);

#define ADXL343_ADDR    (0x53 << 1)   // Correct 8-bit address for grounded ALT_ADDRESS

// 1. Initialize ADXL343 first (do this once during setup)
    uint8_t powerCtl = 0x08;  // Set MEASURE bit (Bit 3) to enable measurement mode
    HAL_I2C_Mem_Write(&hi2c1, ADXL343_ADDR, 0x2D, I2C_MEMADD_SIZE_8BIT, &powerCtl, 1, 1000);

    HAL_Delay(20);

    uint8_t accreg = 0x32;          // Start from DATAX0
    uint8_t accdata[6];
    char accmsg[64];

    // Read with error handling
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, ADXL343_ADDR, accreg,
                                              I2C_MEMADD_SIZE_8BIT, accdata, 6, 1000);

    if(status == HAL_OK) {
        // Convert raw data to signed values
        int16_t x = (int16_t)((accdata[1] << 8) | accdata[0]);
        int16_t y = (int16_t)((accdata[3] << 8) | accdata[2]);
        int16_t z = (int16_t)((accdata[5] << 8) | accdata[4]);

        // Convert to g-force (assuming ±2g range, 10-bit resolution)
        float x_g = x * 0.0039f;  // 4mg/LSB
        float y_g = y * 0.0039f;
        float z_g = z * 0.0039f;

        snprintf(accmsg, sizeof(accmsg), "X: %.2fg, Y: %.2fg, Z: %.2fg\r\n", x_g, y_g, z_g);
    } else {
        snprintf(accmsg, sizeof(accmsg), "I2C Error: %d\r\n", status);
    }

    // Check if USB CDC is ready before transmitting
    if(CDC_Transmit_FS((uint8_t*)accmsg, strlen(accmsg)) != USBD_OK) {
        // Handle USB transmission failure
    }




  HAL_Delay(2000);

  #define MAX17048_ADDR    (0x36 << 1)   // STM32 HAL expects 8-bit address


  uint8_t reg = 0x02;        // VCELL register address
  uint8_t data[2] = {0};     // To store register data

  if (HAL_I2C_Mem_Read(&hi2c1, MAX17048_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 2, 1000) == HAL_OK) {
      // Successfully read data[0] and data[1]
      uint16_t vcell_raw = (data[0] << 8) | data[1];
      vcell_raw >>= 4; // VCELL is 12 bits (upper 12 bits of 16)
      float voltage = vcell_raw * 1.25f / 1000.0f; // Each LSB = 1.25mV

      char msg[64];
      snprintf(msg, sizeof(msg), "VCELL: %.3f V\r\n", voltage);
      CDC_Transmit_FS((uint8_t*)msg, strlen(msg)); // If using USB CDC
  } else {
      char msg[] = "I2C Read Error\r\n";
      CDC_Transmit_FS((uint8_t*)msg, strlen(msg));
  }

  HAL_Delay(2000);
  //HAL_Delay(2000);
  snprintf(buff, sizeof(buff), "Hello world\r\n");
  CDC_Transmit_FS((uint8_t*)buff, strlen(buff));
  //LCD_BasicCommTest(); // Just wake up display


  LCD_Init();
  LCD_FillScreen(LCD_COLOR_RED);
  //LCD_FillRect(50, 50, 100, 100, LCD_COLOR_RED);
  /* USER CODE END 2 */

  /* Init code for STM32_WPAN */
  MX_APPE_Init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //CDC_Transmit_FS((uint8_t*)buff, strlen(buff));
	  //HAL_Delay(500);
    /* USER CODE END WHILE */
    MX_APPE_Process();

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Macro to configure the PLL multiplication factor
  */
  __HAL_RCC_PLL_PLLM_CONFIG(RCC_PLLM_DIV1);

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_MSI);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS|RCC_PERIPHCLK_RFWAKEUP;
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */
  LL_HSEM_1StepLock(HSEM, 5); // this here to keep across regens
  /* USER CODE END Smps */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
