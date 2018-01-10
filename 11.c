#include "reg51.h"			 
#include <intrins.h>

typedef unsigned int uint;	  //对数据类型进行声明定义
typedef unsigned char uchar;

//参考：https://www.cnblogs.com/lulipro/p/5067835.html
sbit SRCLK=P3^6; //移位寄存器时钟引脚，上升沿时，移位寄存器中的bit 数据整体后移，并接受新的bit（从SER输入）
sbit RCLK=P3^5; //存储寄存器时钟输入引脚。上升沿时，数据从移位寄存器转存带存储寄存器。
sbit SER=P3^4; //DS（SER），串行数据输入引脚

uchar duan[]={0x88,0x50,0x21,0x01,0x01,0x21,0x50,0x88};//段选相当于点亮那个灯
uchar wei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//从0111 1111 到 1111 1110 从 第一列上电 到 最后一列

void delay(uint z)
{//延时函数
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}


void HC595(uchar dat)
{//8Bit(1Byte)送到74HC595
		uchar a;
		SRCLK=0;//移位寄存器时钟引脚低电平
		RCLK=0;//存储寄存器时钟引脚低电平
		for(a=0;a<8;a++)
		{
				//取输入8Bit(1Byte)最后一位先进入
				//相当于栈储存的,但是输出是并发的,即8Bit(1Byte)输出。
				//输入是每次1Bit，并行
				SER=dat>>7;
				dat<<=1;//dat=dat<<1;
				
				/*进行移位寄存器移位动作*/
				SRCLK=1;
				_nop_();//等待1us
				_nop_();//等待1us
				SRCLK=0;	
		}
		/*进行移位寄存器进入存储寄存器动作*/
		RCLK=1;
		_nop_();//等待1us
		_nop_();//等待1us
		RCLK=0;
}


void main()
{			
		uchar i;
		while(1)
		{
				P0=0x7f;//0111 1111 
				for(i=0;i<8;i++)
				{
						P0=wei[i];		  //位选
						HC595(duan[i]);	//发送段选数据
						delay(0.5);		   //延时
						HC595(0x00);  //消隐
				}	
		}		
}
