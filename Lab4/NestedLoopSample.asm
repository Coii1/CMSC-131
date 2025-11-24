section .data
N dd 3
M dd 4

section .text
global _start

_start:
    mov eax, [N]      ; eax = N rows
    mov ebx, [M]      ; ebx = M cols

    xor ecx, ecx      ; ecx = i = 0

outer_loop:
    cmp ecx, eax      ; if (i >= N)
    jge end_outer     ; break

    xor edx, edx      ; edx = j = 0

inner_loop:
    cmp edx, ebx      ; if (j >= M)
    jge end_inner     ; break inner loop

    ; ----------------------------
    ; inner loop body here
    ; example: do something with ecx (i) and edx (j)
    ; ----------------------------

    inc edx           ; j++
    jmp inner_loop

end_inner:
    inc ecx           ; i++
    jmp outer_loop

end_outer:
    ; exit(0)
    mov eax, 1
    xor ebx, ebx
    int 0x80
