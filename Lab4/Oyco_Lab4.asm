%include "asm_io.inc"

segment .text
    global _count_neighbors
    global _copy_grid

; int count_neighbors(int *grid, int SIZE, int r, int c)
_count_neighbors:
    enter 4, 0                  ; reserve 4 bytes for sum -> [ebp-4] = sum
    push    ebx
    push    esi
    push    edi
    mov dword [ebp-4], 0        ; sum = 0
    mov esi, [ebp+8]            ; grid pointer
    ; mov edx, [ebp+16]    ; r
    ; mov ecx, [ebp+20]    ; c
    mov ebx, [ebp+12]    ; SIZE in ebx

    mov eax, -1           ; dr = -1 diri and start sng outer loop from -1 to 1 nga offset
row_loop:
    cmp eax, 1
    jg done

    mov edi, -1           ; dc = -1 for column loop
column_loop:
    cmp edi, 1
    jg next_row

    cmp eax, 0              ; if (dr == 0 
    jne do_check            ; check out of bounds
    cmp edi, 0              ; && dc == 0) continue;
    je skip_cell_inc

do_check:
    ; compute nr = r + dr into edx
    mov edx, [ebp+16]
    add edx, eax                   
    cmp edx, 0                      ; if (nr < 0 
    jl skip_cell_inc                ; || 
    cmp edx, ebx                    ; nr >= size) 
    jge skip_cell_inc               ; continue;

    ; compute nc = c + dc into ecx
    mov ecx, [ebp+20]               
    add ecx, edi                    
    cmp ecx, 0                      ; if (nc < 0 
    jl skip_cell_inc                ; ||   
    cmp ecx, ebx                    ; nc >= size) 
    jge skip_cell_inc               ; continue;

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

_copy_grid:
    ; void copy_grid(int *dest, int *src, int size)
    ; [esp+4] = dest                  
    ; [esp+8] = src
    ; [esp+12] = size
    enter 0,0

    ; arguments: [ebp+8]=dest, [ebp+12]=src, [ebp+16]=size
    mov     eax, [ebp+8]   ; dest -> eax
    mov     edx, [ebp+12]  ; src  -> edx
    mov     ecx, [ebp+16]  ; size -> ecx

    push    ebx
    push    esi
    push    edi

    mov     edi, eax       ; EDI = dest
    mov     esi, edx       ; ESI = src
    imul    ecx, ecx       ; ecx = size * size (number of dwords)
    cld
    rep movsd
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret


