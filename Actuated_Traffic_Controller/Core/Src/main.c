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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
#define MAX_SIZE 10

int queue[MAX_SIZE] = { 0 };
int front = -1, rear = -1;
int pin = 0;

// Function to check if the queue is full
int isFull() {
	// If the next position is the front, the queue is full
	return (rear + 1) % MAX_SIZE == front;
}

// Function to check if the queue is empty
int isEmpty() {
	// If the front hasn't been set, the queue is empty

	if (front == -1) {
		return 1;
	} else {
		return 0;
	}
}

// Function to enqueue (insert) an element
void enqueue(int data) {
	// If the queue is full, print an error message and
	// return
	if (isFull()) {
		//printf("Queue overflow\n");
		return;
	}
	// If the queue is empty, set the front to the first
	// position
	if (front == -1) {
		front = 0;
	}

	int insert = 1;
	// Add the data to the queue and move the rear pointer
	int i = front;
	do {
		if (queue[i] == data) {
			insert = 0;
			break;
		}
		i = (i + 1) % MAX_SIZE;
	} while (i != (rear + 1) % MAX_SIZE);

	if (insert == 1) {
		rear = (rear + 1) % MAX_SIZE;
		queue[rear] = data;
	}

	//printf("Element %d inserted\n", data);
}

// Function to dequeue (remove) an element
int dequeue() {
	// If the queue is empty, print an error message and
	// return -1
	if (isEmpty()) {
		//printf("Queue underflow\n");
		return -1;
	}
	// Get the data from the front of the queue
	int data = queue[front];
	queue[front] = 0;
	// If the front and rear pointers are at the same
	// position, reset them
	if (front == rear) {
		front = -1;
		rear = -1;
	} else {
		// Otherwise, move the front pointer to the next
		// position
		front = (front + 1) % MAX_SIZE;
	}
	// Return the dequeued data
	return data;
}

int sec = 1000;

int green_timer = 0;
int default_green = 5;
int min_green = 1;
int max_green = 12;

volatile int green_duration = 5;

void MAJOR_TURNS(void) {
	GPIOB->ODR = 0b00001001;  // MAJOR LEFT RED AND FORWARD RED
	//HAL_Delay(2 * sec);

	GPIOC->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(2 * sec);

	GPIOC->ODR = 0b00100001;  // LEFT GREEN AND FORWARD RED
	HAL_Delay(5 * sec);

	GPIOC->ODR = 0b00010001;  // LEFT YELLOW AND FORWARD RED
	HAL_Delay(1 * sec);

	GPIOC->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(2 * sec);

	GPIOC->ODR = 0b00001100;  // LEFT RED AND FORWARD GREEN
	HAL_Delay(5 * sec);

	GPIOC->ODR = 0b00001010;  // LEFT RED AND FORWARD YELLOW
	HAL_Delay(1 * sec);

	GPIOC->ODR = 0b00001001;  // LEFT RED AND FORWARD RED

}

void MINOR_TURNS(void) {
	GPIOC->ODR = 0b00001001;  // MAJOR LEFT RED AND FORWARD RED
	//HAL_Delay(2 * sec);

	GPIOB->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(2 * sec);

	GPIOB->ODR = 0b00100001;  // LEFT GREEN AND FORWARD RED
	HAL_Delay(5 * sec);

	GPIOB->ODR = 0b00010001;  // LEFT YELLOW AND FORWARD RED
	HAL_Delay(1 * sec);

	GPIOB->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(2 * sec);

	GPIOB->ODR = 0b00001100;  // LEFT RED AND FORWARD GREEN
	HAL_Delay(5 * sec);

	GPIOB->ODR = 0b00001010;  // LEFT RED AND FORWARD YELLOW
	HAL_Delay(1 * sec);

	GPIOB->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(1 * sec);
}

void MAJOR_LEFT_TURN(void) {
	green_duration = default_green;
	for (int i = 0; i < green_duration; i++) {
		GPIOC->ODR = 0b00100001;  // Major left green, forward red
		HAL_Delay(sec);
	}

	//HAL_Delay(5 * sec);
	GPIOC->ODR = 0b00010001;  // Major left yellow
	HAL_Delay(1 * sec);

	GPIOC->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(1 * sec);
}

void MAJOR_FORWARD(void) {
	green_duration = default_green;
	// Major forward green
	for (int i = 0; i < green_duration; i++) {
		GPIOC->ODR = 0b00001100;
		HAL_Delay(sec);
	}

	//HAL_Delay(5 * sec);
	GPIOC->ODR = 0b00001010;  // Major forward yellow
	HAL_Delay(1 * sec);

	GPIOC->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(1 * sec);
}

void MINOR_LEFT_TURN(void) {
	green_duration = default_green;
	// Minor left green, forward red

	for (int i = 0; i < green_duration; i++) {
		GPIOB->ODR = 0b00100001;
		HAL_Delay(sec);
	}

	//HAL_Delay(5 * sec);
	GPIOB->ODR = 0b00010001;  // Minor left yellow
	HAL_Delay(1 * sec);

	GPIOB->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(1 * sec);

}

void MINOR_FORWARD(void) {
	green_duration = default_green;
	// Minor forward green

	for (int i = 0; i < green_duration; i++) {
		GPIOB->ODR = 0b00001100;
		HAL_Delay(sec);
	}

	//HAL_Delay(5 * sec);
	GPIOB->ODR = 0b00001010;  // Minor forward yellow
	HAL_Delay(1 * sec);

	GPIOB->ODR = 0b00001001;  // LEFT RED AND FORWARD RED
	HAL_Delay(1 * sec);

}

int main(void) {

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

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		if (front >= MAX_SIZE || rear >= MAX_SIZE) {
			// Reset the queue as it's been corrupted
			front = -1;
			rear = -1;
		}

		int current_value = queue[front];

		/* USER CODE END WHILE */
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
			MAJOR_TURNS();
			MINOR_TURNS();
		} else {
			//!isEmpty()
			if (!isEmpty()) {

				switch (current_value) {
				case 1:
					MAJOR_FORWARD();
					//dequeue();
					//pin = 0;
					break;

				case 2:
					MAJOR_LEFT_TURN();
					//dequeue();
					//pin = 0;
					break;

				case 3:

					MINOR_FORWARD();
					//dequeue();
					//pin = 0;
					break;

				case 4:
					MINOR_LEFT_TURN();
					//dequeue();
					//pin = 0;
					break;

				default:
					GPIOB->ODR = 0b00001001;
					GPIOC->ODR = 0b00001001;
					break;
				}

				dequeue();
				HAL_Delay(500);

			} else {
				GPIOB->ODR = 0b00001001;
				GPIOC->ODR = 0b00001001;
			}

		}

		/* USER CODE END 3 */
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	switch (GPIO_Pin) {
	case GPIO_PIN_1:
		if (!isEmpty() && queue[front] == 1 && green_duration < max_green) {
			green_duration += min_green;
		}
		enqueue(1);
		break;

	case GPIO_PIN_5:
		if (!isEmpty() && queue[front] == 2 && green_duration < max_green) {
			green_duration += min_green;
		}
		enqueue(2);
		break;

	case GPIO_PIN_6:
		if (!isEmpty() && queue[front] == 3 && green_duration < max_green) {
			green_duration += min_green;
		}
		enqueue(3);
		break;

	case GPIO_PIN_4:

		if (!isEmpty() && queue[front] == 4 && green_duration < max_green) {
			green_duration += min_green;
		}
		enqueue(4);
		break;
	}

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */

static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
	GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PC0 PC1 PC2 PC3
	 PC4 PC5 PC6 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PA0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA1 PA2 PA3 PA4 */
	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 PB3
	 PB4 PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Configure replacement pins for PA2 and PA3 */
	GPIO_InitTypeDef GPIO_InitStruct_Replacement = { 0 };
	GPIO_InitStruct_Replacement.Pin = GPIO_PIN_5 | GPIO_PIN_6;  // New pins
	GPIO_InitStruct_Replacement.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct_Replacement.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_Replacement);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);  // For pins 5-9
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

void EXTI9_5_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
