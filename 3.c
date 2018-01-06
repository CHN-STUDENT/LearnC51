#include<reg52.h>
sbit dula=P2^6;
sbit wela=P2^7;
#define uchar unsigned char 
#define uint unsigned int 
//位选wela指的几组8段数码管，可以独立控制
//段选dula指的8段数码管每一段，连在一起
//共阴极8段数码管显示0-9
uchar i;
unsigned char code num[]={
	0x3f,0x06,0x5b,0x4f,//0,1,2,3
	0x66,0x6d,0x7d,0x07,//4,5,6,7
	0x7f,0x6f//8,9
};//别忘分号
//共阴极8段数码管显示A-F
unsigned char code letter[]={
	0x77,0x7c,0x39,0x5e,//A,b,C,d
	0x79,0x71//E,f
};//别忘分号

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
					dula=1;//段选打开
					P0=num[1];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xfe;//位选数据
					wela=0;//位选关闭
					delay(500);
			
					dula=1;//段选打开
					P0=num[2];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xfd;//位选数据
					wela=0;//位选关闭
					delay(500);
			
					dula=1;//段选打开
					P0=num[3];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xfb;//位选数据
					wela=0;//位选关闭
					delay(500);
					
					dula=1;//段选打开
					P0=num[4];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xf7;//位选数据
					wela=0;//位选关闭
					delay(500);
					
					dula=1;//段选打开
					P0=num[5];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xef;//位选数据
					wela=0;//位选关闭
					delay(500);
					
					dula=1;//段选打开
					P0=num[6];//送入段选数据
					dula=0;//段选关闭
					P0=0xff;//清屏！！！别忘
					wela=1;//位选打开
					P0=0xdf;//位选数据
					wela=0;//位选关闭
					delay(500);
					
		}
}
