.586														; ������� ������ (��������� Pentium)
.model flat, stdcall										; ������ ������, ���������� � �������
includelib kernel32.lib										; ������������: ����������� � kernel32

ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 

.stack 4096													; ��������� ����� ������� 4 ���������	

.data
	array sdword 9, 3, 5, 12,2, 4, 21, 1, 2, 6
	min dword ?
	
.code

getmin proc arr : sdword, count : dword
	mov ESI, arr		
	mov EAX, [ESI];

	sub count, 1
	mov ECX, count

	cycle:
		add ESI, 4
		cmp [ESI], EAX
		jae marker				
		mov EAX, [ESI]
		marker:
	loop cycle

	ret														; ������� ��������� � �������� eax
getmin endp													

main proc													
    push lengthof array										
    push offset array										
    call getmin												
    mov min, eax											

	push 0													
	call ExitProcess										
main endp													
end main	