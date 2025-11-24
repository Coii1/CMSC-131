%include "asm_io.inc"

segment .data

prompt db "Enter a temperature in degree Celcius: ", 0
result db "You entered -> ", 0
faren_message db "Your temp in fahrenheit -> ", 0
kel_message db "Your temp in kelvin -> ", 0
cel_message db "Your temp in celcius -> ", 0


segment .bss


segment .text
        global  _asm_main

_asm_main:
        enter   0,0               ; setup routine
        pusha
        
take_input:
        ; TODO: Prompt for a Celsius value then read input.
        mov eax, prompt                         
        call print_string
        call read_int 
        

celsius_to_fahrenheit:
        ; TODO: Convert the Celsius value to Fahrenheit. Print out the result.
        ; F = C × 9/5 + 32

        ; ma comment na di guro si sir ngaa gn butang ko pa sa ebx kag ebx gamit pang mul
        ; try mag mul nga diritso bi?

        mov ebx, 9
        mul ebx                         ; now eax*ebx is 9*userinput. is stored in eax if kasya and edx:eax if not
        mov ebx, 5
        div ebx                         ; eax = eax/ebx, remainder in edx
        add eax, 32                     ; now eax is the faren

        ;print
        mov edx, eax                    ;now ang fahrenheit ara na sa edx
        mov eax, faren_message 
        call print_string
        mov eax, edx                    ;balik sa eax and faren
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call print_nl 

fahrenheit_to_kelvin:
        ; TODO: Convert the Fahrenheit value to Kelvin. Print out the result.
        ; K = (F - 32) × 5/9 + 273.15
        sub eax, 32
        mov ebx, 5
        mul ebx                         ;eax *= ebx
        mov ebx, 9 
        div ebx
        add eax, 273

        ;print
        mov edx, eax                    ; butang sa edx and kelvin
        mov eax, kel_message 
        call print_string
        mov eax, edx                    ; now balik sa eax ang kelvin
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call    print_nl

kelvin_to_celsius:
        ; TODO: Convert the Kelvin value back to Celsius. Print out the result.
        ; C = K - 273

        sub eax, 273

        ;print
        mov edx, eax
        mov eax, cel_message 
        call print_string
        mov eax, edx
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call print_nl
        jmp end                         ; di ba call dapat kay mey return? kaso ga x sa mag compile

        
end:
        call    print_nl
;
; return to C driver. Do not modify the code
; after this comment.
;
        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret