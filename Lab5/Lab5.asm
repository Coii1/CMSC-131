%include "asm_io.inc"

segment .text
    global _map_chars
    ;global _get_modal_frequency
    global _get_modal_chars

; void map_chars(char *input, modal_character *map, int *unique, int *chars)
_map_chars:
    enter 32, 0            ; reserve 32 bytes for locals
                           ; [ebp-4] = i
                           ; [ebp-8] = local_input pointer
                           ; [ebp-12] = local_map pointer
                           ; [ebp-16] = local_unique pointer
                           ; [ebp-20] = local_chars pointer
                           ; [ebp-24] = current_char
                           ; [ebp-28] = hash_index

    ; copy parameters into locals
    mov     eax, [ebp+8]   ; input
    mov     [ebp-8], eax

    mov     eax, [ebp+12]  ; map
    mov     [ebp-12], eax

    mov     eax, [ebp+16]  ; unique
    mov     [ebp-16], eax

    mov     eax, [ebp+20]  ; chars
    mov     [ebp-20], eax

    ; initialize i = 0
    mov     dword [ebp-4], 0

.loop_start:
    mov     eax, [ebp-4]       ; eax = i
    mov     ebx, [ebp-8]       ; ebx = input
    add     ebx, eax
    movzx   ecx, byte [ebx]    ; ecx = input[i], zero-extended
    cmp     cl, 0
    je      .loop_end           ; exit loop if input[i] == '\0'

    ; store current_char in local
    mov     [ebp-24], cl

    ; hash_index = current_char - 33
    movzx   eax, byte [ebp-24]  ; zero-extend to handle high-bit characters
    sub     eax, 33
    mov     [ebp-28], eax

    ; if (hash_index < 0 || hash_index >= 94) continue
    cmp     eax, 0
    jl      .increment_i
    cmp     eax, 94             ; 0..93 valid (reject >= 94)
    jge     .increment_i

    ; check if map[hash_index].times == 0
    mov     ebx, [ebp-12]       ; map pointer
    mov     ecx, [ebp-28]       ; hash_index
    imul    ecx, 8              ; each modal_character = 8 bytes (with padding)
    add     ebx, ecx
    mov     edx, [ebx+4]        ; times field
    cmp     edx, 0
    jne     .skip_unique_update

    ; map[hash_index].character = input[i]
    mov     al, [ebp-24]
    mov     [ebx], al

    ; (*unique)++
    mov     eax, [ebp-16]       ; unique pointer
    add     dword [eax], 1

.skip_unique_update:
    ; map[hash_index].times++
    mov     eax, [ebp-12]
    mov     ecx, [ebp-28]
    imul    ecx, 8
    add     eax, ecx
    add     dword [eax+4], 1

    ; (*chars)++
    mov     eax, [ebp-20]       ; chars pointer
    add     dword [eax], 1

.increment_i:
    ; i++
    add     dword [ebp-4], 1
    jmp     .loop_start

.loop_end:
    leave
    ret




; void get_modal_chars(modal_character *map, int modal_freq, char *modal_chars, int *modal_count)
_get_modal_chars:
    push    ebp
    mov     ebp, esp

    push    esi
    push    edi
    push    ebx

    ; Initialize *modal_count = 0
    mov     eax, [ebp+20]         ; modal_count pointer
    mov     dword [eax], 0

    xor     ecx, ecx              ; i = 0 loop counter

.loop_start:
    cmp     ecx, 94
    jge     .loop_end

    ; Calculate pointer to map[i]
    mov     edx, [ebp+8]          ; map pointer
    mov     ebx, ecx
    imul    ebx, 8
    add     edx, ebx              ; edx = &map[i]

    mov     eax, [edx+4]          ; map[i].times
    mov     ebx, [ebp+12]         ; modal_freq

    cmp     eax, ebx
    jne     .next_char
    cmp     ebx, 0
    jle     .next_char

    mov     dl, [edx]             ; map[i].character

    mov     esi, [ebp+16]         ; modal_chars pointer
    mov     edi, [ebp+20]         ; modal_count pointer
    mov     eax, [edi]            ; current modal_count

    mov     [esi+eax], dl         ; modal_chars[modal_count] = character

    inc     eax
    mov     [edi], eax

.next_char:
    inc     ecx
    jmp     .loop_start

.loop_end:
    pop     ebx
    pop     edi
    pop     esi
    pop     ebp
    ret
