/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/** @addtogroup
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
#ifdef KEY_MODULE
#define KEY_EXTERN
#else
#define KEY_EXTERN extern
#endif

// paramaters for configuration of keypad
#define KEY_GPIO_PORT   (GPIOC)
#define KEY_GPIO_PIN    (GPIO_PIN_4)
#define KEY_GPIO_MODE   (GPIO_MODE_IN_PU_IT)
#define KEY_IT_PORT     (EXTI_PORT_GPIOC)
#define KEY_IT_MODE     (EXTI_SENSITIVITY_FALL_ONLY)

/* Exported functions --------------------------------------------------------*/
KEY_EXTERN void Key_Initialize(void);

#endif

