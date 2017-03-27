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
#define KEY_GPIO_PORT   (GPIOB)
#define KEY_GPIO_PIN    (GPIO_PIN_4)

/* Exported functions --------------------------------------------------------*/
extern void Key_Initialize(void);


#endif

