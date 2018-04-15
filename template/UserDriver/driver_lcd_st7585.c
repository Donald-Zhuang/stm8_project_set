#include "driver_lcd_st7585.h"
#include "font.h"
/* Type definition */
typedef struct
{
    vu8 bit0:1;
    vu8 bit1:1;
    vu8 bit2:1;
    vu8 bit3:1;
    vu8 bit4:1;
    vu8 bit5:1;
    vu8 bit6:1;
    vu8 bit7:1;
} Byte,*pByte;

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_GpioInit(void)
{
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_HIGH_SLOW);
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_Delay(u16 x)
{
    u16 i,j;
    for(i=0; i<x; i++)
        for(j=0; j<2000; j++);
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_ShiftWrite(u8 dat)
{
    u8 tmp = 0, i = 0;
    tmp = dat;

    for(i=0; i<8; i++)
    {
        LCD_SCL = 0;
        LCD_SDA = tmp & 0x80 ? 1 : 0;
        tmp <<= 1;
        LCD_SCL = 1;
    }
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_SendCmd(u8 cmd, u8 dat)
{
    LCD_A0=0;
    LCD_CS=0;
    LCD_ShiftWrite(cmd|dat);
    LCD_CS=1;
    LCD_A0=1;
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */

void LCD_SendDat(u8 dat)
{
    LCD_CS=0;
    LCD_ShiftWrite(dat);
    LCD_CS=1;
}


/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_Init(void)
{
    LCD_GpioInit();

    LCD_RES=0;
    LCD_Delay(10);
    LCD_RES=1;
    LCD_Delay(10);
    LCD_SendCmd(FUNCTION_SET,     0x01);
    LCD_SendCmd(SET_V0,           0x30);
    LCD_SendCmd(SET_TEST_MODE,    0x02);
    LCD_SendCmd(FUNCTION_SET,     0x00);
    LCD_SendCmd(DISPLAY_CONTROL,  0x04);
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */

/*
Notes: This panel is 96*64 DOTs and has a line for ICON in 8th.

0<= y <= 8

    8 >>>>>>>>>>> ICON Line

    7
    ^
    |
    |
    |   96*64
    |
    |
    0---------->96 0 <= x <= 96
*/
void LCD_SetXY(u8 x, u8 y)
{
    LCD_SendCmd(SET_X_LOCATION,x);
    LCD_SendCmd(SET_Y_LOCATION,y);
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_cls(void)
{
    int i;
    LCD_SendCmd(SET_X_LOCATION,	0);
    LCD_SendCmd(SET_Y_LOCATION,	0);
    for(i=0; i < NUMBER_OF_PIXEL; i++)
    {
        LCD_SendDat(0x00);
    }
    LCD_SendCmd(SET_X_LOCATION,	0);
    LCD_SendCmd(SET_Y_LOCATION,	0);
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_putch(u8 x, u8 y, u16 ch)
{
    u8 i;
    LCD_SendCmd(SET_X_LOCATION,x);
    LCD_SendCmd(SET_Y_LOCATION,y);
    for(i=0; i<5; i++)
    {
        LCD_SendDat(FONT[(ch-0x20)*5+i]);
    }
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_putstr(u8 x, u8 y, char *str)
{
    while(*str!=0)
    {
        LCD_putch( x, y, *str++ );
        x += 6;
    }
}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_ShowIcon(u8 u8Icon, u8 bOn)
{
    LCD_SendCmd(SET_X_LOCATION,u8Icon);
    LCD_SendCmd(SET_Y_LOCATION,8);
    LCD_SendDat(bOn ? DIS_ON : DIS_OFF);
}

/**
  * @brief Clear one LCD
  * @param[in] Line Line to be cleared (LCD_LINE1 or LCD_LINE2)
  * @retval None
  * @par Required preconditions:
  * - LCD must be enabled
  * @par Functions called:
  * - LCD_SendByte
  * @par Example:
  * @code
  * LCD_ClearLine(LCD_LINE1);
  * @endcode
  */
void LCD_ClearLine(u8 u8Line)
{

  u8 CharPos;

  /* Select the line to be cleared */
  LCD_SetXY( 0, u8Line > 8 ? 8 : u8Line);

  /* Clear the selected line */
  for (CharPos = 0; CharPos < LENGTH_OF_LINE_PIXEL; CharPos++)
  {
    LCD_SendDat(0x00);
  }

}

/**
  * @brief
  * @par Parameters:
  *
  * @retval
  * @par Required preconditions:
  * -
  * @par Functions called:
  * -
  * @par Example:
  * @code
  *
  * @endcode
  */
void LCD_LEDControl(u8 bOn)
{
#if (LED_ENABLE == 1)
    LCD_LED = bOn;
#endif
}
