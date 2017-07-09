/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

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
#ifdef DELAY_MODULE
#define DELAY_EXTERN
#else
#define DELAY_EXTERN extern
#endif

/* Exported functions --------------------------------------------------------*/
DELAY_EXTERN void Delay_Initialize(void);
DELAY_EXTERN void Delay_Nmsec(u16 nms);
DELAY_EXTERN void Delay_Nsec(u16 ns);


#endif


