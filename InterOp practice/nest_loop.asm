section .data
N dd 3       ; outer loop limit
M dd 4       ; inner loop limit

section .bss
i resd 1
j resd 1

section .text
global _start

_start:
    mov dword [i], 0          ; i = 0

outer_loop:
    mov eax, [i]              ; eax = i
    cmp eax, [N]              ; compare i with N
    jge done_outer             ; if i >= N, exit outer loop

    mov dword [j], 0          ; j = 0 at start of inner loop

inner_loop:
    mov ebx, [j]              ; ebx = j
    cmp ebx, [M]              ; compare j with M
    jge done_inner            ; if j >= M, exit inner loop

    ; --------------------------
    ; body of inner loop goes here
    ; for example, print i and j or do some calculation
    ; --------------------------

    add dword [j], 1          ; j++
    jmp inner_loop            ; repeat inner loop

done_inner:
    add dword [i], 1          ; i++
    jmp outer_loop            ; repeat outer loop

done_outer:
    ; exit program (Linux syscall)
    mov eax, 1
    mov ebx, 0
    int 0x80
