%include "asm_io.inc"



segment .text
    global _asm_main

_asm_main:
    enter 0,0
    pusha

    ;------------------------------
    ; Initial dump (before doing anything)
    ;------------------------------
    dump_regs 1

    ;------------------------------
    ; Print the initial value AT THE TOP OF THE STACK
    ;------------------------------
    mov eax, [esp]   ; read the pushed value
    call print_int
    call print_nl
    ;------------------------------
    ; Before pushing - print ESP
    ;------------------------------
    mov eax, esp
    call print_int
    call print_nl
    
    ;------------------------------
    ; Put 5 in EAX
    ;------------------------------
    mov eax, 5
    call print_int
    call print_nl

    ;------------------------------
    ; PUSH EAX (push 5)
    ;------------------------------
    push 5       ; ESP -= 4, [ESP] = 5

    ;------------------------------
    ; Put 7 in EAX
    ;------------------------------
    mov eax, 7
    call print_int
    call print_nl

    ;------------------------------
    ; PUSH EAX (push 7)
    ;------------------------------
    push eax       ; ESP -= 4, [ESP] = 7

            ;------------------;992 <--ESP
            ;         7
            ;------------------;996
            ;         5
            ;------------------;1000

    ;------------------------------
    ; After pushing - print ESP again ; should be orgig - 8
    ;------------------------------
    mov eax, esp 
    call print_int
    call print_nl

    ;------------------------------
    ; Print the value AT THE TOP OF THE STACK
    ;------------------------------
    mov eax, [esp]   ; read the pushed value
    call print_int        ; should print 7
    call print_nl

    ;------------------------------
    ; Print the value 2nd OF THE STACK
    ;------------------------------
    mov eax, [esp+4]      ; read the pushed value
    call print_int        ; should print 5
    call print_nl

    ;------------------------------
    ; Final register dump
    ;------------------------------
    dump_regs 2



    ;------------------------------
    ; Clean up stack (remove the pushed 5 and 7)
    ;------------------------------
    add esp, 8

    popa
    mov eax, 0
    leave
    ret
; Register Dump # 1
; EAX = 00000001 EBX = 00621A20 ECX = 00621900 EDX = 76F6DFBC
; ESI = 00000000 EDI = 01121588 EBP = 00E3FB98 ESP = 00E3FB78
; EIP = 00621502 FLAGS = 0202
; 17962376
; 14941048
; 5
; 7
; 14941040
; 7
; 6
; Register Dump # 2
; EAX = 00000006 EBX = 00621A20 ECX = 00621900 EDX = 76F6DFBC
; ESI = 00000000 EDI = 01121588 EBP = 00E3FB98 ESP = 00E3FB70
; EIP = 0062156A FLAGS = 0202

; -------------------------------------------
; print eax in HEX (8 digits)
; -------------------------------------------
print_hex:
    pusha                ; save registers

    mov ecx, 8           ; we will print 8 hex digits
    mov ebx, eax         ; value to print

.hex_loop:
    rol ebx, 4           ; rotate left 4 bits (1 hex digit)
    mov edx, ebx
    and edx, 0Fh         ; extract lowest hex digit

    cmp edx, 9
    jbe .digit_is_number
    add edx, 55h         ; convert 10–15 to 'A'–'F'
    jmp .print_it

.digit_is_number:
    add edx, 30h         ; convert 0–9 to '0'–'9'

.print_it:
    mov eax, edx
    call print_char

    loop .hex_loop

    popa
    ret

