%include "asm_io.inc"

segment .data

segment .bss

segment .text

    global _add_two_numbers
    global _subtract_two_numbers
    global _sum_array
    global _sum_grid

; int add_two_numbers(int a, int b)
_add_two_numbers:
    enter 0,0 ;enter <locals>, <nesting level>
    ; push ebp
    ; mov  ebp, esp
    ;sub  esp, N  ; allocate local variables


    ;Before pusha (after enter 0,0 and call):
    ; [esp+0]  = return address
    ; [esp+4]  = first arg (a = 7)
    ; [esp+8]  = second arg (b = 35)
    ;pusha
    ; After pusha (pushes EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX):
    ; [esp+0]   = saved EAX
    ; [esp+4]   = saved ECX
    ; [esp+8]   = saved EDX
    ; [esp+12]  = saved EBX
    ; [esp+16]  = saved ESP (original)
    ; [esp+20]  = saved EBP
    ; [esp+24]  = saved ESI
    ; [esp+28]  = saved EDI
    ; [esp+32]  = return address
    ; [esp+36]  = first arg (a = 7)
    ; [esp+40]  = second arg (b = 35)


    
    ; [ebp+0]   = saved EBP (pushed by enter)
    ; [ebp+4]   = return address
    ; read parameters using EBP (standard cdecl)
    ; [ebp+8]  = first arg (a)
    ; [ebp+12] = second arg (b)
    mov eax, [ebp + 8]      ; a
    mov ebx, [ebp + 12]     ; b
    add eax, ebx           ; eax = a + b

    ;popa
    leave
    ret                    ; return eax to C because C receives the value in EAX.
                                            ;  ^ 
;How does the function return the value to C?  |
;what if I have 2 functions, do i need to do enter and leave for every function? wouldn't it be redundant and make the execution slower?

_subtract_two_numbers:
    enter 0,0
    ;pusha

    ; read parameters using EBP (standard cdecl)
    ; [ebp+8]  = first arg (a)
    ; [ebp+12] = second arg (b)
    mov eax, [ebp + 8]      ; a
    mov ebx, [ebp + 12]     ; b
    sub eax, ebx           ; eax = a - b

    ;popa
    leave
    ret                    ; return eax to C because C receives the value in EAX.

;     The problem was pusha/popa. When you use pusha, it modifies EAX before you save it, and popa restores your original EAX value, overwriting the result you calculated (which was in EAX). After popa, EAX reverts to whatever it was before the function started.

; Key takeaway: Don't use pusha/popa if you need to return a value in EAX. Use enter/leave and access arguments via [ebp+8], [ebp+12], etc. If you must preserve registers, save/restore only the ones you modify (e.g., push ebx; ... pop ebx).

        
_sum_array:
    enter 0,0

    mov esi, [ebp + 8]      ; arr pointer
    mov ecx, [ebp + 12]     ; len
    xor eax, eax            ; sum = 0

loop:
    test ecx, ecx
    jz done

    add eax, [esi]          ; sum += arr[i]
    add esi, 4              ; advance pointer
    dec ecx
    jmp loop

done:
    leave
    ret




; int sum_grid(int *grid, int rows, int cols)
_sum_grid:
    enter 4, 0              ; reserve 4 bytes → [ebp-4] = sum
    mov dword [ebp-4], 0    ; sum = 0

    mov esi, [ebp + 8]      ; pointer to grid
    mov ecx, [ebp + 12]     ; rows
    mov edx, [ebp + 16]     ; cols

    xor ebx, ebx            ; row index = 0

row_loop:
    cmp ebx, ecx
    jge grid_done                ; if row >= rows → exit loop

    xor edi, edi            ; col index = 0

col_loop:
    cmp edi, edx
    jge next_row            ; if col >= cols → next row

    ; offset = (row * cols + col) * 4
    mov eax, ebx
    imul eax, edx           ; eax = row * cols
    add eax, edi            ; eax = row * cols + col
    shl eax, 2              ; int = 4 bytes
    mov eax, [esi + eax]    ; eax = grid[row][col]

    add [ebp - 4], eax      ; sum += value

    inc edi
    jmp col_loop

next_row:
    inc ebx
    jmp row_loop

grid_done:
    mov eax, [ebp - 4]      ; return sum
    leave
    ret
