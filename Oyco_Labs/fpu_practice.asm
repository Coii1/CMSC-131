; float_example.asm
; NASM 32-bit Windows example using IEEE 754 floats
%include "asm_io.inc"

section .data
    num     dd 3.75         ; 32-bit float: 3.75
    add_val dd 2.5          ; 32-bit float: 2.5
    fmt     db "Result: %f", 10, 0   ; printf format string with newline

section .bss
    result  resd 1          ; reserve 4 bytes for float result

section .text
    global _asm_main


_asm_main:
    ; --- optional stack frame ---
    enter 0,0
    pusha

    ; --- FPU computation ---
    fld dword [num]         ; st(0) = 3.75 ; Load num into FPU stack
    fadd dword [add_val]    ; st(0) = 6.25 ; Load add_val and add
    fstp dword [result]     ; store result  ; Store result back to memory

    ; --- call printf ---
    fld dword [result]      ; push result to FPU stack again
    sub esp, 8              ; allocate stack for float argument (align to 8 bytes)
    fstp qword [esp]        ; store as 64-bit double on stack (printf expects double)
    push fmt                ; push format string
    call print_int
    add esp, 12             ; clean up stack (8 + 4)

    ; --- restore registers ---
    popa
    mov eax, 0              ; return value to C
    leave
    ret
