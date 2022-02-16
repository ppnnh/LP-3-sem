.586														; ������� ������ (��������� Pentium)
.model flat, stdcall										; ������ ������, ���������� � �������
includelib kernel32.lib										; ������������: ����������� � kernel32

ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 

.stack 4096													; ��������� ����� ������� 4 ���������	

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

getmax proc arr : sdword, count : dword
	mov ESI, arr		
	mov EAX, [ESI];

	sub count, 1
	mov ECX, count

	cycle:
		add ESI, 4
		cmp [ESI], EAX
		jle marker				
		mov EAX, [ESI]
		marker:
	loop cycle

	ret														; ������� ��������� � �������� eax
getmax endp

end