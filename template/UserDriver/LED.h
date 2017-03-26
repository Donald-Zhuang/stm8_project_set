/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/** @addtogroup
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup
  * @{
  */
void LED_Initialize(void);
void LED_Set_Status(u8 sta);
void LED_Reverse(void);
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#endif


