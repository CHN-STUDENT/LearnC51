#include<reg52.h>
typedef unsigned char uchar;//数据类型宏定义
sbit BF = P0^7;	//状态检测端引脚 1不能操作 0可以操作
sbit EN = P2^5;	//使能端引脚 1可以操作 0不能操作
sbit RS = P1^0;	//数据/命令选择端引脚 1(高电平)数据 2(低电平)命令
sbit RW = P1^1;	//读/写选择段引脚 1(高电平)读 2(低电平)写
void wait(void)
{
	 P0=0xFF;//1111 1111
	 do
	 {
		 RS=0;//命令模式
		 RW=1;//读取模式
		 EN=0;//使能打开
		 EN=1;//使能关闭
	 }while (BF==1);//状态检测端引脚不可操作
	 EN=0;//使能端引脚关闭
}

//写数据函数
void w_dat(uchar dat)
{
	wait();
	EN=0;
	P0=dat;//传入数据
	RS=1;//数据模式
	RW=0;//写入模式
	EN=1;//使能打开
	EN=0;//使能关闭
}

void w_cmd(uchar cmd)
{
	wait();
	EN=0;
	P0=cmd;//传入命令
	RS=0;//命令模式
	RW=0;//写入模式
	EN=1;//使能打开
	EN=0;//使能关闭
}

void Init_LCD1602(void)
{
	w_cmd(0x38); //0011 1000 设置16*2 5*7点阵 8位数据接口
	w_cmd(0x0c); //0000 1100 开启显示 不显示光标 光标闪烁同样不显示
	w_cmd(0x06); //0000 0110 读写一个字符之后指针加1光标加1 
	w_cmd(0x01); //0000 0001 全部清除显示
}
void main()
{
	Init_LCD1602();//调用LCD函数
	w_cmd(0x80); //1000 0000 设置1602首地址0x80
	w_dat('A'); //显示一个字符 A   'A'
	while(1);
}
