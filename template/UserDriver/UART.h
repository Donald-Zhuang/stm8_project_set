/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

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
#ifdef UART_MODULE
    #define UART_EXTERN
#else
    #define UART_EXTERN extern
#endif

UART_EXTERN u8 u8UartData;

/* Exported functions --------------------------------------------------------*/
UART_EXTERN void UART_Initialize(void);

#endif

