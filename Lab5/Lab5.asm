%include "asm_io.inc"

segment .text
    global _map_chars
    global _get_unique_count
    global _get_total_chars
    global _get_modal_chars

; void map_chars(char input[], modal_character map[])
_map_chars:
    enter 0, 0
    push    ebx
    push    esi
    push    edi

    mov     esi, [ebp+8]       ; esi = input pointer
    xor     edi, edi           ; edi = i = 0

.loop_start:
    movzx   eax, byte [esi+edi] ; al = input[i], zero-extended
    test    al, al              ; check if input[i] == '\0'
    je      .loop_end

    ; Skip spaces
    cmp     al, ' '             ; check if character is space
    je      .increment_i        ; skip if space

    sub     al, 33              ; hash_index = current_char - 33
    movzx   ecx, al             ; ecx = hash_index (zero-extend for safety)

    ; if (hash_index < 0 || hash_index >= 94) continue
    cmp     ecx, 94             ; unsigned compare handles both < 0 and >= 94
    jae     .increment_i        ; jump if above or equal (unsigned)

    ; calculate &map[hash_index]
    mov     ebx, [ebp+12]       ; ebx = map pointer
    lea     ebx, [ebx + ecx*8]  ; ebx = &map[hash_index] (each struct = 8 bytes)

    ; check if map[hash_index].times == 0
    cmp     dword [ebx+4], 0    ; times field
    jne     .skip_char_store

    ; map[hash_index].character = input[i]
    mov     al, [esi+edi]       ; reload original character
    mov     [ebx], al

.skip_char_store:
    ; map[hash_index].times++
    inc     dword [ebx+4]

.increment_i:
    inc     edi                 ; i++
    jmp     .loop_start

.loop_end:
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret


; int get_unique_count(modal_character map[])
_get_unique_count:
    enter 0, 0
    push    ebx
    push    esi

    mov     esi, [ebp+8]        ; esi = map pointer
    xor     eax, eax            ; eax = unique count = 0
    xor     ecx, ecx            ; ecx = i = 0

.loop_start:
    cmp     ecx, 94
    jge     .loop_end

    ; Calculate pointer to map[i]
    lea     ebx, [esi + ecx*8]  ; ebx = &map[i]

    ; if (map[i].times > 0) unique++
    cmp     dword [ebx+4], 0    ; check times field
    jle     .next_char
    inc     eax                 ; unique++

.next_char:
    inc     ecx
    jmp     .loop_start

.loop_end:
    pop     esi
    pop     ebx
    leave
    ret


; int get_total_chars(modal_character map[])
_get_total_chars:
    enter 0, 0
    push    ebx
    push    esi

    mov     esi, [ebp+8]        ; esi = map pointer
    xor     eax, eax            ; eax = total = 0
    xor     ecx, ecx            ; ecx = i = 0

.loop_start:
    cmp     ecx, 94
    jge     .loop_end

    ; Calculate pointer to map[i]
    lea     ebx, [esi + ecx*8]  ; ebx = &map[i]

    ; total += map[i].times
    add     eax, [ebx+4]        ; add times field to total

.next_char:
    inc     ecx
    jmp     .loop_start

.loop_end:
    pop     esi
    pop     ebx
    leave
    ret


; int get_modal_chars(modal_character map[], int modal_freq, char modal_chars[])
_get_modal_chars:
    push    ebp
    mov     ebp, esp

    push    esi
    push    edi
    push    ebx

    xor     edi, edi            ; edi = modal_count
    xor     ecx, ecx            ; ecx = i = 0 loop counter

.loop_start:
    cmp     ecx, 94
    jge     .loop_end

    ; Calculate pointer to map[i]
    mov     esi, [ebp+8]        ; map pointer
    lea     esi, [esi + ecx*8]  ; esi = &map[i] (each struct = 8 bytes)

    mov     eax, [esi+4]        ; map[i].times
    cmp     eax, [ebp+12]       ; compare with modal_freq
    jne     .next_char
    cmp     eax, 0              ; check if modal_freq > 0
    jle     .next_char

    mov     al, [esi]           ; map[i].character
    mov     ebx, [ebp+16]       ; modal_chars pointer
    mov     [ebx+edi], al       ; modal_chars[modal_count] = character

    inc     edi                 ; modal_count++

.next_char:
    inc     ecx
    jmp     .loop_start

.loop_end:
    mov     eax, edi            ; return modal_count
    pop     ebx
    pop     edi
    pop     esi
    pop     ebp
    ret