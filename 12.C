#include "reg51.h"			 
#include <intrins.h>

typedef unsigned int uint;	  //对数据类型进行声明定义
typedef unsigned char uchar;

//参考：https://www.cnblogs.com/lulipro/p/5067835.html
sbit SRCLK=P3^6; //移位寄存器时钟引脚，上升沿时，移位寄存器中的bit 数据整体后移，并接受新的bit（从SER输入）
sbit RCLK=P3^5; //存储寄存器时钟输入引脚。上升沿时，数据从移位寄存器转存带存储寄存器。
sbit SER=P3^4; //DS（SER），串行数据输入引脚

uchar wei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//从0111 1111 到 1111 1110 从 第一列上电 到 最后一列
uchar num,n;

unsigned char code digittab[16][10]={ {0x7c,0xfe,0x82,0x82,0x82,0xfe,0x7c,0x00},//0
																		{0x02,0x42,0xfe,0xfe,0x02,0x02,0x00,0x00},//1
																		{0x46,0xce,0x9a,0x92,0xf6,0x66,0x00,0x00},//2
																		{0x44,0xc6,0x92,0x92,0xfe,0x6c,0x00,0x00},//3
																		{0x18,0x38,0x68,0xca,0xfe,0xfe,0x0a,0x00},//4
																		{0xe4,0xe6,0xa2,0xa2,0xbe,0x9c,0x00,0x00},//5
																		{0x3c,0x7e,0xd2,0x92,0x9e,0x0c,0x00,0x00},//6
																		{0xc0,0xc0,0x8e,0x9e,0xf0,0xe0,0x00,0x00},//7
																		{0x6c,0xfe,0x92,0x92,0xfe,0x6c,0x00,0x00},//8
																		{0x60,0xf2,0x92,0x96,0xfc,0x78,0x00,0x00},//9
																		{0x3e,0x7e,0xc8,0xc8,0x7e,0x3e,0x00,0x00},//A
																		{0x82,0xfe,0xfe,0x92,0x92,0xfe,0x6c,0x00},//B
																		{0x38,0x7c,0xc6,0x82,0x82,0xc6,0x44,0x00},//C
																		{0x82,0xfe,0xfe,0x82,0xc6,0x7c,0x38,0x00},//D
																		{0x00,0xfe,0xfe,0x92,0x92,0x82,0x82,0x00},//E
																		{0x00,0xfe,0xfe,0x90,0x90,0x80,0x80,0x00}//F
                                    };//8*8显示0-F
void delay(uint z)
{//延时函数
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

																		
uchar keyscan()
{//扫描用户输入
		//检测第一行键盘
		uchar temp;
		P1=0xfe;//1111 1110
		temp=P1;//取值
		temp=temp&0xf0;//逻辑与 P1与1111 0000
		while(temp!=0xf0)
		{//如果被按下
				delay(5);//延时5ms
				temp=P1;//取值
				temp=temp&0xf0;//逻辑与 P1与1111 0000
				while(temp!=0xf0)
				{//持续被按下
						temp=P1;//取值
						switch(temp)
						{//执行动作
							case 0xee:num=1;//1110 1110
								break;
							case 0xde:num=2;//1101 1110
								break;
							case 0xbe:num=3;//1011 1110
								break;
							case 0x7e:num=4;//0111 1110
								break;
						}
						while(temp!=0xf0)
						{//等待释放
							temp=P1;//取值
							temp=temp&0xf0;//逻辑与 P1与1111 0000
						}
				}
		}
		//检测第二行键盘
		P1=0xfd;//1111 1101
		temp=P1;//取值
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P1;
						switch(temp)
						{
							case 0xed:num=5;//1110 1101
								break;
							case 0xdd:num=6;//1101 1101
								break;
							case 0xbd:num=7;//1011 1101
								break;
							case 0x7d:num=8;//0111 1101
								break;
						}
						while(temp!=0xf0)
						{
							temp=P1;
							temp=temp&0xf0;
						}
				}
		}
		//检测第三行键盘
		P1=0xfb;//1111 1011
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P1;
						switch(temp)
						{
							case 0xeb:num=9;//1110 1011
								break;
							case 0xdb:num=10;//1101 1011
								break;
							case 0xbb:num=11;//1011 1011
								break;
							case 0x7b:num=12;//0111 1011
								break;
						}
						while(temp!=0xf0)
						{
							temp=P1;
							temp=temp&0xf0;
						}
				}
		}
		//检测第四行键盘
		P1=0xf7;//1111 0111
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P1;
						switch(temp)
						{
							case 0xe7:num=13;//‭1110 0111‬
								break;
							case 0xd7:num=14;//1101 0111
								break;
							case 0xb7:num=15;//1011 0111
								break;
							case 0x77:num=16;//0111 0111
								break;
						}
						while(temp!=0xf0)
						{
							temp=P1;
							temp=temp&0xf0;
						}
				}
		}
		return num;
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
		uchar i,n;
		while(1)
		{
				n=keyscan()-1;
				for(i=0;i<8;i++)
				{
						P0=wei[i];		  //位选
						HC595(digittab[n][i]);	//发送段选数据
						delay(0.5);		   //延时
						HC595(0x00);  //消隐
				}	
		}		
}
