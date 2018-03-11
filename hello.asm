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
PRINT_HELLO:
	MOV P2,#0E0H  ;开段选锁存器
	MOV P0,#089H  ;输出H
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	MOV P2,#0C0H  ;开位选锁存器
	MOV P0,#004H  ;在第三个8段管显示
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	LCALL DELAY2MS ;延时
	MOV P2,#0E0H  ;开段选锁存器
	MOV P0,#086H  ;输出E
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	MOV P2,#0C0H  ;开位选锁存器
	MOV P0,#008H  ;在第四个8段管显示
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	LCALL DELAY2MS ;延时
	MOV P2,#0E0H  ;开段选锁存器
	MOV P0,#0C7H  ;输出L
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	MOV P2,#0C0H  ;开位选锁存器
	MOV P0,#010H  ;在第五个8段管显示
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	LCALL DELAY2MS ;延时
	MOV P2,#0E0H  ;开段选锁存器
	MOV P0,#0C7H  ;输出L
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	MOV P2,#0C0H  ;开位选锁存器
	MOV P0,#020H  ;在第六个8段管显示
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	LCALL DELAY2MS ;延时
	MOV P2,#0E0H  ;开段选锁存器
	MOV P0,#0C0H  ;输出O
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐
	MOV P2,#0C0H  ;开位选锁存器
	MOV P0,#040H  ;在第七个8段管显示
	MOV P2,#000H  ;锁存器启动
	MOV P0,#0FFH  ;消隐	
	LCALL DELAY2MS ;延时
	LJMP PRINT_HELLO
DELAY2MS:			;@11.0592MHz
	NOP
	NOP
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	MOV 30H,#18
	MOV 31H,#48
NEXT:
	DJNZ 31H,NEXT
	DJNZ 30H,NEXT
	POP 31H
	POP 30H
	RET

 END