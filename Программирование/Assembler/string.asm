%include 'io.inc'

section .bss
    x resw 256
    x_rows resw 20
section .text
global main
main:
    mov ebp, esp; for correct debugging
    mov edi, x
    xor ecx, ecx
    xor edx, edx
scan:
    mov [x_rows + 4*edx], edi
wor:
    GET_CHAR eax
    
    cmp eax, '.'
    je end_scan
    
    stosd
    
    cmp eax, ' '
    je plus_word
    jmp wor
    
plus_word:

    inc edx
    jmp scan
end_scan:
    mov dword[edi], `\0`
    push x_rows
    call C
    add esp, 4
    ret
    
C:
    enter 0, 0
    pushad
    mov edi, [ebp + 8]    
.cycle:
    mov esi, [edi]
    
    cmp dword[esi], 0
    je .end
    
    cmp dword[esi], 'c'
    jne .iteration
.print:
    cmp dword[esi], `\0`
    je .end
    
    cmp dword[esi], ' '
    je .end_print
    
    lodsd
    PRINT_CHAR eax
    jmp .print
.end_print:
    PRINT_STRING ' '
.iteration:
    add edi, 4
    jmp .cycle
.end:
    popad
    leave
    ret