#include<reg52.h>            //头文件
#define uint unsigned int    
#define uchar unsigned char 

sbit H=P2^3;

void delay(uint xms)
{//延时函数
		uint i,j;
		for(i=xms;i>0;i--)
			for(j=110;j>0;j--);
}

void main()
{
		while(1)
		{
				H=1;//高电平发声
				delay(20);
				H=0;
				delay(20);
		}
}
