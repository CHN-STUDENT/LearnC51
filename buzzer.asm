;���ǻ�����Ե�ע�ͷ���
;CT107���ط�����ѧϰ
;WRĬ��Ϊ�͵�ƽ
ORG 0000H ;�����000H��ʼ
LJMP MAIN ;����������
ORG 0100H ;MAIN��0100H��ʼ
MAIN:
	MOV P0,#0A0H 
START:
	;��������
	MOV P2,#0A0H  ;0xA0= 1       0      1     0     000    0    ����Ѱַ
	              ;      P2.7	P2.6   P2.5	 P2.4	...   P2.0  
	SETB P0.6	 
	MOV P2,#000H
	LCALL DELAY
	;����������
	MOV P2,#0A0H  ;0xA0=10100000 ����Ѱַ
	CLR P0.6	 
	MOV P2,#000H
	LCALL DELAY
	;ѭ��
	LJMP START ;��������ת��
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
