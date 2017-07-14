/* Includes ------------------------------------------------------------------*/
#define NRF24L01_MODULE
#include "TIM.h"
#include "nrf24l01.h"
/* Private defines -----------------------------------------------------------*/

#define NRF24L01_CSN_PORT       (GPIOD)
#define NRF24L01_CSN_PIN        (GPIO_PIN_3)
#define NRF24L01_CE_PORT        (GPIOD)
#define NRF24L01_CE_PIN         (GPIO_PIN_2)
#define NRF24L01_CE_CSN_GPIO_MODE    (GPIO_MODE_OUT_PP_HIGH_FAST)

#define NRF24L01_CS_LOW()   {NRF24L01_CSN_PORT->ODR &= ~(NRF24L01_CSN_PIN);}
#define NRF24L01_CS_HIGH()  {NRF24L01_CSN_PORT->ODR |=  (NRF24L01_CSN_PIN);}

#define NRF24L01_CE_LOW()   {NRF24L01_CE_PORT->ODR &= ~(NRF24L01_CE_PIN);}
#define NRF24L01_CE_HIGH()  {NRF24L01_CE_PORT->ODR |=  (NRF24L01_CE_PIN);}

//*****************************************************//
#define MAX_TX  	0x10  //达到最大发送次数中断
#define TX_OK   	0x20  //TX发送完成中断
#define RX_OK   	0x40  //接收到数据中断

/*-----------------------------------------------------------*/
#define TX_ADR_WIDTH    5   // 5 bytes TX address width
#define RX_ADR_WIDTH    5   // 5 bytes RX address width
#define TX_PLOAD_WIDTH  5   // 20 bytes TX payload
#define RX_PLOAD_WIDTH  5   // 20 bytes TX payload

/* static global variables ---------------------------------------------------*/
static u8 TX_ADDRESS[TX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static TX address
static u8 RX_ADDRESS[RX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static RX address

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef STM8S103
// the following functions are relevant to chip
static void Delay_nus(u16 nus)
{
    while(nus--)
    {
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

static u8 SPI_RW(u8 ch)
{
    u8 u8retry = 0;
    while( (SPI->SR & SPI_FLAG_TXE) == RESET )
    {
        u8retry++;
        if(u8retry > 250)
        {
            return 0;
        }
    }
    SPI->DR = ch ;
    u8retry = 0;
    while( (SPI->SR & SPI_FLAG_RXNE) == RESET )
    {
        u8retry++;
        if(u8retry > 250)
        {
            return 0;
        }
    }
    return( (uint8_t)SPI->DR );
}

void NRF24L01_GPIO_Initialize( void )
{
    SPI_Init(   SPI_FIRSTBIT_MSB,
                SPI_BAUDRATEPRESCALER_4,
                SPI_MODE_MASTER,SPI_CLOCKPOLARITY_LOW,
                SPI_CLOCKPHASE_1EDGE,
                SPI_DATADIRECTION_2LINES_FULLDUPLEX,
                SPI_NSS_SOFT,
                0x07
                );
    SPI_Cmd(ENABLE);

    GPIO_Init(NRF24L01_CE_PORT,  NRF24L01_CE_PIN,  NRF24L01_CE_CSN_GPIO_MODE);
    GPIO_Init(NRF24L01_CSN_PORT, NRF24L01_CSN_PIN, NRF24L01_CE_CSN_GPIO_MODE);
}
#endif

static u8 SPI_Write_REG(u8 u8reg, u8 u8value)
{
    u8 u8status = 0;
    NRF24L01_CS_LOW();

    u8status = SPI_RW( u8reg );
    SPI_RW(u8value);

    NRF24L01_CS_HIGH();
    return u8status;
}

static u8 SPI_Read_REG(u8 u8reg)
{
    u8 u8val;
    NRF24L01_CS_LOW();

    SPI_RW(u8reg);
    u8val = SPI_RW(0);

    NRF24L01_CS_HIGH();
    return u8val;
}

u8 SPI_Write_Buf(u8 u8reg, u8 *pu8buf, u8 u8length)
{
    u8 u8status, i;
    NRF24L01_CS_LOW();

    u8status = SPI_RW( u8reg );
    for(i=0; i < u8length; i++)
    {
        SPI_RW(*pu8buf++);
    }

    NRF24L01_CS_HIGH();
    return u8status;
}

u8 SPI_Read_Buf(u8 u8reg, u8 *pu8buf, u8 u8length)
{
    u8 u8status, i;
    NRF24L01_CS_LOW();

    u8status = SPI_RW( u8reg );
    for(i=0; i < u8length; i++)
    {
        pu8buf[i] = SPI_RW(0);
    }

    NRF24L01_CS_HIGH();
    return u8status;
}

void NRF24L01_RX_Initialize(void)
{
    NRF24L01_CE_LOW();

    // Config the NRF24L01 Address
    SPI_Write_Buf(WRITE_REG + TX_ADDR,      TX_ADDRESS, TX_ADR_WIDTH);
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0,   RX_ADDRESS, TX_ADR_WIDTH);

    SPI_Write_REG(WRITE_REG + EN_AA,    0x01);
    SPI_Write_REG(WRITE_REG + EN_RXADDR,0x01);
    SPI_Write_REG(WRITE_REG + RF_CH,    40);
    SPI_Write_REG(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
    SPI_Write_REG(WRITE_REG + RF_SETUP, 0x07);
    SPI_Write_REG(WRITE_REG + CONFIG,   0x0f);

    NRF24L01_CE_HIGH();
    Delay_nus(130);
}

void NRF24L01_TX_Initialize(void)
{
    NRF24L01_CE_LOW();
    SPI_Write_REG(WRITE_REG + CONFIG,   0x02);

    // Config the NRF24L01 Address
    SPI_Write_Buf(WRITE_REG + TX_ADDR,      TX_ADDRESS, TX_ADR_WIDTH);
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0,   RX_ADDRESS, TX_ADR_WIDTH);

    SPI_Write_REG(WRITE_REG + EN_AA,        0x01);
    SPI_Write_REG(WRITE_REG + EN_RXADDR,    0x01);
    SPI_Write_REG(WRITE_REG + SETUP_RETR,   0x1a);
    SPI_Write_REG(WRITE_REG + RF_CH,        40);
    SPI_Write_REG(WRITE_REG + RF_SETUP,     0x07);
    SPI_Write_REG(WRITE_REG + CONFIG,       0x0e);

    NRF24L01_CE_HIGH();
    Delay_nus(130);
}

u8 NRF24L01_Recieve_Packet(u8 *pu8buf, u8 u8length)
{
    u8 u8RevSta = 0, u8RegSta;
    u8RegSta = SPI_Read_REG(STATUS);
    if( RESET != (u8RegSta & 0x40) )
    {
        NRF24L01_CE_LOW();
        SPI_Read_Buf(RD_RX_PLOAD, pu8buf,  u8length);
        SPI_Write_REG(WRITE_REG+STATUS,0xff);

        NRF24L01_CS_LOW();
        SPI_RW(FLUSH_RX);
        NRF24L01_CS_HIGH();

        u8RevSta = 1;
    }else{
        u8RevSta = 0;
    }
    SPI_Write_REG(WRITE_REG + STATUS, u8RegSta);
    return u8RevSta;
}

u8 NRF24L01_Send_Packet(u8 *pu8buf, u8 u8length)
{
    NRF24L01_CE_LOW();
    SPI_Write_Buf(WR_TX_PLOAD, pu8buf, u8length);
    NRF24L01_CE_HIGH();
    Delay_nus(10);
}

u8 NRF24L01_Check_Ack( void )
{
    u8 u8sta = 0;
    u8sta = SPI_Read_REG(READ_REG + STATUS);
    if( (u8sta&0x20) || (u8sta&0x10) )
    {
        SPI_Write_REG(WRITE_REG+STATUS, 0xff);
        NRF24L01_CS_LOW();
        SPI_RW(FLUSH_TX);
        return 0; // send successfully
    }
    else
    {
        return 1; // send failed
    }
}

u8 NRF24L01_Check_Device( void )
{
    u8 buf_w[5] = {0xa2,0xa3, 0xa4, 0xa5, 0xa6};
    u8 buf_r[5] = {0x00,};
    u8 i = 0;
    SPI_Write_Buf(TX_ADDR, buf_w, 5);
    SPI_Read_Buf( TX_ADDR, buf_r, 5);
    for( i = 0; i < 5; i++ )
    {
        if(buf_w[i] != buf_r[i])
        {
            return 1;
        }
    }
    return 0;
}
