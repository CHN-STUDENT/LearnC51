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
		aa=0xfe;
		while(aa!=0x7f)//11111110
		{
				P1=aa;
				delay(500);
				aa=_crol_(aa,1);//aa=aa<<1;左移一位
		}
		while(aa!=0xfe)//01111111
		{
				P1=aa;
				delay(500);
				aa=_cror_(aa,1);//aa=aa>>1;右移一位
		}
}
