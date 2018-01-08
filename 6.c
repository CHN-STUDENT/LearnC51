#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
//使用锁存器的引脚，用来存储8位数码管
sbit dula=P2^6;//段选
sbit wela=P2^7;//位选
//使用键盘的引脚
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;

//共阴极8段数码管显示0-9
unsigned char code table[]={
	0x3f,0x06,0x5b,0x4f,//0,1,2,3
	0x66,0x6d,0x7d,0x07,//4,5,6,7
	0x7f,0x6f//8,9
};//别忘了分号
	
/****!!!注意!!!******
*  每次别忘了清屏动作 
*	    P0=0xff; 
********************/

uchar num; //50ms的个数声明 20个为1s
uchar n;	//显示数字声明
uchar baiwei,shiwei,gewei;

void delay(uint xms)
{//延时函数
		uint x,y;
	for(x=xms;x>0;x--)
		for(y=110;y>0;y--);
}
	
void keyscan()
{
		if(key1==0)
		{//key1低电平被按下
				delay(10);//10ms延迟
				if(key1==0)
				{//持续被按下
						n++;
						if(n==100)//0-100动态显示
							n=0;//超过一100置0
						while(!key1); //等待被释放
				}
		}
		if(key2==0)
		{//key2低电平被按下
				delay(10);//10ms延迟
				if(key2==0)
				{//持续被按下
						n--;
						if(n==0)//0-100动态显示
							n=100;//超过一100置0
						while(!key2); //等待被释放
				}
		}
		if(key3==0)
		{//key3低电平被按下
				delay(10);//10ms延迟
				if(key3==0)
				{//持续被按下
						n=0;
						while(!key3); //等待被释放
				}
		}
		if(key4==0)
		{//key4低电平被按下
				delay(10);//10ms延迟
				if(key4==0)
				{//持续被按下
						while(!key4); //等待被释放
						TR0=!TR0;//启动或者关闭定时器
				}
		}
}

void display(uchar n)
{
		//分离百十个位
		uchar baiwei=n/100;
		uchar shiwei=n%100/10;
		uchar gewei=n%10;
	
		dula=1;//段选打开
		P0=table[baiwei];//送入百位
		dula=0;//段选关闭
		P0=0xff;//清屏！！！别忘
		wela=1;//位选打开
		P0=0xfe;//第一位8段管打开
		wela=0;//位选关闭
		delay(1);//5ms延时利用余晖效应人眼就看不出来
	
		dula=1;//段选打开
		P0=table[shiwei];//送入十位
		dula=0;//段选关闭
		P0=0xff;//清屏！！！别忘
		wela=1;//位选打开
		P0=0xfd;//第二位8段管打开
		wela=0;//位选关闭
		delay(1);//5ms延时利用余晖效应人眼就看不出来
		
		dula=1;//段选打开
		P0=table[gewei];//送入个位
		dula=0;//段选关闭
		P0=0xff;//清屏！！！别忘
		wela=1;//位选打开
		P0=0xfb;//第三位8段管打开
		wela=0;//位选关闭
		delay(1);//5ms延时利用余晖效应人眼就看不出来
}
	
void T0_time() interrupt 1
{//中断函数每50ms中断一次
		TH0=(65536-45872)/256;
		TL0=(65536-45872)%256;
		num++;//中断次数计算
		if(num==20)
		{//时间计数,50ms*20=1s
				num=0;//时间计算重置
				n++;
				if(n==100)//0-100动态显示
					n=0;//超过一100置0
		}
		
}	
	
void main()
{	
	wela=0;
	dula=0;
	n=0;
	num=0;
		/*中断定时器初始化*/
		TMOD=0x01;//16位工作模式？
		TH0=(65536-45872)/256;
		TL0=(65536-45872)%256;
		EA=1;	//总中断打开
		ET0=1;	//开定时器0中断
		while(1)
		{
			keyscan();
			display(n);//完成时间计数后调用显示函数
			//显示函数一定要时间计数后，不然会出问题！！
		}
}
