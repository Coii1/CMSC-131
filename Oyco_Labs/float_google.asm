section .data
    float_format db "The value is: %f", 10, 0 ; Format string for printing a float
    my_float dd 3.14159                    ; Single-precision float

section .text
    global _start

_start:
    ; Load the float value into xmm0
    movss xmm0, [my_float]

    ; Prepare arguments for printf
    mov edi, float_format   ; First argument: format string
    mov eax, 1              ; Indicate one floating-point argument in xmm0

    ; Call printf
    extern printf
    call printf wrt ..plt

    ; Exit the program
    mov eax, 60             ; sys_exit system call number
    xor edi, edi            ; Exit code 0
    syscall