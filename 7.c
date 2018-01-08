#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar num;

//使用锁存器的引脚，用来存储8位数码管
sbit dula=P2^6;//段选
sbit wela=P2^7;//位选
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

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

uchar keyscan()
{//扫描用户输入
		//检测第一行键盘
		uchar temp;
		P3=0xfe;//1111 1110
		temp=P3;//取值
		temp=temp&0xf0;//逻辑与 P3与1111 0000
		while(temp!=0xf0)
		{//如果被按下
				delay(5);//延时5ms
				temp=P3;//取值
				temp=temp&0xf0;//逻辑与 P3与1111 0000
				while(temp!=0xf0)
				{//持续被按下
						temp=P3;//取值
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
							temp=P3;//取值
							temp=temp&0xf0;//逻辑与 P3与1111 0000
						}
				}
		}
		//检测第二行键盘
		P3=0xfd;//1111 1101
		temp=P3;//取值
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P3;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P3;
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
							temp=P3;
							temp=temp&0xf0;
						}
				}
		}
		//检测第三行键盘
		P3=0xfb;//1111 1011
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P3;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P3;
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
							temp=P3;
							temp=temp&0xf0;
						}
				}
		}
		//检测第四行键盘
		P3=0xf7;//1111 0111
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
				delay(5);
				temp=P3;
				temp=temp&0xf0;
				while(temp!=0xf0)
				{
						temp=P3;
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
							temp=P3;
							temp=temp&0xf0;
						}
				}
		}
		return num;
}	

void display(uchar n)
{//8段管输出
		//分离百十个位
		uchar shiwei=n%100/10;
		uchar gewei=n%10;
	
		dula=1;//段选打开
		P0=table[shiwei];//送入十位
		dula=0;//段选关闭
		P0=0xff;//清屏！！！别忘
		wela=1;//位选打开
		P0=0xef;
		wela=0;//位选关闭
		delay(1);//5ms延时利用余晖效应人眼就看不出来
		
		dula=1;//段选打开
		P0=table[gewei];//送入个位
		dula=0;//段选关闭
		P0=0xff;//清屏！！！别忘
		wela=1;//位选打开
		P0=0xdf;
		wela=0;//位选关闭
		delay(1);//5ms延时利用余晖效应人眼就看不出来
}

void main()
{
		num=0;
		wela=0;
		dula=0;
		while(1)
		{
				num=keyscan();
				display(num);//完成时间计数后调用显示函数
				//显示函数一定要时间计数后，不然会出问题！！
		}
}
