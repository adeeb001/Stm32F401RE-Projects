/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
unsigned char key_press(void);
unsigned char check_clm(unsigned char pin_var);
void LCD_init(void);
void LCD(uint8_t val_1, uint8_t cmd);
void LCD_str(unsigned char *str1);
void Disp_pass_key(unsigned char key_var);
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
  /* USER CODE BEGIN 2 */
  unsigned char var1;                 //to store the pressed key
  	unsigned char arr[] = "Welcome";    //String to be displayed on LCD

      HAL_Init();
      SystemClock_Config();
      MX_GPIO_Init();

  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                            |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                            |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_SET);
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  	LCD_init();                         //LCD initialization function
  	LCD_str(&arr[0]);                   //LCD string display function
  	HAL_Delay(1000);
  	LCD(0x80, 0);                       //cursor position to start of first line
  	LCD_str("Enter password");          //display "Enter password" on first line
  	LCD(0xC0, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	  		HAL_Delay(300);
	  		var1 = key_press();
	  		Disp_pass_key(var1);
	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	  		HAL_Delay(1000);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
unsigned char key_press(void)
{
	unsigned char clm_var;
	unsigned char key_arr[] = {7, 8, 9, 15, 4, 5, 6, 14, 1, 2, 3, 13, 10, 0, 11, 12};

	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)
	{
		clm_var = check_clm(GPIO_PIN_0);
		return key_arr[clm_var-1];
	}
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0)
	{
		clm_var = check_clm(GPIO_PIN_1);
		return key_arr[clm_var+3];
	}
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
	{
		clm_var = check_clm(GPIO_PIN_2);
		return key_arr[clm_var+7];
	}
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
	{
		clm_var = check_clm(GPIO_PIN_3);
		return key_arr[clm_var+11];
	}
	else
		return 16;
}

unsigned char check_clm(unsigned char pin_var)
{
	unsigned char clm;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);		//Set all columns to logic 1 ie connected to Vcc

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);						//set first column to Gnd
	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)
		clm = 1;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);						//set second column to Gnd
	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)
		clm = 2;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);						//set third column to Gnd
	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)
		clm = 3;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);						//set fourth column to Gnd
	if(HAL_GPIO_ReadPin(GPIOB, pin_var) == 0)
		clm = 4;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);		//Set all columns to logic 0 ie connected to GND
	return clm;
}

void LCD_init(void)
{
	LCD(0x38, 0);			//2 lines, 5*7 matrix
	//LCD(0x0C, 0);			//Display on, cursor off
	LCD(0x0E, 0);			//Display on, cursor blinking
	LCD(0x06, 0);			//Increment cursor (shift cursor to right)
	LCD(0x01, 0);			//Clear display screen
	LCD(0x80, 0);			//Force cursor to beginning ( 1st line)
}

void LCD(uint8_t val_1, uint8_t cmd)
{
	uint8_t data1;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, cmd);			//set RS = cmd; (cmd=0) => Command; (cmd=1) => Data

	data1 = val_1 & 0x01;														//mask bit and assign it to GPIO 0
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, data1);

	data1 = (val_1>>1) & 0x01;											//mask bit and assign it to GPIO 1
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, data1);

	data1 = (val_1>>2) & 0x01;											//mask bit and assign it to GPIO 2
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, data1);

	data1 = (val_1>>3) & 0x01;											//mask bit and assign it to GPIO 3
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, data1);

	data1 = (val_1>>4) & 0x01;											//mask bit and assign it to GPIO 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, data1);

	data1 = (val_1>>5) & 0x01;											//mask bit and assign it to GPIO 5
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, data1);

	data1 = (val_1>>6) & 0x01;											//mask bit and assign it to GPIO 6
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, data1);

	data1 = (val_1>>7) & 0x01;											//mask bit and assign it to GPIO 7
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, data1);

	//---------------------------------------------//
	//		Enable Pulse		//
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
}

void LCD_str(unsigned char *str1)
{
	while(*str1 != 0)               //0 ==> null character
	{
		LCD(*str1, 1);              //*str1 : value at the address pointed
		str1++;
	}
}

void Disp_pass_key(unsigned char key_var)
{
	static unsigned char pass_var1 = 0;
	static unsigned char key_arr[5];
	unsigned char enter_key[5] = {"12345"};         //correct passkey
	unsigned char i;

	if(key_var != 16)
	{
		key_arr[pass_var1] = key_var + 48;
		LCD(key_var + 48, 1);
		pass_var1++;
		if(pass_var1 == 5)
		{
			LCD(0xC0, 0);
			for(i=0;i<5;i++)
			{
				if(key_arr[i] != enter_key[i])
				{
					LCD_str("Re-enter pw");
					pass_var1 = 0;
					break;
				}
			}
			if(i == 5)
			{
				LCD_str("Welcome!!!!");
			}
			HAL_Delay(3000);
			pass_var1 = 0;
			LCD(0x01, 0);
			LCD(0x80, 0);
			LCD_str("Enter password:");
			LCD(0xC0, 0);
		}

	}
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
