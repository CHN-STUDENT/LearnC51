;���ǻ�����Ե�ע�ͷ���
;CT107��ˮ��ѧϰ
;WRĬ��Ϊ�͵�ƽ
ORG 0000H ;�����000H��ʼ
LJMP MAIN ;����������
ORG 0100H ;MAIN��0100H��ʼ
MAIN:
	MOV P0,#0FFH  ;P0����ȫ���ߵ�ƽ
	MOV P2,#0A0H  ;0xA0= 1       0      1     0     000    0    ����Ѱַ��ʽ
	              ;      P2.7	P2.6   P2.5	 P2.4	...   P2.0
	 			  ;��������������
	CLR P0.6	  ;�رշ����� 
	MOV P2,#000H  ;����������
	MOV A,#0FEH	  ;��A�ۼ�����ֵ0xFE=11111110 ����Ѱַ��ʽ 
	SETB C		  ;��λ�Ĵ���C��1
ZHENG: ;��ˮ����������ˮ��	
	MOV P0,#0FFH  ;P0����ȫ���ߵ�ƽ
	MOV P2,#080H  ;����ˮ��������
	MOV P0,A 	  ;A�ۼ���ֵ��P0���� ֱ��Ѱַ��ʽ
	MOV P2,#000H  ;����������
	LCALL DELAY	  ;��ʱ����
   	RLC A	   ;����λѭ������	  	
	JNC	 FAN   ;����λCΪ0 ����ת
	LJMP ZHENG ;ѭ��
FAN:  ;��ˮ�Ʒ�������ˮ��
	MOV P0,#0FFH  ;P0����ȫ���ߵ�ƽ
	MOV P2,#080H  ;����ˮ��������
	MOV P0,A 	  ;A�ۼ���ֵ��P0���� ֱ��Ѱַ��ʽ
	MOV P2,#000H  ;����������
	LCALL DELAY	  ;��ʱ����
   	RRC A	   ;����λѭ������	  
  	JNC	 ZHENG   ;����λCΪ0 ����ת
	LJMP FAN ;ѭ��
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
