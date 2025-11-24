%include "asm_io.inc"

segment .data

; initialized data is put in the data segment here

hello_msg db "Hello, world!", 0    ; null-terminated string for printing
something dq 2

segment .bss

label resd 1
; uninitialized data is put in the bss segment


segment .text
        global  _asm_main
_asm_main:
        enter   0,0               ; setup routine
        pusha

; code is put in the text segment, but do not modify the code before this comment.

        ; mov     eax, 1001b     
        ; call    print_int   
        
        ; mov ebx, 2
        ; mov [label], ebx
        ; mov eax, [label]

        ; mov dword [label], 4
        ; mov ebx, [label]

        ; dump_regs 1     

        ; call print_nl
        ; call print_nl

        ; dump_mem something, 2
        


        mov bx, 1
        mov ax, bx

        dump_regs 1





        call    print_nl          ; print("\n")



; return to C driver. Do not modify the code after this comment.

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret