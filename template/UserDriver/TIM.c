#define TIM_MODULE (1)

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "TIM.h"
/* Private defines -----------------------------------------------------------*/
#define TIM2_PRESCALER_CNT  (TIM2_PRESCALER_16)
#define TIM2_PERIOD_CNT     (999)

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void TIM1_Initialize(void)
{
    TIM1_TimeBaseInit( 16, TIM1_COUNTERMODE_UP, 1000, 0);
    TIM1_PrescalerConfig( 16, TIM1_PSCRELOADMODE_IMMEDIATE );
    TIM1_ARRPreloadConfig(ENABLE);
    TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
    TIM1_Cmd(ENABLE);
}


void TIM2_Counter_Initialize( void )
{
    TIM2_TimeBaseInit( TIM2_PRESCALER_CNT, TIM2_PERIOD_CNT );
    TIM2_PrescalerConfig( TIM2_PRESCALER_CNT, TIM2_PSCRELOADMODE_IMMEDIATE ); // make the config effect immediately
    TIM2_ARRPreloadConfig(ENABLE);
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE );
    TIM2_Cmd(ENABLE);
}

void TIM2_PWM_Initialize( void )
{
    TIM2_TimeBaseInit(TIM2_PRESCALER_CNT, TIM2_PERIOD_CNT);
    TIM2_OC1Init( TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, TIM2_PERIOD_CNT/3, TIM2_OCPOLARITY_HIGH);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);
}

void TIM4_Timer_Init(void)
{
    u16SysTick = 0;
    // Warning : DO NOT Change these configurations
    TIM4_TimeBaseInit( TIM4_PRESCALER_64, 250 );
    TIM4_ARRPreloadConfig(ENABLE);
    TIM4_PrescalerConfig(TIM4_PRESCALER_64, TIM4_PSCRELOADMODE_IMMEDIATE);
    TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
    TIM4_Cmd(ENABLE);
}

