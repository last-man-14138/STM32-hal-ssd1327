
#include "i2c.h"
#include "stm32f4xx_hal.h" 


//******************************************************************
//函数名称： IIC_Start
//功能：    开启IIC总线
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void IIC_Start(void)
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

//******************************************************************
//函数名称： IIC_Stop
//功能：    停止IIC总线
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void IIC_Stop(void)
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

//******************************************************************
//函数名称： IIC_Wait_Ack
//功能：    等待IIC从设备应答
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void IIC_Wait_Ack(void)
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}

//******************************************************************
//函数名称： Write_IIC_Byte
//功能：    通过IIC写入一个字节数据
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}

//******************************************************************
//函数名称： Write_IIC_Command
//功能：    通过IIC写入命令
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(IIC_SLAVE_ADDR);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}

//******************************************************************
//函数名称： Write_IIC_Data
//功能：    通过IIC写入数据
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(IIC_SLAVE_ADDR);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
  IIC_Stop();
}

