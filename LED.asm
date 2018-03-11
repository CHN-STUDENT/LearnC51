;这是汇编语言的注释方法
;CT107流水灯学习
;WR默认为低电平
ORG 0000H ;程序从000H开始
LJMP MAIN ;跳到主函数
ORG 0100H ;MAIN在0100H开始
MAIN:
	MOV P0,#0FFH  ;P0总线全部高电平
	MOV P2,#0A0H  ;0xA0= 1       0      1     0     000    0    立即寻址方式
	              ;      P2.7	P2.6   P2.5	 P2.4	...   P2.0
	 			  ;开蜂鸣器锁存器
	CLR P0.6	  ;关闭蜂鸣器 
	MOV P2,#000H  ;锁存器启动
	MOV A,#0FEH	  ;给A累加器赋值0xFE=11111110 立即寻址方式 
	SETB C		  ;进位寄存器C设1
ZHENG: ;流水灯正方向流水亮	
	MOV P0,#0FFH  ;P0总线全部高电平
	MOV P2,#080H  ;开流水灯锁存器
	MOV P0,A 	  ;A累加器值给P0总线 直接寻址方式
	MOV P2,#000H  ;锁存器启动
	LCALL DELAY	  ;延时函数
   	RLC A	   ;带进位循环左移	  	
	JNC	 FAN   ;若进位C为0 则跳转
	LJMP ZHENG ;循环
FAN:  ;流水灯反方向流水亮
	MOV P0,#0FFH  ;P0总线全部高电平
	MOV P2,#080H  ;开流水灯锁存器
	MOV P0,A 	  ;A累加器值给P0总线 直接寻址方式
	MOV P2,#000H  ;锁存器启动
	LCALL DELAY	  ;延时函数
   	RRC A	   ;带进位循环右移	  
  	JNC	 ZHENG   ;若进位C为0 则跳转
	LJMP FAN ;循环
DELAY:			;@11.0592MHz
	NOP
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	PUSH 32H
	MOV 30H,#17
	MOV 31H,#208
	MOV 32H,#24
NEXT:
	DJNZ 32H,NEXT
	DJNZ 31H,NEXT
	DJNZ 30H,NEXT
	POP 32H
	POP 31H
	POP 30H
	RET
END
