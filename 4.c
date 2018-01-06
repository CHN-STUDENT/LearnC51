#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int 
sbit led1=P1^0;
uchar num;
//参考http://bbs.elecfans.com/jishu_216681_1_1.html
/*TMOD工作模式
	M1 M0
	0  0 	方式0 13位定时器
	0  1	方式1 16位定时器
	常用TMOD=0x01
*/
/*机器周期T(us)=FOSC(定时器时钟)*1/频率(Hz);
	例如STC89定时器时钟12T，晶振11.0592MHZ
	50ms初值 N=50000/(12*(1/11059200))=45872;*/
//其中TH0高8位代表的是有多少个256,TL0低8位是不足256部分
void main()
{
		TMOD=0x01;//16位工作模式？
		TH0=(65536-45872)/256;
		TL0=(65536-45872)%256;
		EA=1;	//总中断打开
		ET0=1;	//开定时器0中断
		TR0=1;	//启动定时器0
		while(1)
		{
			if(num==20)
			{
					num=0;
					led1=~led1;//取反led1=led1
			}
		}
}

void T0_time() interrupt 1
{
		TH0=(65536-45872)/256;
		TL0=(65536-45872)%256;
		num++;
}
