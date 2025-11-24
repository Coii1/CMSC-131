; Name: Cedric Oyco
; Section: 
;
; File: surname_lab3.asm
;
; Instructions:
; 
; 1) Prompt the user for network packet fields:
;    - Source IP address
;    - Destination IP address
;    - Source port number
;    - Destination port number
;    - Packet length in bits
;
; 2) Display the packet in x86 little endian format
;
; 3) Convert the packet to network big endian format for "transmission"
;
; 3) Simulate receiving the packet and converting back to little endian
;
; Notes:
; * Store packet data only in registers
; * You may use the dump_regs macro to display hex values
; * Final values should match original input (round-trip conversion)
; * EBP, ESP, EIP, FLAGS are used internally - do not modify
;

%include "asm_io.inc"

segment .data
;
prompt_IP db "Input the source IP: ", 0
prompt_DIP db "Input the destination IP: ", 0
prompt_SP db "Input the source port: ", 0
prompt_DP db "Input the destination port: ", 0
prompt_PL db "Input the packet length in bits: ", 0
received_msg db "Received Little Endian Packet!", 0



segment .bss
;
; uninitialized data is put in the bss segment
;


segment .text
        global  _asm_main
_asm_main:
        enter   0,0               ; setup routine
        pusha

;
; code is put in the text segment, but do not modify the code
; before this comment.
;


        mov eax, prompt_IP              ;edi muna karon balik ni sa eax
        call print_string
        call read_int
        mov edi, eax
        
        mov eax, prompt_DIP             ;ebx and DIP
        call print_string
        call read_int
        mov ebx, eax

        mov eax, prompt_SP              ;ecx and SP
        call print_string
        call read_int
        mov cx, ax
        rol eax, 16                     ; ara na sa e and sp

        mov eax, prompt_DP              ;edx and DP
        call print_string
        call read_int
        mov cx, ax                      ; cx ang DP

        mov eax, prompt_PL              ;edx and PL
        call print_string
        call read_int
        mov edx, eax

        mov eax, edi                    ; balik sa eax and IP
        xor edi, edi


        dump_regs 1
        call reverse_endianness
        dump_regs 2
        call reverse_endianness
        dump_regs 3
        call print_nl

reverse_endianness:        
        rol ax, 8
        rol eax, 16
        rol ax, 8

        rol bx, 8
        rol ebx, 16
        rol bx, 8

        rol cx, 8
        rol ecx, 16
        rol cx, 8

        rol dx, 8
        rol edx, 16
        rol dx, 8

        rol si, 8
        rol esi, 16
        rol si, 8

        call print_nl

        ret



        ; rol ax, 8
        ; rol eax, 16
        ; rol ax, 8

        ; rol bx, 8
        ; rol ebx, 16
        ; rol bx, 8

        ; rol cx, 8
        ; rol ecx, 16
        ; rol cx, 8

        ; rol dx, 8
        ; rol edx, 16
        ; rol dx, 8

        ; rol si, 8
        ; rol esi, 16
        ; rol si, 8
        
        ; dump_regs 3


;
; return to C driver. Do not modify the code
; after this comment.
;
        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret