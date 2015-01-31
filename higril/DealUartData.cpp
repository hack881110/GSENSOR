#include "DealUartData.h"
#include "windows.h"

//A5 5A 12 A1 80 01 00 00 00 00 00 00 00 00 00 00 00 00 34 AA

/*
//Z轴正方向为前进方向

pitch()：俯仰，将物体绕X轴旋转（localRotationX）

yaw()：航向，将物体绕Y轴旋转（localRotationY）

roll()：横滚，将物体绕Z轴旋转（localRotationZ）
*/

/* 
编写者：lisn3188
网址：www.chiplab7.com
作者E-mail：lisn3188@163.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2012-05-25
测试： 本程序已在第七实验室的mini IMU上完成测试
功能：
使用串行中断程序接收mini IMU 的数据。
移植者需在自己编写对应的串口初始化程序，并开启接收中断。
在中断子程序中 需要做相应的改动

为了使用这个程序，你需要：
1.初始化你的串口，将波特率与模块的波特率设置成一致的
2.开启串口的接收中断，并参考以下程序编写中断子程序
  参考 void USART2_IRQHandler(void) 
3.在主程序的循环体中，定时调用子程序：
  void UART2_CommandRoute(void)
  以检查是否收到新的数据帧
  所有的姿态数据和ADC值都会在 UART2_CommandRoute
  中进行更新。
4.使用 以下值会自动更新：

float 	yaw,  //偏航角
		pitch,//俯仰
		roll, //滚转
		alt,  //高度
		tempr,//温度
		press;//气压
int16_t ax, ay, az;//加速度计
int16_t gx, gy, gz;//陀螺仪
int16_t hx, hy, hz;//磁力计
------------------------------------
*/
 




//uart reicer flag

typedef unsigned short int16_t;          


#define b_uart_head  0x80  //收到A5 头 标志位
#define b_rx_over    0x40  //收到完整的帧标志
// USART Receiver buffer


CHAR Rx_buffer[RX_BUFFER_SIZE]; //接收数据缓冲区

CHAR *pHeadofRx_Buffer=NULL;
CHAR *pTailofRx_Buffer=NULL;
short iEndFlag0fRx_Buffer=0;

volatile unsigned char rx_wr_index; //缓冲写指针
volatile unsigned char RC_Flag;  //接收状态标志字节

//解算后的角度值
float 	yaw=0,  //偏航角
		pitch=0,//俯仰
		roll=0, //滚转
		alt,  //高度
		tempr,//温度
		press;//气压

int k1=1;
int k2=1;
int k3=1;

//ADC值
int16_t ax, ay, az;//加速度计
int16_t gx, gy, gz;//陀螺仪
int16_t hx, hy, hz;//磁力计
//GPS位置信息
float GPS_Altitude , //天线离海平面的高度，-9999.9到9999.9米
	  Latitude_GPS , //纬度	 单位为度
	  Longitude_GPS , //经度  单位为度
	  Speed_GPS , //地面速率  单位  米每秒
	  Course_GPS ; //地面航向（000.0~359.9度，以真北为参考基准)
unsigned char GPS_STA_Num ;

DWORD WINAPI SerialDealData(LPVOID lpParam)
{
	while(1)
	{

		
		
	}
	return 0;
}

int iAscToBcd(char *pcASC,char *pcBCD,int iLength)
{
	int i;
	for(i=0;i<iLength/2;i++)
	{
		char ch1,ch2,ch3;
		ch1=(unsigned char)pcASC[i*2];
		ch2=(unsigned char)pcASC[i*2+1];
		if(ch1>='a' && ch1<='f')
			ch1=ch1-'a'+0xa;
		else if(ch1>='A' && ch1<='F')
			ch1=ch1-'A'+0xa;
		else
			ch1=ch1-'0';
		if(ch2>='a' && ch2<='f')
			ch2=ch2-'a'+0xa;
		else if(ch2>='A' && ch2<='F')
			ch2=ch2-'A'+0xa;
		else
			ch2=ch2-'0';

		ch3=ch1<<4;
		pcBCD[i]=(ch3)|ch2;
	}
	return(0);
}
/*
bool Check_Data_Invalid()
{
	
	if(rx_buffer[0]==0xa5&&rx_buffer[1]==0x5a&&rx_buffer[2]==0x12&&rx_buffer[3]==0xa1)
		return TRUE;
	else
		return FALSE;
}
*/
//在接收完一帧IMU姿态报告后，调用这个子程序来取出姿态数据
//A5 5A 12 A1 80 03 00 00 00 00 00 00 00 00 00 00 00 00 36 AA 
void UART2_Get_IMU(char *rx_buffer)
{
	short temp=0;
	
	temp = 0;
	temp = rx_buffer[4]&0x00ff;
	temp <<= 8;
	temp |= (rx_buffer[5]&0x00ff);
	if(temp&0x8000){
		temp = (temp&0x7fff);
		k1=-1;
	}else 
	{temp = abs((temp&0x7fff));
		k1=1;
		}
	yaw=(float)temp / 10.0f; //偏航角
	
	temp = 0;
	temp = rx_buffer[6]&0x00ff;
	temp <<= 8;
	temp |= (rx_buffer[7]&0x00ff);
	if(temp&0x8000){
		temp = (temp&0x7fff);
		k2=-1;
	}else
		{temp = abs((temp&0x7fff));
	k2=1;
	}
	pitch=(float)temp / 10.0f;//俯仰
	//俯仰
	
	temp = 0;
	temp = (rx_buffer[8]&0x00ff);
	temp <<= 8;
	temp |= (rx_buffer[9]&0x00ff);
	if(temp&0x8000){
		temp =(temp&0x7fff);
		k3=-1;
	}else
		{temp = abs((temp&0x7fff));
	k3=1;
	}

	roll=(float)temp / 10.0f;//滚转
	//滚转



}
/*

//在接收一帧ReportMotion 后调用这个子程序来取出ADC数据
void UART2_Get_Motion()
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ax=temp;//加速度计 X轴的ADC值
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//加速度计 Y轴的ADC值
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//加速度计 Z轴的ADC值
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//陀螺仪 X轴的ADC值
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//陀螺仪 Y轴的ADC值
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//陀螺仪 Z轴的ADC值
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//磁力计 X轴的ADC值
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//磁力计 Y轴的ADC值
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//磁力计 Z轴的ADC值
}

//在接收完一帧GPS位置报告后，调用这个子程序来取出姿态数据
void UART2_Get_GPS(char* rx_buffer)
{
	long int temp;
	//经度值，单位0.0001度。当传送的值为 1234567  表示 123.4567度
	temp = 0;
	temp = ((long int)rx_buffer[2]<<24);
	temp |= ((long int)rx_buffer[3]<<16);
	temp |= ((long int)rx_buffer[4]<<8);
	temp |= ((long int)rx_buffer[5]); 
	Longitude_GPS = ((float)temp) / ((float)10000.0);
	//纬度值，单位0.0001度。当传送的值为 123456  表示  12.4567度
	temp = 0;
	temp = ((long int)rx_buffer[6]<<24);
	temp |= ((long int)rx_buffer[7]<<16);
	temp |= ((long int)rx_buffer[8]<<8);
	temp |= ((long int)rx_buffer[9]);
	Latitude_GPS = ((float)temp) / ((float)10000.0);
	//GPS海拔高度值，单位0.1米。当传送值为 1623  表示当前海拔为 162.3米
	temp = 0;
	temp |= ((long int)rx_buffer[10]<<8);
	temp |= ((long int)rx_buffer[11]);
	GPS_Altitude = ((float)temp) / ((float)10.0);
	//锁定的卫星数量， 0 表示没有定位、
	GPS_STA_Num = rx_buffer[12];
	//GPS航向值，单位0.1度。当传送值为 125时，表示12.5度。
	temp = 0;
	temp |= ((long int)rx_buffer[13]<<8);
	temp |= ((long int)rx_buffer[14]);
	Course_GPS = ((float)temp) / ((float)10.0);
	//GPS速度，单位0.1米/S  当传送的值为 255时，表示 25.5M/S
	temp = 0;
	temp |= ((long int)rx_buffer[15]<<8);
	temp |= ((long int)rx_buffer[16]);
	Speed_GPS = ((float)temp) / ((float)10.0);

}

//以下中断子程序是基于STM32的，如果你使用的不是STM32 请做相应的修改
//------------------------------------------------------
void USART2_IRQHandler(void) //接收中断子程序
{
  unsigned char data;
 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //是否收到数据?
  {
  data=USART_ReceiveData(USART2); //读取接收到的字节
  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //如果接收到A5 置位帧头标专位
    rx_buffer[rx_wr_index++]=data; //保存这个字节.
  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //如果上一个字节是A5 那么认定 这个是帧起始字节
	     { rx_wr_index=0;  //重置 缓冲区指针
		   RC_Flag&=~b_rx_over; //这个帧才刚刚开始收
         }
         else //上一个字节不是A5
		  rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //清帧头标志
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //收够了字节数.
	     {  
			RC_Flag|=b_rx_over; //置位 接收完整的一帧数据
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //防止缓冲区溢出
  rx_wr_index--;
  //Clear the USART2 Recive interrupt 
  USART_ClearITPendingBit(USART2, USART_IT_RXNE); //清中断标志.
  }
  
}
*/

//--校验当前接收到的一帧数据是否 与帧校验字节一致
unsigned char Sum_check(char* rx_buffer)
{ 
  unsigned char i;
  unsigned int checksum=0; 
  for(i=0;i<rx_buffer[0]-2;i++)
   checksum+=rx_buffer[i];
  if((checksum%256)==rx_buffer[rx_buffer[0]-2])
   return(0x01); //Checksum successful
  else
   return(0x00); //Checksum error
}


/*
//--这个子程序需要在主程序中 定时调用,以检查 串口是否接收完一帧数据
void UART2_CommandRoute(void)
{
 if(RC_Flag&b_rx_over){  //已经接收完一帧?
		RC_Flag&=~b_rx_over; //清标志先
		if(Sum_check()){ 
		//校验通过
		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU 的数据
		 UART2_Get_IMU();	//取数据
		}
		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion 的数据
		 UART2_Get_Motion();	 //取数据
		} 
		if(rx_buffer[1]==0xA3){ //UART2_ReportPosition 的数据
			UART2_Get_GPS();	 //取数据
		} 
		}//校验是否通过?
	}
}

*/
