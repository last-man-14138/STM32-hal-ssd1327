
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


#include "oled.h"
#include "i2c.h"
#include "stdlib.h"	 
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 	
		   
//******************************************************************
//函数名：  OLED_WR_Byte
    
    
//功能：    通过IIC数据总线写入一个字节数据
//输入参数：dat：待写入的数据
//          cmd：0-命令，1-数据
//返回值：  无
//修改记录：无
//******************************************************************
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
  }
	else 
	{
		Write_IIC_Command(dat);		
	}
}



//******************************************************************
//函数名：  OLED_Set_Pos
//功能：    设置点坐标
//输入参数：x,y：坐标值，一个x表示2列
//返回值：  无
//修改记录：无
//******************************************************************
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0x75,OLED_CMD);
	OLED_WR_Byte(x,OLED_CMD);
	OLED_WR_Byte(x+7,OLED_CMD);

	OLED_WR_Byte(0x15,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
}   	  
	   			 
//******************************************************************
//函数名：  OLED_Clear
//功能：    清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
//输入参数：dat：0-黑色，0xFF-白色
//返回值：  无
//修改记录：无
//******************************************************************	  
void OLED_Clear(uint8_t dat)  
{  
	unsigned int i,j;
  OLED_WR_Byte(0x15,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x3f,OLED_CMD);

  OLED_WR_Byte(0x75,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x7f,OLED_CMD);

	for(i=0;i<128;i++) 
  {
    for(j=0;j<64;j++)
     {
      OLED_WR_Byte(dat,OLED_DATA);//RAM data write
     }
  }
}

//******************************************************************
//函数名：  OLED_SetWindows
//功能：    设置显示窗口  
//输入参数：xStart、yStart：窗口起点坐标
//          xEnd、yEnd：窗口终点坐标
//返回值：  无
//修改记录：无
//******************************************************************
void OLED_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{
	OLED_WR_Byte(0x15,OLED_CMD);
	OLED_WR_Byte(xStar,OLED_CMD);
	OLED_WR_Byte(xEnd,OLED_CMD);

	OLED_WR_Byte(0x75,OLED_CMD);
	OLED_WR_Byte(yStar,OLED_CMD);
	OLED_WR_Byte(yEnd,OLED_CMD);
}

//******************************************************************
//函数名：  LCD_SetContrast
//功能：    设置整体灰度值  
//输入参数：arr：灰度值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_SetContrast(uint16_t arr)
{
	 OLED_WR_Byte(0x81,OLED_CMD);  // set contrast control
   OLED_WR_Byte(arr,OLED_CMD);
}

//******************************************************************
//函数名：  OLED_transfer_col_data
//功能：    设置点坐标颜色值	  
//输入参数：data1：第一个点颜色数据
//          data2：第二个点颜色数据
//返回值：  无
//修改记录：无
//****************************************************************** 
void OLED_transfer_col_data(unsigned char data1,unsigned char data2)
{
  unsigned char i; 
	 	for(i=0;i<8;i++)
	{
          if ((data1& 0x01)&&(data2& 0x01))	
		    { 	
		  			OLED_WR_Byte(0xFF,OLED_DATA);              //4BIT表示亮度，可以设置0~F，16级灰度
							//LCD_WR_DATA(0xF8);              //4BIT表示亮度，可以设置0~F，16级灰度
			  }
        else  if  ((data1& 0x01)==1&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0xF0,OLED_DATA);   
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==1)				
		    {
			       
              OLED_WR_Byte(0x0F,OLED_DATA);  
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0x00,OLED_DATA);  
        }
 
        data1>>= 1;
        data2>>= 1;
    }
  
}

//******************************************************************
//函数名：  OLED_transfer_col_data2
//功能：    设置点坐标颜色值	  
//输入参数：data1：第一个点颜色数据
//          data2：第二个点颜色数据
//					gray_value：灰度值
//返回值：  无
//修改记录：无
//****************************************************************** 
void OLED_transfer_col_data2(unsigned char data1,unsigned char data2,unsigned char gray_value)
{
  unsigned char i; 
	 	for(i=0;i<8;i++)
	{
          if ((data1& 0x01)&&(data2& 0x01))	
		    { 	
						OLED_WR_Byte((gray_value<<4)|gray_value,OLED_DATA);//4BIT表示亮度，可以设置0~F，16级灰度		  			            
			  }
        else  if  ((data1& 0x01)==1&&(data2& 0x01)==0)				
		    {
			       OLED_WR_Byte((gray_value<<4)&0xF0,OLED_DATA); 
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==1)				
		    {
			       OLED_WR_Byte((gray_value)&0x0F,OLED_DATA);   
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0x00,OLED_DATA);  
        }
        data1>>= 1;
        data2>>= 1;
    } 
}

//******************************************************************
//函数名：  display_full_gray
//功能：    显示全屏灰度值  
//输入参数：data1：灰度值
//返回值：  无
//修改记录：无
//****************************************************************** 
void display_full_gray(uint8_t data1)
{
  int i,j;
  OLED_WR_Byte(0x15,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x3f,OLED_CMD);

  OLED_WR_Byte(0x75,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x7f,OLED_CMD);
  for(i=0;i<128;i++) 
  {
    for(j=0;j<64;j++)
     {
      OLED_WR_Byte(data1,OLED_DATA);
     }
  }

}

//******************************************************************
//函数名：  OLED_Init
//功能：    初始化SSD1327	  
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 				    
void OLED_Init(void)
{ 		 
	MX_GPIO_Init();
	HAL_Delay(200);
	OLED_WR_Byte(0xae,OLED_CMD);     //display off

   OLED_WR_Byte(0x15,OLED_CMD);    //   set column address
   OLED_WR_Byte(0x00,OLED_CMD);    //  start column   0
   OLED_WR_Byte(0x7f,OLED_CMD);    //  end column   127

   OLED_WR_Byte(0x75,OLED_CMD);    //   set row address
   OLED_WR_Byte(0x00,OLED_CMD);    //  start row   0
   OLED_WR_Byte(0x7f,OLED_CMD);    //  end row   127
   OLED_WR_Byte(0x81,OLED_CMD);  // set contrast control
   OLED_WR_Byte(0x80,OLED_CMD);
   OLED_WR_Byte(0xa0,OLED_CMD);    // gment remap
   OLED_WR_Byte(0x51,OLED_CMD);   //
   OLED_WR_Byte(0xa1,OLED_CMD);  // start line
   OLED_WR_Byte(0x00,OLED_CMD);
   OLED_WR_Byte(0xa2,OLED_CMD);  // display offset
   OLED_WR_Byte(0x00,OLED_CMD);
   OLED_WR_Byte(0xa4,OLED_CMD);    // rmal display
   OLED_WR_Byte(0xa8,OLED_CMD);    // set multiplex ratio
   OLED_WR_Byte(0x7f,OLED_CMD); 
   OLED_WR_Byte(0xb1,OLED_CMD);  // set phase leghth
   OLED_WR_Byte(0xf1,OLED_CMD);
   OLED_WR_Byte(0xb3,OLED_CMD);  // set dclk
   OLED_WR_Byte(0x00,OLED_CMD);  //80Hz:0xc1 90Hz:0xe1   100Hz:0x00   110Hz:0x30 120Hz:0x50   130Hz:0x70     01
   OLED_WR_Byte(0xab,OLED_CMD);  // 
   OLED_WR_Byte(0x01,OLED_CMD);  //
   OLED_WR_Byte(0xb6,OLED_CMD);  // set phase leghth
   OLED_WR_Byte(0x0f,OLED_CMD);
   OLED_WR_Byte(0xbe,OLED_CMD);
   OLED_WR_Byte(0x0f,OLED_CMD);
   OLED_WR_Byte(0xbc,OLED_CMD);
   OLED_WR_Byte(0x08,OLED_CMD);
   OLED_WR_Byte(0xd5,OLED_CMD);
   OLED_WR_Byte(0x62,OLED_CMD);  
   OLED_WR_Byte(0xfd,OLED_CMD);
   OLED_WR_Byte(0x12,OLED_CMD);
   OLED_WR_Byte(0xaf,OLED_CMD); 
	 
}  





























