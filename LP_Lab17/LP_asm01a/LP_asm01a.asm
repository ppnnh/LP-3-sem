.586														; система команд (процессор Pentium)
.model flat, stdcall										; модель памяти, соглашение о вызовах
includelib kernel32.lib										; компановщику: компоновать с kernel32

ExitProcess PROTO: DWORD									; прототип функции для завершения процесса Windows 

.stack 4096													; выделение стека объёмом 4 мегабайта	

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

	ret														; возврат результат в регистре eax
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

	ret														; возврат результат в регистре eax
getmax endp

end