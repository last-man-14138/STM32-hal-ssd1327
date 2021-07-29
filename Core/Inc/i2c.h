
#ifndef __I2C_H__
#define __I2C_H__

#include "gpio.h"

//-----------------OLED IIC????----------------  					   
//#define GPIO_TYPE GPIOB  //IIC GPIO??
//#define OLED_SCLK GPIO_Pin_13  //IIC????
//#define OLED_SDIN GPIO_Pin_14  //IIC????

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13, GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)

#define IIC_SLAVE_ADDR 0x78  //IIC slave device address

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Wait_Ack(void);
void Write_IIC_Byte(unsigned char IIC_Byte);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
#endif
