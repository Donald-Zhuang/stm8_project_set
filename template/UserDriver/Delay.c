
/* Includes ------------------------------------------------------------------*/
#define DELAY_MODULE
#include "stm8s.h"
#include "TIM.h"
#include "Delay.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Delay_Initialize(void)
{
    TIM4_Timer_Init();
}

void Delay_Nmsec(u16 nms)
{
    s32 s32SysTickTmp = u16SysTick,s32Tmp;
    u16 u16Cnt = 0;
    while(u16Cnt < nms)
    {
        s32Tmp = u16SysTick - s32SysTickTmp;
        u16Cnt =  (s32Tmp < 0) ? (s32Tmp + (1<<16 - 1)):s32Tmp;
    }
    return ;
}

void Delay_Nsec(u16 ns)
{

    while(ns--)
    {
        Delay_Nmsec(1000);
    }
    return ;
}