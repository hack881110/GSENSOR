#include "DealUartData.h"
#include "windows.h"

//A5 5A 12 A1 80 01 00 00 00 00 00 00 00 00 00 00 00 00 34 AA

/*
//Z��������Ϊǰ������

pitch()����������������X����ת��localRotationX��

yaw()�����򣬽�������Y����ת��localRotationY��

roll()���������������Z����ת��localRotationZ��
*/

/* 
��д�ߣ�lisn3188
��ַ��www.chiplab7.com
����E-mail��lisn3188@163.com
���뻷����MDK-Lite  Version: 4.23
����ʱ��: 2012-05-25
���ԣ� ���������ڵ���ʵ���ҵ�mini IMU����ɲ���
���ܣ�
ʹ�ô����жϳ������mini IMU �����ݡ�
��ֲ�������Լ���д��Ӧ�Ĵ��ڳ�ʼ�����򣬲����������жϡ�
���ж��ӳ����� ��Ҫ����Ӧ�ĸĶ�

Ϊ��ʹ�������������Ҫ��
1.��ʼ����Ĵ��ڣ�����������ģ��Ĳ��������ó�һ�µ�
2.�������ڵĽ����жϣ����ο����³����д�ж��ӳ���
  �ο� void USART2_IRQHandler(void) 
3.���������ѭ�����У���ʱ�����ӳ���
  void UART2_CommandRoute(void)
  �Լ���Ƿ��յ��µ�����֡
  ���е���̬���ݺ�ADCֵ������ UART2_CommandRoute
  �н��и��¡�
4.ʹ�� ����ֵ���Զ����£�

float 	yaw,  //ƫ����
		pitch,//����
		roll, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ
int16_t ax, ay, az;//���ٶȼ�
int16_t gx, gy, gz;//������
int16_t hx, hy, hz;//������
------------------------------------
*/
 




//uart reicer flag

typedef unsigned short int16_t;          


#define b_uart_head  0x80  //�յ�A5 ͷ ��־λ
#define b_rx_over    0x40  //�յ�������֡��־
// USART Receiver buffer


CHAR Rx_buffer[RX_BUFFER_SIZE]; //�������ݻ�����

CHAR *pHeadofRx_Buffer=NULL;
CHAR *pTailofRx_Buffer=NULL;
short iEndFlag0fRx_Buffer=0;

volatile unsigned char rx_wr_index; //����дָ��
volatile unsigned char RC_Flag;  //����״̬��־�ֽ�

//�����ĽǶ�ֵ
float 	yaw=0,  //ƫ����
		pitch=0,//����
		roll=0, //��ת
		alt,  //�߶�
		tempr,//�¶�
		press;//��ѹ

int k1=1;
int k2=1;
int k3=1;

//ADCֵ
int16_t ax, ay, az;//���ٶȼ�
int16_t gx, gy, gz;//������
int16_t hx, hy, hz;//������
//GPSλ����Ϣ
float GPS_Altitude , //�����뺣ƽ��ĸ߶ȣ�-9999.9��9999.9��
	  Latitude_GPS , //γ��	 ��λΪ��
	  Longitude_GPS , //����  ��λΪ��
	  Speed_GPS , //��������  ��λ  ��ÿ��
	  Course_GPS ; //���溽��000.0~359.9�ȣ����汱Ϊ�ο���׼)
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
//�ڽ�����һ֡IMU��̬����󣬵�������ӳ�����ȡ����̬����
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
	yaw=(float)temp / 10.0f; //ƫ����
	
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
	pitch=(float)temp / 10.0f;//����
	//����
	
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

	roll=(float)temp / 10.0f;//��ת
	//��ת



}
/*

//�ڽ���һ֡ReportMotion ���������ӳ�����ȡ��ADC����
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
	ax=temp;//���ٶȼ� X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//���ٶȼ� Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//���ٶȼ� Z���ADCֵ
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//������ X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//������ Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//������ Z���ADCֵ
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//������ X���ADCֵ
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//������ Y���ADCֵ
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//������ Z���ADCֵ
}

//�ڽ�����һ֡GPSλ�ñ���󣬵�������ӳ�����ȡ����̬����
void UART2_Get_GPS(char* rx_buffer)
{
	long int temp;
	//����ֵ����λ0.0001�ȡ������͵�ֵΪ 1234567  ��ʾ 123.4567��
	temp = 0;
	temp = ((long int)rx_buffer[2]<<24);
	temp |= ((long int)rx_buffer[3]<<16);
	temp |= ((long int)rx_buffer[4]<<8);
	temp |= ((long int)rx_buffer[5]); 
	Longitude_GPS = ((float)temp) / ((float)10000.0);
	//γ��ֵ����λ0.0001�ȡ������͵�ֵΪ 123456  ��ʾ  12.4567��
	temp = 0;
	temp = ((long int)rx_buffer[6]<<24);
	temp |= ((long int)rx_buffer[7]<<16);
	temp |= ((long int)rx_buffer[8]<<8);
	temp |= ((long int)rx_buffer[9]);
	Latitude_GPS = ((float)temp) / ((float)10000.0);
	//GPS���θ߶�ֵ����λ0.1�ס�������ֵΪ 1623  ��ʾ��ǰ����Ϊ 162.3��
	temp = 0;
	temp |= ((long int)rx_buffer[10]<<8);
	temp |= ((long int)rx_buffer[11]);
	GPS_Altitude = ((float)temp) / ((float)10.0);
	//���������������� 0 ��ʾû�ж�λ��
	GPS_STA_Num = rx_buffer[12];
	//GPS����ֵ����λ0.1�ȡ�������ֵΪ 125ʱ����ʾ12.5�ȡ�
	temp = 0;
	temp |= ((long int)rx_buffer[13]<<8);
	temp |= ((long int)rx_buffer[14]);
	Course_GPS = ((float)temp) / ((float)10.0);
	//GPS�ٶȣ���λ0.1��/S  �����͵�ֵΪ 255ʱ����ʾ 25.5M/S
	temp = 0;
	temp |= ((long int)rx_buffer[15]<<8);
	temp |= ((long int)rx_buffer[16]);
	Speed_GPS = ((float)temp) / ((float)10.0);

}

//�����ж��ӳ����ǻ���STM32�ģ������ʹ�õĲ���STM32 ������Ӧ���޸�
//------------------------------------------------------
void USART2_IRQHandler(void) //�����ж��ӳ���
{
  unsigned char data;
 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�Ƿ��յ�����?
  {
  data=USART_ReceiveData(USART2); //��ȡ���յ����ֽ�
  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //������յ�A5 ��λ֡ͷ��רλ
    rx_buffer[rx_wr_index++]=data; //��������ֽ�.
  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //�����һ���ֽ���A5 ��ô�϶� �����֡��ʼ�ֽ�
	     { rx_wr_index=0;  //���� ������ָ��
		   RC_Flag&=~b_rx_over; //���֡�Ÿոտ�ʼ��
         }
         else //��һ���ֽڲ���A5
		  rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //��֡ͷ��־
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //�չ����ֽ���.
	     {  
			RC_Flag|=b_rx_over; //��λ ����������һ֡����
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //��ֹ���������
  rx_wr_index--;
  //Clear the USART2 Recive interrupt 
  USART_ClearITPendingBit(USART2, USART_IT_RXNE); //���жϱ�־.
  }
  
}
*/

//--У�鵱ǰ���յ���һ֡�����Ƿ� ��֡У���ֽ�һ��
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
//--����ӳ�����Ҫ���������� ��ʱ����,�Լ�� �����Ƿ������һ֡����
void UART2_CommandRoute(void)
{
 if(RC_Flag&b_rx_over){  //�Ѿ�������һ֡?
		RC_Flag&=~b_rx_over; //���־��
		if(Sum_check()){ 
		//У��ͨ��
		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU ������
		 UART2_Get_IMU();	//ȡ����
		}
		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion ������
		 UART2_Get_Motion();	 //ȡ����
		} 
		if(rx_buffer[1]==0xA3){ //UART2_ReportPosition ������
			UART2_Get_GPS();	 //ȡ����
		} 
		}//У���Ƿ�ͨ��?
	}
}

*/
