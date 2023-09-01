%include "io.inc" 
section .bss 
    A resd 256 
    A_rows resd 16 
    B resd 256
    B_rows resd 16
    C resd 256
    C_rows resd 16
    m1 resd 1 
    n1 resd 1 
 section .text 
global CMAIN 
CMAIN: 
    mov ebp, esp; for correct debugging 
    GET_UDEC 4, m1 
    GET_UDEC 4, n1 
     
    push A_rows 
    push A 
    push dword[n1] 
    push dword[m1] 
    call INIT 
    add esp, 16 
     
    push A_rows 
    push dword[n1] 
    push dword[m1] 
    call READ
    add esp, 12
    
    push A_rows
    push dword[n1]
    push dword[m1]
    call MAX_SUMM
    add esp, 12
    PRINT_DEC 4, eax 
    ret 
 
INIT: 
    enter 0, 0 
    xor ecx, ecx 
    mov edi, [ebp + 16]; матрица 
    mov esi, [ebp + 20]; массив строк 
    shl dword[ebp + 12], 2 
.cycle:
    cmp ecx, [ebp + 8]
    je .end_cycle 
    mov [esi + 4 * ecx ], edi 
    add edi, dword[ebp + 12] 
    inc ecx 
    jmp .cycle
.end_cycle: 
    leave 
    ret 
 
READ: 
    enter 0, 0 
    xor ecx, ecx 
    mov esi, [ebp + 16]; массив строк 
.cycle: 
    cmp ecx, [ebp + 8] 
    je .end_cycle 
     
    mov edi, [esi + 4 * ecx] 
    xor edx, edx 
.inner_cycle: 
    cmp edx, [ebp + 12] 
    je .end_inner 
     
    GET_DEC 4, eax 
    stosd 
     
    inc edx 
    jmp .inner_cycle 
.end_inner: 
    inc ecx 
    jmp .cycle 
.end_cycle: 
    leave 
    ret 
 
print: 
    enter 0, 0 
    xor ecx, ecx 
    mov edi, [ebp + 16]; массив строк 
.cycle: 
    cmp ecx, [ebp + 8] 
    je .end_cycle 
     
    mov esi, [edi + 4 * ecx] 
    xor edx, edx 
.inner_cycle: 
    cmp edx, [ebp + 12] 
    je .end_inner 
     
    lodsd 
    PRINT_DEC 4, eax 
    PRINT_CHAR ' ' 
    inc edx 
    jmp .inner_cycle 
.end_inner: 
    PRINT_CHAR `\n` 
    inc ecx 
    jmp .cycle 
.end_cycle: 
    leave 
    ret
    
SUM:
    enter 0,0
    mov esi, [ebp + 24]; arr A
    mov edi, [ebp + 20]; arr B
    mov ebx, [ebp + 16]; arr C
    mov eax, [ebp + 12]
    mul dword[ebp + 8]
    push eax
    xor ecx, ecx
.cycle:
    cmp ecx, dword[ebp - 4]
    je .end
    
    mov eax, dword[esi + 4*ecx]
    add eax, dword[edi + 4*ecx]
    mov dword[ebx + 4*ecx], eax
    
    inc ecx
    jmp .cycle
.end:
    pop eax
    leave
    ret

MAX_SUMM:
    enter 0, 0
    mov edi, [ebp + 16]
    mov esi, [edi]
    mov edi, esi; адрес первого элемента в в A_rows
    xor eax, eax; max
    xor ecx, ecx; j
.cycle:
    cmp ecx, [ebp + 8]; номер столбца
    je .end
    xor edx, edx; i
    xor esi, esi; local max
    ;push ecx
    ;shl ecx, 2
    ;add edi, ecx
    ;pop ecx
.inner_cycle:
    cmp edx, [ebp + 12]; номер строки
    je .cont
    mov ebx, [edi + 4*edx]; i столбец, j строка 
    add esi, ebx
    inc edx; i++
    jmp .inner_cycle
.cont:
    inc ecx; j++
    cmp eax, esi
    jge .cycle
    mov eax, esi
    jmp .cycle
.end:
    leave
    ret