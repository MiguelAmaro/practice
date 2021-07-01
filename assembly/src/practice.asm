extrn printf : proc

; INCLUDES
include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 

; LIBRARIES
includelib \masm32\lib\kernel32.lib  

.data
move_speed real4 90.50
my_f32     dword 0
helloworld byte  "hello world", 0ah, 0h

.code

mainCRTStartup proc
call main

ret

mainCRTStartup endp 

main proc

mov rax, 15
mov ecx, move_speed
add eax, ecx
mov my_f32, eax
lea rax, my_f32
mov dword ptr [rax], ecx

; call conditional_jump

start:
invoke GetStdHandle, STD_OUTPUT_HANDLE
invoke WriteConsole, eax, addr helloworld, sizeof helloworld, ebx, NULL
invoke ExitProcess, 0

ret
main endp

INCLUDE creel_10_conditional_jumps_mov.asm

end
