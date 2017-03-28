/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void TIM1_Initialize(void)
{
    TIM1_TimeBaseInit( 16, TIM1_COUNTERMODE_UP, 1000, 0);
    TIM1_ARRPreloadConfig(ENABLE);
    TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
    TIM1_Cmd(ENABLE);
}

