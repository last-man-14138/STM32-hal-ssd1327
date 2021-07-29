
//********************************************************************************
//=========================================电源接线================================================//
//    OLED模块             单片机
//      5V        接    DC5V或3.3V电源
//      GND       接        GND                        
//======================================OLED屏数据线接线==========================================//
//本模块数据总线类型为IIC
//    OLED模块             单片机
//      SCL       接        PB13     // IIC时钟信号
//      SDA       接        PB14     // IIC数据信号
//======================================OLED屏控制线接线==========================================//
//本模块数据总线类型为IIC，不需要接控制信号线    
//=========================================触摸屏接线=========================================//
//本模块本身不带触摸，不需要接触摸屏线
//============================================================================================//
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f4xx_hal.h"
#include "stdlib.h"	
#include "i2c.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		128
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	128	    						  
		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);     							   		    
void OLED_Init(void);
void OLED_Clear(uint8_t dat); 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
void OLED_transfer_col_data(unsigned char data1,unsigned char data2);
void OLED_transfer_col_data2(unsigned char data1,unsigned char data2,unsigned char gray_value);
void display_full_gray(uint8_t data1); 
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void LCD_SetContrast(uint16_t arr);
#endif
