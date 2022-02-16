.586																	; ������� ������ (��������� Pentium)
.model flat, stdcall													; ������ ������, ���������� � �������
includelib kernel32.lib													; ������������: ����������� � kernel32
includelib "D:\3 ���\��\������\Lab_17\LP_asm01\LP_asm01\Debug\LP_asm01a.lib"

ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 
GetStdHandle PROTO: DWORD									; �������� handle ������ �� ������� 
															; (��������� ����������� �������� -10 ����, -11 �����, -12 ������)
WriteConsoleA PROTO: DWORD,: DWORD,: DWORD,: DWORD,: DWORD	

getmin PROTO: DWORD,: DWORD
getmax PROTO: DWORD,: DWORD

.stack 4096													

.const														
	handleOutput sdword -11									; ������ ���������� ������ � �������
	text byte 'getmax - getmin = ', 0						; ������ ��� ������ ������	
	array sdword 9, 3, 5, 12,2, 4, 21, 1, 2, 6

.data
	consoleHandle dword 0h									; ��������� �������
	min sdword ?
	result sdword ?
	resultStr byte 4 dup(0)

.code

int_to_char PROC uses eax ebx ecx edi esi, ; �������� �-�� ������. ����� � ������
								pstr: dword, ; ����� ������ ����������
							intfield: sdword ; ����� ��� ��������������

	mov edi, pstr					; �������� �� pstr � edi
	mov esi, 0						; ���-�� �������� � ����������
	mov eax, intfield				; ����� -> � eax
	cdq								; ���� ����� ���������������� � eax �� edx
	mov ebx, 10						; ��������� ������� ��������� (10)-> ebx
	idiv ebx						; eax/ebx (�.�. - eax, ���. - edx)
	test eax, 80000000h				; ��������� �������� ���
	jz plus							; ���� ������������� ����� �� plus
	neg eax							; ������ ����
	neg edx							; ������ ����
	mov cl, '-'						; ������ ������ ���������� '-'
	mov[edi], cl					; ������ ������ ���������� '-'
	inc edi							; ++edi
plus:								; ���� ���������� �� �������� 10

	push dx							; �������-> ����
	inc esi							; ++esi
	test eax, eax					; eax==?
	jz fin							; ���� �� �� �� fin
	cdq								; ���� ��������������� � eax �� edx
	idiv ebx						; eax=eax/ebx, ������� � edx
	jmp plus						; ����������� ������� �� plus
fin:

	mov ecx ,esi					; � ecx ���-�� �� 0-�� ��������=���-�� �������� ����������

write:								; ���� ������ ����������

	pop bx							; ������� �� �����->bx
	add bl,'0'						; ������������ ������ � bl
	mov[edi], bl					; bl->���������
	inc edi							; edi++
	loop write						; ���� (--ecx)>0 ������� �� write
	ret

int_to_char ENDP

main PROC										        
			
	invoke getmin, offset array, lengthof array
    mov min, eax										

	invoke getmax, offset array, lengthof array
	sub eax, min										 
	mov result, eax										
											        
	invoke GetStdHandle, handleOutput					; �������� � ���� ��� ����������� �� ����� � ������� � �������� �-�� �������� ���������� �� �����
	mov consoleHandle, eax						        ; �������� ���������� ���������� �� �������� eax

	invoke WriteConsoleA, consoleHandle, offset text, sizeof text, 0, 0
	invoke int_to_char, offset resultStr, result
	invoke WriteConsoleA, consoleHandle, offset resultStr, sizeof resultStr, 0, 0

	invoke ExitProcess, 0

main ENDP												
end main