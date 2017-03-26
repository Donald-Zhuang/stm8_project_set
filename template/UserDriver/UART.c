/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void UART_Initialize(void)
{
    UART1_DeInit();
    UART1_Init((uint32_t)115200,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,\
                UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
}


int putchar( int ch )
{
    UART1_SendData8((uint8_t)ch);
    while( RESET == UART1_GetFlagStatus(UART1_FLAG_TXE))
    {
        ;
    }
    return ch;
}

int getchar( void )
{
    int ch  = 0;
    while( RESET == UART1_GetFlagStatus(UART1_FLAG_RXNE) )
    {
        ;
    }
    ch = UART1_ReceiveData8();
    return ch;
}
