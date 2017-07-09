/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
// parameters for initialization
#define LED_GPIO_PIN    (GPIO_PIN_5)
#define LED_GPIO_PORT   (GPIOB)
#define LED_GPIO_MODE   (GPIO_MODE_OUT_PP_HIGH_FAST)


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void LED_Initialize( void )
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PIN, LED_GPIO_MODE);
}

void LED_Set_Status( u8 sta )
{
    if(sta == SET)
    {
        LED_GPIO_PORT->ODR |=  LED_GPIO_PIN;
    }else{
        LED_GPIO_PORT->ODR &= ~(LED_GPIO_PIN);
    }

}
void LED_Reverse( void )
{
    GPIO_WriteReverse( LED_GPIO_PORT, LED_GPIO_PIN );
}

