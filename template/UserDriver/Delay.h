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
#define EXTERN
#else
#define EXTERN extern
#endif

/* Exported functions --------------------------------------------------------*/
EXTERN void Delay_Initialize(void);
EXTERN void Delay_Nmsec(u16 nms);
EXTERN void Delay_Nsec(u16 ns);


#endif


