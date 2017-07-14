/**
  ******************************************************************************
  * @file    Project/main.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "UART.h"
#include "LED.h"
#include "Key.h"
#include "TIM.h"
#include "Delay.h"
#include "nrf24l01.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void main(void)
{
    char ch = 0;
    u8 rxbuf[32] = {0,};
    //Clock Initialize
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    //Initialize the UART for Communication
    UART_Initialize();
    LED_Initialize();
    //TIM1_Initialize();
    TIM2_PWM_Initialize();
    //test of printf
    printf("Hello World!\r\n");
    Delay_Initialize();
    //test of led
    LED_Set_Status(SET);
    Key_Initialize();
    NRF24L01_GPIO_Initialize();
    if ( NRF24L01_Check_Device())
    {
        printf("There is a NRF24L01.\r\n");
        NRF24L01_RX_Initialize();
    }

    /*Enable the response of interrupt function*/
    enableInterrupts();
    /* Infinite loop */
    while (1)
    {
        Delay_Nmsec(500);
        LED_Reverse();

        if (NRF24L01_Recieve_Packet(rxbuf,13) != RESET)
        {
            printf(rxbuf);
        }
    }

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
