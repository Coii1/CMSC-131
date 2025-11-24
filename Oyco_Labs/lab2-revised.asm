; Name: 
; Section: 
;
; File: surname_lab2.asm
;
; Instructions:
; 
; 1) Prompt the user to input an initial account balance (in centavos) as an integer.
;
; 2) Prompt the user to input an annual interest rate as a fixed point integer.
;
; 3) Prompt the user to input the number of years Y as an integer.
;
; 4) Simulate Y years of annual interest calculations.
;    Formula: Balance_next = Balance_current + (Balance_current × Interest) / 100
;
; 5) After each year, display the current balance in floating point representation.
; 
; Notes:
; * Banks store your money in fixed point representation and only output the floating point representation at the end.
; * It is possible to convert from fixed point integer representation to floating point representation with only non-FPU instructions.
; * A Python script is provided to validate your results.
;

%include "asm_io.inc"

segment .data

prompt_balance db "Enter a initial account balance in centavos(e.g. 100 -> Php1): ", 0
prompt_interest db "How much would you like as the interest rate: ", 0
prompt_years db "Enter the number of years for this investment: ", 0
;year_num dd 0
year_label db " Year: ", 0
balance_label db " -> Balance: ", 0

segment .bss
;
; uninitialized data is put in the bss segment
;
user_balance resd 1
interest resd 1
years resd 1


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
        mov eax, prompt_balance
        call print_string
        call read_int
        mov [user_balance], eax

        mov eax, prompt_interest
        call print_string
        call read_int
        mov [interest], eax

        mov eax, prompt_years
        call print_string
        call read_int
        mov [years], eax
        mov ecx, eax                    ;counter para sa loop

        jmp yearly_balance


yearly_balance:

        ; calculate new balance
        mov eax, [user_balance]
        mov ebx, [interest]
        mul ebx                         ; now eax = balance*interest
        mov ebx, 10000                  ; 
        xor edx, edx                    ; clear remainder before div, kay sa edx gakadto and remainder diba? taz and gina divide di is EDX:EAX          
        div ebx                         ; eax is now (Balance_current × Interest) / 100
        
        ; mov ebx, 19                     ;
        ; mul ebx
        ; mul ebx
        ; shr eax, 12

        add eax, [user_balance]
        mov [user_balance], eax

        ;printing
                ;year
        mov eax, year_label
        call print_string

        ; mov eax, [year_num]
        ; add eax, 1
        ; call print_int
        ; mov [year_num], eax

        mov eax, [years]
        sub eax, ecx
        add eax, 1
        call print_int

        mov eax, balance_label
        call print_string
                ;amount
        mov eax, [user_balance]

        ; mov ebx, 100
        ; xor edx, edx 
        ; div ebx

        ; mov ebx, 19
        ; mul ebx
        ; shr eax, 6 

        shr eax, 2
        mov ebx, 41943
        mul ebx
        shr eax, 20

        call print_int
        mov eax, '.'
        call print_char
        call check_remainder            ; kay if 5 ang remainder, dapat ma num.05, indi .5
        mov eax, edx
        call print_int
        call print_nl
        loop yearly_balance
        jmp end                         ; end correctly tapos sng loop para indi mag fall through sa check remainder


check_remainder:
        cmp edx, 10
        jl pad
        ret
        
pad:
        mov eax, 0
        call print_int
        ret

        
end:

;
; return to C driver. Do not modify the code
; after this comment.
;
        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret