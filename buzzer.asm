;这是汇编语言的注释方法
;CT107开关蜂鸣器学习
;WR默认为低电平
ORG 0000H ;程序从000H开始
LJMP MAIN ;跳到主函数
ORG 0100H ;MAIN在0100H开始
MAIN:
	MOV P0,#0A0H 
START:
	;蜂鸣器响
	MOV P2,#0A0H  ;0xA0= 1       0      1     0     000    0    立即寻址
	              ;      P2.7	P2.6   P2.5	 P2.4	...   P2.0  
	SETB P0.6	 
	MOV P2,#000H
	LCALL DELAY
	;蜂鸣器不响
	MOV P2,#0A0H  ;0xA0=10100000 立即寻址
	CLR P0.6	 
	MOV P2,#000H
	LCALL DELAY
	;循环
	LJMP START ;无条件长转移
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
