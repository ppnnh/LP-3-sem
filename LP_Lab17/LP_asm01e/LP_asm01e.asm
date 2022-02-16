.586														; система команд (процессор Pentium)
.model flat, stdcall										; модель памяти, соглашение о вызовах
includelib kernel32.lib										; компановщику: компоновать с kernel32
includelib libucrt.lib
includelib "D:\3 сем\ЯП\лекции\Lab_17\LP_asm01\LP_asm01\Debug\LP_asm01d.lib"

ExitProcess PROTO: DWORD									; прототип функции для завершения процесса Windows 
GetStdHandle PROTO: DWORD									; получить handle вывода на консоль 
															; (принимает константное значение -10 ввод, -11 вывод, -12 ошибка устройства вывода)
WriteConsoleA PROTO: DWORD,: DWORD,: DWORD,: DWORD,: DWORD	; вывод на консоль (стандартная ф-ия)
SetConsoleTitleA PROTO: DWORD								; прототип ф-ии устанавливающей заголовок консольного окна (функция стандартная)

EXTRN getmax: proc
EXTRN getmin: proc

.stack 4096													; выделение стека объёмом 4 мегабайта

.const														; константы
	handleOutput sdword -11									; код на запрос разрешения вывода в консоль
	array sdword 9, 3, 5, 12,2, 4, 21, 1, 2, 6 		; массив заполненый 10-ю значениями
	text byte 'getmax - getmin = ', 0						; строка для вывода ответа	

.data
	consoleHandle dd 0h									; состояние консоли
	min sdword ?
	result sdword ?
	resultString byte 4 dup(0)

.code

int_to_char PROC uses eax ebx ecx edi esi, ; прототип ф-ии преобр. числа в строку
								pstr: dword, ; адрес строки результата
							intfield: sdword ; число для преобразования

	mov edi, pstr					; копирует из pstr в edi
	mov esi, 0						; кол-во символов в результате
	mov eax, intfield				; число -> в eax
	cdq								; знак числа распростроняется с eax на edx
	mov ebx, 10						; основание системы счисления (10)-> ebx
	idiv ebx						; eax/ebx (ц.ч. - eax, ост. - edx)
	test eax, 80000000h				; тестируем знаковый бит
	jz plus							; если положительное число на plus
	neg eax							; меняем знак
	neg edx							; меняем знак
	mov cl, '-'						; первый символ результата '-'
	mov[edi], cl					; первый символ результата '-'
	inc edi							; ++edi

plus:								; цикл разложения по степеням 10
	push dx							; остаток-> стек
	inc esi							; ++esi
	test eax, eax					; eax==?
	jz fin							; если да то на fin
	cdq								; знак распространяетс с eax на edx
	idiv ebx						; eax=eax/ebx, остаток в edx
	jmp plus						; безусловный переход на plus

fin:
	mov ecx ,esi					; в ecx кол-во не 0-ых остатков=кол-ву символов результата

write:								; цикл записи результата
	pop bx							; остаток из стека->bx
	add bl,'0'						; сформировали символ в bl
	mov[edi], bl					; bl->результат
	inc edi							; edi++
	loop write						; если (--ecx)>0 переход на write
	ret

int_to_char ENDP

main PROC										        ; точка входа main
												        
    push lengthof array                                 ;
    push offset array                                   ; помещаем массив в стек
    call getmax											; вызов процедуры getmin
    mov min, eax										; результат в min

	push lengthof array									;
    push offset array									; помещаем массив в стек
    call getmin											; вызов процедуры getmax

	sub eax, min										
	mov result, eax	
	neg result
	
	invoke GetStdHandle, handleOutput					
	mov consoleHandle, eax						        

	invoke WriteConsoleA, consoleHandle, offset text, sizeof text, 0, 0
	invoke int_to_char, offset resultString, result
	invoke WriteConsoleA, consoleHandle, offset resultString, sizeof resultString, 0, 0
	invoke ExitProcess, 0

main ENDP												
end main