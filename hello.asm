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
PRINT_HELLO:
	MOV P2,#0E0H  ;����ѡ������
	MOV P0,#089H  ;���H
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	MOV P2,#0C0H  ;��λѡ������
	MOV P0,#004H  ;�ڵ�����8�ι���ʾ
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	LCALL DELAY2MS ;��ʱ
	MOV P2,#0E0H  ;����ѡ������
	MOV P0,#086H  ;���E
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	MOV P2,#0C0H  ;��λѡ������
	MOV P0,#008H  ;�ڵ��ĸ�8�ι���ʾ
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	LCALL DELAY2MS ;��ʱ
	MOV P2,#0E0H  ;����ѡ������
	MOV P0,#0C7H  ;���L
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	MOV P2,#0C0H  ;��λѡ������
	MOV P0,#010H  ;�ڵ����8�ι���ʾ
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	LCALL DELAY2MS ;��ʱ
	MOV P2,#0E0H  ;����ѡ������
	MOV P0,#0C7H  ;���L
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	MOV P2,#0C0H  ;��λѡ������
	MOV P0,#020H  ;�ڵ�����8�ι���ʾ
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	LCALL DELAY2MS ;��ʱ
	MOV P2,#0E0H  ;����ѡ������
	MOV P0,#0C0H  ;���O
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����
	MOV P2,#0C0H  ;��λѡ������
	MOV P0,#040H  ;�ڵ��߸�8�ι���ʾ
	MOV P2,#000H  ;����������
	MOV P0,#0FFH  ;����	
	LCALL DELAY2MS ;��ʱ
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