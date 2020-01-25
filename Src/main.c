/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usbd_customhid.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum {
    GAMEPAD_1,
    GAMEPAD_2,
    GAMEPAD_COUNT
} GamePad_Index;

#define GAMEPAD_REPORT_ID_1         (GAMEPAD_1 + 1)
#define GAMEPAD_REPORT_ID_2         (GAMEPAD_2 + 1)

extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct {
    const uint8_t ReportId;
    uint8_t ButtonsMask;
} GamePad_HidReportTypeDef;

_Static_assert(sizeof(GamePad_HidReportTypeDef) == USBD_CUSTOMHID_OUTREPORT_BUF_SIZE,
               "Invalid size of GamePad_HidReportTypeDef");

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

static GamePad_HidReportTypeDef GamepadReports[GAMEPAD_COUNT] = {
    { GAMEPAD_REPORT_ID_1, 0 }, /* First GamePad */
    { GAMEPAD_REPORT_ID_2, 0 } /* Second GamePad */
};

static uint8_t GamePadStates[GAMEPAD_COUNT] = {
    0, 0
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static void Gamepad_SomeNopCounts(uint32_t Counts)
{
    for (volatile uint32_t Index = 0; Index < Counts; ++Index) {
        __asm__("nop");
    }
}

static void Gamepad_SendReports()
{
    for (uint8_t gamepadIndex = 0; gamepadIndex < GAMEPAD_COUNT; ++gamepadIndex) {
        if (!GamePadStates[gamepadIndex])
            continue;
        const uint8_t Status = USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&GamepadReports[gamepadIndex], USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
        if (Status == HAL_OK) {
            GamePadStates[gamepadIndex] = 0;
        }
    }
}

static void Gamepad_Poll()
{
    /* Send latch pulse */
    HAL_GPIO_WritePin(GAMEPAD_LATCH_GPIO_Port, GAMEPAD_LATCH_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GAMEPAD_LATCH_GPIO_Port, GAMEPAD_LATCH_Pin, GPIO_PIN_RESET);

    uint8_t ButtonsMask1 = 0;
    uint8_t ButtonsMask2 = 0;

    for (uint8_t Bit = 0; Bit < 8; ++Bit) {
        Gamepad_SomeNopCounts(5);

        /* Note: Status GPIO_PIN_RESET means that a button is pressed. */
        const GPIO_PinState State1 = HAL_GPIO_ReadPin(GAMEPAD_DATA_1_GPIO_Port, GAMEPAD_DATA_1_Pin);
        const GPIO_PinState State2 = HAL_GPIO_ReadPin(GAMEPAD_DATA_2_GPIO_Port, GAMEPAD_DATA_2_Pin);

        const uint8_t Value1 = (State1 == GPIO_PIN_RESET) ? 1 : 0;
        const uint8_t Value2 = (State2 == GPIO_PIN_RESET) ? 1 : 0;

        ButtonsMask1 |= (Value1 << Bit);
        ButtonsMask2 |= (Value2 << Bit);

        /* Send clock pulse. */
        HAL_GPIO_WritePin(GAMEPAD_CLK_GPIO_Port, GAMEPAD_CLK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GAMEPAD_CLK_GPIO_Port, GAMEPAD_CLK_Pin, GPIO_PIN_RESET);
    }

    GamepadReports[GAMEPAD_1].ButtonsMask = ButtonsMask1;
    GamepadReports[GAMEPAD_2].ButtonsMask = ButtonsMask2;

    GamePadStates[GAMEPAD_1] = 1;
    GamePadStates[GAMEPAD_2] = 1;

    Gamepad_SendReports();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      HAL_Delay(5);

      Gamepad_Poll();

    /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GAMEPAD_LATCH_Pin|GAMEPAD_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GAMEPAD_LATCH_Pin GAMEPAD_CLK_Pin */
  GPIO_InitStruct.Pin = GAMEPAD_LATCH_Pin|GAMEPAD_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : GAMEPAD_DATA_2_Pin GAMEPAD_DATA_1_Pin */
  GPIO_InitStruct.Pin = GAMEPAD_DATA_2_Pin|GAMEPAD_DATA_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
