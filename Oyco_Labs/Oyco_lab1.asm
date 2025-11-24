; Name: Cedric T Oyco
; Section: 1
;
; File: surname_lab1.asm
;
; Instructions: 
; 
; 1) Prompt the user to input a temperature in degrees Celsius.
;
; 2) Convert the Celsius value to Fahrenheit.
;    Formula: F = (C × 9) / 5 + 32
;
; 3) Convert the Fahrenheit value to Kelvin.
;    Formula:  K = (F - 32) × 5/9 + 273
;
; 4) Convert the Kelvin value back to Celsius.
;    Formula: C = K - 273
;
; 5) Display the result at each step using calls to print_string and print_int.
; 
; Notes:
; * Use only unsigned integer math - truncate any fractional values
; * Use registers appropriately - clean up of the Floating Point Unit (FPU) is not required
; * Assume input is valid and within reasonable bounds (e.g., no negative temperatures, no absurdly large or odd inputs, etc.)
; * A Python script is provided to validate your results
;

%include "asm_io.inc"

segment .data

prompt db "Enter a temperature in degree Celcius: ", 0
result db "You entered -> ", 0
faren_message db "Your temp in fahrenheit -> ", 0
kel_message db "Your temp in kelvin -> ", 0
cel_message db "Your temp in celcius -> ", 0


segment .bss

user_input resd 1
fahrenheit resd 1
kelvin resd 1
celcius resd 1 

segment .text
        global  _asm_main

_asm_main:
        enter   0,0               ; setup routine
        pusha
        

;
; code is put in the text segment, but do not modify the code
; before this comment.
;


take_input:
        ; TODO: Prompt for a Celsius value then read input.
        mov eax, prompt                         
        call print_string
        call read_int 
        mov [user_input], eax
        jmp celsius_to_fahrenheit
        

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
        mov [fahrenheit], eax
        mov eax, faren_message 
        call print_string
        mov eax, [fahrenheit]
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call    print_nl
        jmp fahrenheit_to_kelvin

        

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
        mov [kelvin], eax
        mov eax, kel_message 
        call print_string
        mov eax, [kelvin]
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call    print_nl
        jmp kelvin_to_celsius


        


kelvin_to_celsius:
        ; TODO: Convert the Kelvin value back to Celsius. Print out the result.
        ; C = K - 273

        sub eax, 273

        ;print
        mov [celcius], eax
        mov eax, cel_message 
        call print_string
        mov eax, [celcius]
        call print_int                  ; ma print sya sng faren kay ara sa eax
        call    print_nl
        jmp end ; di ba call dapat kay mey return? kaso ga x sa mag compile

        
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