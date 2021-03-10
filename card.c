/************************************************************************************
*刷指定卡片，点亮LED1
*************************************************************************************/

#include<reg52.h>
#include<card.h>
#define unit unsigned int
#define on 0
#define off 1

	xdata CMD Cmd;
	sbit led1 = P1^0;
	sbit led2 = P1^1;
	sbit led3 = P1^2;
	sbit led4 = P1^3;
	sbit led5 = P1^4;
	sbit led6 = P1^5;
	sbit led7 = P1^6;
	sbit led8 = P1^7;
void delay(unit xms)//延时函数
{
	unit i,j;
	for(i=xms;i>0;i--)
		for(j=122;j>0;j--);
}
void UsartConfiguration()//串口参数配置函数
{
	SCON = 0X50;	//设置为工作方式1
	TMOD = 0X20;	//设置计数器工作方式2
	PCON = 0X00;	//SMOD=0,32分频
	TH1 = 0Xfd;	//计数器初始值设置，波特率为9600bit/s
	TL1 = 0Xfd;
	ES = 1;		//打开接收中断
	EA = 1;		//打开总中断
	TR1 = 1;	//打开计数器
}


void ControlLED(unsigned char* a)//灯控函数
{
	if(a[12] == 0x84&a[13] == 0x36)
	{
		led1 = ~led1;
	}
}

void main()//主函数
{
	UsartConfiguration();
	while(1);	
}       

void Uart() interrupt 4	//串口中断函数
{
	static unsigned char date;
	date = 	SBUF;
	RI = 0;
	if(date == 0x7F)
	{
		Cmd.ReceivePoint = 0;		
	}
	Cmd.ReceiveBuffer[Cmd.ReceivePoint++] = date;
	if(Cmd.ReceivePoint == 14)
	{
		ControlLED(Cmd.ReceiveBuffer);
	}
	if(TI){TI = 0;}
}
