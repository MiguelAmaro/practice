COMMENT ;
rip - relative instruction pointer
relative addressing for jumping 
;

.code

conditional_jump proc

call example_01
call example_02
call example_03
call example_04

ret
conditional_jump endp


; ****************************************
; LABLES & JUMPS
; ****************************************
example_01 proc
mov eax,  -9
add eax, -12

; jump based on wether the overflow flag was set
jo overflowed
jno didntoverflow

; labels spec a place in the code u can jump to  
overflowed:

mov rax, 12


didntoverflow:

mov rax, 15

ret
example_01 endp



; ****************************************
; CONDITIONAL INSTRUCTIONS BASED ON FLAG STATUS
; ****************************************
example_02 proc

push rbx

mov ebx,  67
mov eax,  -1
add eax,   1
; instruction to clear the carry flag
clc

; conditional move only moves stuff into the reg if carry flag is set
cmovc eax, ebx

pop rbx

ret
example_02 endp


; ****************************************
; LOOPS
; ****************************************
example_03 proc

push rbx

mov rax, 10 ; counter

loop_head:
; body of loop
dec rax ;decrement the counter
jnz loop_head ; jump if zero flag is not set

pop rbx

ret
example_03 endp



; ****************************************
; COMPARE
; ****************************************
example_04 proc

push rbx

mov eax,  5
mov ecx,  5

; cmp actually subs the 2 operands and 
; sets the zero flag if the 2 ops are equal.
cmp eax, ecx

; sete checks the zero flag
sete bh

pop rbx

ret
example_04 endp

; ****************************************

; END OF CODE SECTION
end
