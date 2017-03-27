/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "key.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Key_Initialize(void)
{
    GPIO_Init( KEY_GPIO_PORT, KEY_GPIO_PIN, GPIO_MODE_IN_PU_IT );
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);
    //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
}



