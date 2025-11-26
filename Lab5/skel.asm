%include "asm_io.inc"

segment .data

segment .bss

segment .text
        
        global  _asm_main
_asm_main:
        enter   0,0               ; setup routine
        pusha

;
; code is put in the text segment, but do not modify the code
; before this comment.
;

        mov     eax, hello_msg    ; eax = "Hello, world!"
        call    print_string      ; print(eax)

        call    print_nl          ; print("\n")
        call    print_nl          ; print("\n")

;
; return to C driver. Do not modify the code
; after this comment.
;
        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret