.586														; система команд (процессор Pentium)
.model flat, stdcall										; модель памяти, соглашение о вызовах
includelib kernel32.lib										; компановщику: компоновать с kernel32

ExitProcess PROTO: DWORD									; прототип функции для завершения процесса Windows 

.stack 4096													; выделение стека объёмом 4 мегабайта	

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

	ret														; возврат результат в регистре eax
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