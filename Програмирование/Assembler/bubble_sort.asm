%include 'io.inc'
section .bss
    arr resd 255

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    xor ebx, ebx
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    mov edi, arr
    GET_UDEC 1, ebx ;вводиться кол-во элементов
    mov ecx, ebx ;для вывода
scan:
    cmp edx, ebx
    je end_scan
    GET_UDEC 4, eax
    stosd
    inc edx
    jmp scan
end_scan:
    inc ebx
bubble_sort:
    dec ebx
    cmp ebx, 1
    je end_bubble
    mov eax, 0
    mov edx, 1
bubble:
    cmp edx, ebx
    je bubble_sort
    mov esi, [arr + 4*eax]
    mov edi, [arr + 4*edx]
    cmp esi, [arr + 4*edx]
    jle inc_bubble
    mov [arr + 4*edx], esi
    mov [arr + 4*eax], edi
inc_bubble:
    inc eax
    inc edx
    jmp bubble
end_bubble:
    mov esi, arr
    xor edx, edx
print:
    cmp edx, ecx
    je end
    lodsd 
    PRINT_UDEC 4, eax
    PRINT_STRING ' '
    inc edx
    jmp print 
end:
    ret