#ifndef __DIRIVER_LCD_ST7585_H
#define __DIRIVER_LCD_ST7585_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
/* Exported constants --------------------------------------------------------*/

/* Function Control */
#define LED_ENABLE (0)

/* LCD Chip Select I/O definition */
#define LCD_SDA  ((pByte)&GPIOC->ODR)->bit5
#define LCD_A0   ((pByte)&GPIOC->ODR)->bit6
#define LCD_CS   ((pByte)&GPIOC->ODR)->bit3
#define LCD_SCL  ((pByte)&GPIOC->ODR)->bit4
#define LCD_RES  ((pByte)&GPIOC->ODR)->bit7

/* LCD Backlight I/O definition */
#if (LED_ENABLE == 1)
#define LCD_LED  ((pByte)&GPIOD->ODR)->bit5
#endif

/* LCD Commands */
#define NOP                 (0x00)
#define FUNCTION_SET        (0x20)
#define DISPLAY_CONTROL     (0x08)
#define SET_Y_LOCATION      (0x40)
#define SET_X_LOCATION      (0x80)
#define SET_V0              (0x80)
#define SET_TEST_MODE       (0x30)

/* Some LCD data*/
#define LENGTH_OF_CHAR          (0x06)
#define LENGTH_OF_LINE_PIXEL    (0x96)
#define NUMBER_OF_PIXEL         (960)

/* Exported macro ------------------------------------------------------------*/
#define DIS_PHONEANT_0  0    //天线
#define DIS_PHONEANT_1  4    //信号1 格
#define DIS_PHONEANT_2  5    //信号2 格
#define DIS_PHONEANT_3  7    //信号3 格
#define DIS_PHONEANT_4  8    //信号4 格
#define DIS_PHONEANT_5  10
#define DIS_PHONE       20   //电话
#define DIS_LOCK        30   //锁定
#define DIS_Gr          40   //Gr 符号
#define DIS_SMS         50   //短信符号
#define DIS_SHAKE       60   //震动符号
#define DIS_HOME        61   //室内符号
#define DIS_HOME_ANT    65   //室内天线符号
#define DIS_HOME_ANT_1  67   //室内天线1 格
#define DIS_HOME_ANT_2  68   //室内天线2 格
#define DIS_HOME_ANT_3  69   //室内天线3 格
#define DIS_MUTE        70   //静音符号
#define DIS_ALAM        75   //闹钟符号
#define DIS_CELL_0      80   //电池电量符号
#define DIS_CELL_1      94   //电池电量1 格
#define DIS_CELL_2      95   //电池电量2 格
#define DIS_CELL_3      93   //电池电量3 格

#define DIS_ON      0xFF
#define DIS_OFF     0x00

/* Exported functions --------------------------------------------------------*/
void LCD_Init(void);
void LCD_SetXY(u8 x, u8 y);
void LCD_cls(void);
void LCD_putch(u8 x, u8 y, u16 ch);
void LCD_putstr(u8 x, u8 y, char *str);
void LCD_ShowIcon(u8 u8Icon, u8 bOn);
void LCD_LEDControl(u8 bOn);

#endif /* __DIRIVER_LCD_ST7585_H */