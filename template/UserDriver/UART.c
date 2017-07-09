#define UART_MODULE (1)
/* Includes ------------------------------------------------------------------*/
#include "UART.h"
#include "stdio.h"

/* Private defines -----------------------------------------------------------*/
//parameters for configuration of UART
#define UART_CONFIG_BAUDRATE    (115200)
#define UART_CONFIG_WORDLENGTH  (UART1_WORDLENGTH_8D)
#define UART_CONFIG_STOPBITS    (UART1_STOPBITS_1)
#define UART_CONFIG_PARITY      (UART1_PARITY_NO)
#define UART_CONFIG_SYNCMODE    (UART1_SYNCMODE_CLOCK_DISABLE)
#define UART_CONFIG_MODE        (UART1_MODE_TXRX_ENABLE)
//choise UART for printf
#define UART_CONFIG_PRINTF      UART1

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void UART_Initialize(void)
{
    UART1_DeInit();
    UART1_Init((uint32_t)UART_CONFIG_BAUDRATE,
                         UART_CONFIG_WORDLENGTH,
                         UART_CONFIG_STOPBITS,
                         UART_CONFIG_PARITY,
                         UART_CONFIG_SYNCMODE,
                         UART_CONFIG_MODE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
}


int putchar( int ch )
{
    UART_CONFIG_PRINTF->DR = ((uint8_t)ch);
    while( RESET == (UART_CONFIG_PRINTF->SR & UART1_FLAG_TXE))
    {
        ;
    }
    return ch;
}

int getchar( void )
{
    int ch  = 0;
    while( RESET == (UART_CONFIG_PRINTF->SR & UART1_FLAG_RXNE) )
    {
        ;
    }
    ch = UART_CONFIG_PRINTF->DR;
    return ch;
}
