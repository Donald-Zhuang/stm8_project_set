/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOB)
#define LED_GPIO_PIN  (GPIO_PIN_5)

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void LED_Initialize( void )
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

void LED_Set_Status( u8 sta )
{
    if(sta == RESET)
    {
        GPIO_WriteHigh( LED_GPIO_PORT, LED_GPIO_PIN );
    }else{
        GPIO_WriteLow( LED_GPIO_PORT, LED_GPIO_PIN );
    }
}
void LED_Reverse( void )
{
    GPIO_WriteReverse( LED_GPIO_PORT, LED_GPIO_PIN );
}

