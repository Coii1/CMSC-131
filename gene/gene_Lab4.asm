segment .text
    global _count_neighbors

; int count_neighbors(int *grid, int rows, int cols, int r, int c)
_count_neighbors:
    push    ebp
    mov     ebp, esp
    sub     esp, 4           ; local for sum at [ebp-4]
    mov     dword [ebp-4], 0 ; sum = 0

    mov     esi, [ebp+8]     ; grid pointer
    mov     ebx, [ebp+12]    ; rows
    mov     edx, [ebp+16]    ; cols
    mov     ecx, [ebp+20]    ; r
    mov     edi, [ebp+24]    ; c

    mov     eax, -1           ; dr = -1
    
dr_loop:
    cmp     eax, 2
    jge done
    mov     ebp, -1           ; dc = -1
dc_loop:
    cmp     ebp, 2
    jge next_dr

    ; skip center cell
    cmp     eax, 0      ; if dr == 0 check if dc == 0, if true, skip, 
    jne check_cell      ; if dr == 0 check if dc != 0 fall through sa check_cell
    cmp     ebp, 0      ; if dr != 0 go to check_cell
    je skip_cell

check_cell:
    ; nr = r + dr
    mov     ebx, ecx
    add     ebx, eax
    cmp     ebx, 0
    jl skip_cell
    cmp     ebx, [ebp+12]     ; rows
    jge skip_cell

    ; nc = c + dc
    mov     edx, edi
    add     edx, ebp
    cmp     edx, 0
    jl skip_cell
    cmp edx, [ebp+16]         ; cols
    jge skip_cell

   ; compute index = nr*cols + nc
    mov     eax, ebx           ; eax = nr
    imul    eax, [ebp+16]      ; nr*cols
    add     eax, edx           ; + nc
    shl     eax, 2             ; *4
    mov     ebx, [esi + eax]   ; load value into register
    add     [ebp-4], ebx       ; add to sum


skip_cell:
    inc     ebp
    jmp dc_loop

next_dr:
    inc     eax
    jmp dr_loop

done:
    mov     eax, [ebp-4]      ; return sum
    mov     esp, ebp
    pop     ebp
    ret
