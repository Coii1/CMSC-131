%include "asm_io.inc"

segment .text
    global _count_neighbors
    global _copy_grid

; int count_neighbors(int *grid, int SIZE, int r, int c)
_count_neighbors:
    enter 4, 0                  ; reserve 4 bytes for sum -> [ebp-4] = sum
    mov dword [ebp-4], 0        ; sum = 0
    ; mov dword [ebp-8], 0            ; nr
    ; mov dword [ebp-12], 0           ; nc
    ;[ebp] = old EBP
    ;[ebp+4] = return address
    mov esi, [ebp+8]     ; grid pointer
    mov edi, [ebp+12]    ; SIZE
    mov edx, [ebp+16]    ; r
    mov ecx, [ebp+20]    ; c

    mov eax, -1           ; dr = -1 diri and start sng outer loop from -1 to 1 nga offset
row_loop:
    cmp eax, 1
    jg done

    mov ebx, -1           ; dc = -1
column_loop:
    cmp ebx, 1
    jg next_row

    ; skip center cell
    cmp eax, 0                  ; if dr == 0 check if dc == 0, if true, skip, 
    jne check_cell              ; if dr == 0 check if dc != 0 fall through sa check_cell
    cmp ebx, 0                  ; if dr != 0 go to check_cell
    je skip_cell

check_cell:
    ; nr = r + dr ; edx = r + dr   
    add edx, eax                    ; problem di is gina modify ang edx nga ga hold sng r
    cmp edx, 0
    jl  skip_cell_restore_r               ; if nr < 0, neighbor is off-grid → skip
    cmp edx, edi                            ; compare nr >= SIZE
    jge skip_cell_restore_r               ; jge kay out of bounds na if index SIZE

    ; nc = c + dc = ecx
    add ecx, ebx
    cmp ecx, 0
    jl skip_cell_restore_c               ; if nc < 0, neighbor is off-grid → skip
    cmp ecx, edi                      ; compare nc >= SIZE
    jge skip_cell_restore_c               ; jge kay out of bounds na if index SIZE

    ; compute index = nr*SIZE + nc  
    ;add edx, eax           ; edx = nr
    ;add ecx, ebx           ; ecx = nc

    ;nr * size
    imul edx, edi         ; nr*SIZE
    add edx, ecx          ; + nc
    shl edx, 2            ; *4
    mov edi, [esi + edx]  ; load value of grid[nr][nc] into register
    add [ebp-4], edi      ; add to sum

restore_b:
    mov edi, [ebp+12]    ; SIZE (reload SIZE)

skip_cell_restore_r:
    mov edx, [ebp+16]    ; r (reload r)

skip_cell_restore_c:
    mov ecx, [ebp+20]    ; c (reload c)

skip_cell:
    inc     ebx
    jmp column_loop

next_row:
    inc     eax
    jmp row_loop

done:
    mov     eax, [ebp-4]      ; return sum
    leave
    ret


_copy_grid:
    ; void copy_grid(int *dest, int *src, int size)
    ; [esp+4] = dest                  
    ; [esp+8] = src
    ; [esp+12] = size
    ; need ipreserve and esi, edi kay if inidi sila mabalik. ga runtime error
    ;enter 0, 0                 ; no local variables
    push    esi
    push    edi
    mov edi, [esp+12]  ; dest
    mov esi, [esp+16]  ; src
    mov ecx, [esp+20]  ; size
    imul    ecx, ecx
    cld
    rep movsd
    pop     edi
    pop     esi
    ;leave
    ret
    ;no need for stack frame since no local variables
    


