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
    mov eax, [esp]        ; read the pushed value
    call print_int        ; should print idk
    call print_nl



    

    ;------------------------------------
    ; MAKE A STABLE STACK FRAME
    ;------------------------------------
    push ebp        ; save caller's base pointer
    mov  ebp, esp   ; set our base pointer

    ; Now EBP is stable. ESP will move, but EBP won't.

    ;------------------------------
    ; Initial dump (before doing anything)
    ;------------------------------
    dump_regs 2

    ;------------------------------
    ; Before pushing - print ESP
    ;------------------------------
    mov eax, esp
    call print_int
    call print_nl

    ;------------------------------
    ; Before pushing - print EBP
    ;------------------------------
    mov eax, [esp]
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
    push eax       ; ESP -= 4, [ESP] = 5

    ;------------------------------
    ; After pushing - print ESP again
    ;------------------------------
    mov eax, esp
    call print_int
    call print_nl

    ;------------------------------
    ; Print the value AT THE TOP OF THE STACK
    ;------------------------------
    mov eax, [esp]   ; read the pushed value
    call print_int        ; should print 5
    call print_nl

    ;------------------------------
    ; Final register dump
    ;------------------------------
    dump_regs 3

    ;------------------------------
    ; Clean up stack (remove the pushed 5)
    ;------------------------------
    add esp, 4

    ;------------------------------------
    ; RESTORE THE STACK FRAME
    ;------------------------------------
    mov esp, ebp    ; undo temporary pushes
    pop ebp         ; restore caller's EBP

    popa
    mov eax, 0
    leave
    ret
