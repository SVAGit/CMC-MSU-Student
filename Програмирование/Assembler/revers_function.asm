%include 'io.inc'
section .bss
    mas resd 32
section .text
global main
main:
    mov edi, mas
    GET_UDEC 4, ebx; вводиться количество цифр
    mov ecx, ebx
scan:
    GET_UDEC 4, eax
    cmp ebx, 0
    je end_scan
    dec ebx
    stosd
    jmp scan
end_scan:
    push ecx
    call revers
    pop ecx
    mov esi, mas
print:
    cmp ecx, 0
    je end_print
    lodsd
    PRINT_UDEC 4, eax
    PRINT_CHAR ' '
    dec ecx
    jmp print
end_print:
    ret   
revers:
    push ebp
    mov ebp, esp
    mov ecx, [ebp + 8]
    xor ebx, ebx
    dec ecx
.cycle:
    cmp ebx, ecx
    jge .stop
    mov edx, [mas + 4*ecx]
    push dword[mas + 4*ebx]
    mov [mas + 4*ebx], edx
    pop edx
    mov [mas + 4*ecx], edx
    inc ebx
    dec ecx
    jmp .cycle
.stop:
    mov esp, ebp
    pop ebp
    ret    