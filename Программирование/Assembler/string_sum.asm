%include "io.inc"
section .bss
    x resb 31
    y resb 31
    res resb 32
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    xor edx, edx
    xor ecx, ecx
    mov edi, x
scan1:
    GET_CHAR al
    cmp al ,`\n`
    je end1
    stosb
    inc edx
    jmp scan1
end1:
    mov byte[edi], `\0`
    mov edi, y
scan2:
    GET_CHAR al
    cmp al ,`\n`
    je end2
    stosb
    inc ecx
    jmp scan2
end2:
    mov byte[edi], `\0`
    xor eax, eax
    dec ecx
    mov bl, 10
cycle1:
    cmp edx, 0
    je end
    add al, [x + ecx]
    sub al, '0'
    add al, [y + ecx]
    sub al, '0'
    xor ah, ah
    div bl
    mov [res + edx], ah
    dec edx
    dec ecx
    jmp cycle1
end:
    mov [res + edx], al
    mov esi, res
print:
    cmp edx, 5
    je endend
    lodsb
    PRINT_DEC 1, al
    inc edx
    jmp print
endend:    
    ret 