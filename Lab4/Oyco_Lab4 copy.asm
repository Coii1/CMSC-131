%include "asm_io.inc"

segment .text
    global _count_neighbors

; int count_neighbors(int *grid, int SIZE, int r, int c)
_count_neighbors:
    enter 4, 0                  ; reserve 4 bytes for sum -> [ebp-4] = sum
    push    ebx
    push    esi
    push    edi
    mov dword [ebp-4], 0        ; sum = 0

    mov esi, [ebp+8]     ; grid pointer
    mov ebx, [ebp+12]    ; SIZE in ebx

    mov eax, -1           ; dr = -1
row_loop:
    cmp eax, 1
    jg done

    mov edi, -1           ; dc = -1 (use edi as dc)
column_loop:
    cmp edi, 1
    jg next_row

    ; skip center cell when dr == 0 and dc == 0
    cmp eax, 0
    jne do_check
    cmp edi, 0
    je skip_cell_inc

do_check:
    ; compute nr = r + dr into edx
    mov edx, [ebp+16]
    add edx, eax         ; edx = nr
    cmp edx, 0
    jl skip_cell_inc
    cmp edx, ebx
    jge skip_cell_inc

    ; compute nc = c + dc into ecx
    mov ecx, [ebp+20]
    add ecx, edi         ; ecx = nc
    cmp ecx, 0
    jl skip_cell_inc
    cmp ecx, ebx
    jge skip_cell_inc

    ; compute index = (nr * SIZE + nc) * 4 (byte offset)
    imul edx, ebx        ; edx = nr * SIZE
    add edx, ecx         ; edx += nc
    shl edx, 2           ; multiply by 4 (sizeof int)
    mov ecx, [esi + edx] ; load grid[nr][nc] into ecx
    add [ebp-4], ecx     ; sum += value

skip_cell_inc:
    inc edi
    jmp column_loop

next_row:
    inc eax
    jmp row_loop

done:
    mov eax, [ebp-4]      ; return sum
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret