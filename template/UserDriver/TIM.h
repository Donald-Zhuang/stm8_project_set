/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H
#define __TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/** @addtogroup
  * @{
  */

/* Exported types ------------------------------------------------------------*/

#ifdef TIM_MODULE
#define TIM_EXTERN
#else
#define TIM_EXTERN extern
#endif

TIM_EXTERN u16 u16SysTick; // this variable just designes for system tick tok.

/** @addtogroup
  * @{
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
TIM_EXTERN void TIM1_Initialize(void);
TIM_EXTERN void TIM2_PWM_Initialize( void );
TIM_EXTERN void TIM2_Counter_Initialize( void );
TIM_EXTERN void TIM4_Timer_Init(void);

#endif


