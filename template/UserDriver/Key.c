#define KEY_MODULE (1)
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "key.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Key_Initialize(void)
{
    GPIO_Init( KEY_GPIO_PORT, KEY_GPIO_PIN, KEY_GPIO_MODE );
    EXTI_SetExtIntSensitivity( KEY_IT_PORT, KEY_IT_MODE );
    //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
}



