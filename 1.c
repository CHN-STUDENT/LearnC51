#include <reg52.h>
#include <intrins.h>
#define uint unsigned int 
#define uchar unsigned char 
uchar aa;
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
				P1=0x7e;//0111 1110
				delay(500);
				P1=0xbd;//1011 1101
				delay(500);
				P1=0xdb;//1101 1011
				delay(500);
				P1=0xe7;//1110 0111
				delay(500);
				P1=0xdb;//1101 1011
				delay(500);
				P1=0xbd;//1011 1101
				delay(500);
		}
}
