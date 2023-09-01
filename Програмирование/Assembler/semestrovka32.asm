%include "io.inc"

section .data
    HEAP_MAX_SIZE equ 256
    NULL equ 0
    MAX_WORD_LENGHT equ 8
    MAX_WORD_VOLUME equ 20
section .bss
    struc memory_node
        next_node resd 2
    endstruc
    
    struc list_node
        data resb 9
        volume resd 1
        next resd 1 
    endstruc
    
    heap resb HEAP_MAX_SIZE * memory_node_size
    heap_ptr resd 1
    
    array_list resq 8 ; используем для нашей структуры
    help_array resb 9 ; используется для заполнения поля data листа
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    call init_heap
    call MAIN_SCAN_FUNCTION
    push array_list
    call MAIN_PRINT_FUNCTION
    add esp, 4
    ret


init_heap:
    enter 0, 0
    lea esi, [heap]
    mov [heap_ptr], esi
    mov edi, esi
    add edi, memory_node_size
    mov ecx, HEAP_MAX_SIZE
.cycle:
    mov [esi + next_node], edi
    add esi, memory_node_size
    add edi, memory_node_size
    loop .cycle
    
    mov dword[esi - memory_node_size + next_node], NULL    
    leave
    ret
    
new:
    enter 0, 0
    
    xor ecx, ecx
.cycle:
    cmp ecx, [ebp + 8]
    jnl .end
    add ecx, memory_node_size
    jmp .cycle
.end:
    mov eax, [heap_ptr]
    cmp eax, NULL
    je .bad_alloc
    
    add [heap_ptr], ecx
    
   jmp .finish 
.bad_alloc:
    PRINT_STRING "Heap is empty\n"
.finish:    
    leave
    ret

;вспомогательная функция, читает лист и печатает все слова, которые встречаются один раз
;void PRINT_LIST(struct list_node* head)    
PRINT_LIST:
    enter 0, 0
    push ecx
    mov esi, [ebp + 8]
.cycle:
    cmp esi, NULL
    je .finish
    
    mov ecx, [esi + volume]
    cmp ecx, 1
    jg .next
    xor ecx, ecx
.print:    
    cmp byte[esi + ecx], `\0`
    je .next
    
    PRINT_CHAR [esi + ecx]
    inc ecx
    jmp .print
.next:
    PRINT_CHAR ' '
    mov esi, [esi + next]
    jmp .cycle
.finish:
    pop ecx  
    leave
    ret 
     
; эта функция будет считывать одно словo в массив, а вернем длину этого слова через EAX 
; int SCAN_WORD(void)
SCAN_WORD:
    enter 0, 0
    xor ebx, ebx; счетчик букв в слове
    mov edi, help_array
    xor eax, eax
.scan:
    GET_CHAR al
    cmp eax, '.'
    je .finish
    
    cmp eax, ','
    je .finish
    
    stosb
    inc ebx
    jmp .scan
.finish:
    mov dword[edi], `\0`
    mov eax, ebx
    leave
    ret
    
; создает лист с заполненым массивом, и возвращает адрес на ячейку
; struct list_node* CREATE_LIST(*char help_array)   
CREATE_LIST:
    enter 0, 0
    mov esi, [ebp + 8]
    
    push dword list_node_size
    call new
    add esp, 4
    
    mov edi, eax
.cycle:
    cmp byte[esi], `\0`
    je .end
    
    movsb
    jmp .cycle
.end:
    mov byte[edi], `\0`
    mov dword[eax + volume], 1
    mov dword[eax + next], NULL
    leave
    ret
    
; вспомогательная функция, принимает адрес листа,адрес массива,размер, и вставляет его в массив списков
; void PUSH_LIST(struct list_node* ptr, struct list_node* array_list, int lenght)
PUSH_LIST:
    enter 0, 0
    mov esi, [ebp + 8];ptr
    mov eax, [ebp + 12];array_list
    mov ecx, [ebp + 16];lenght
    dec ecx

    mov ebx, [eax + 4*ecx]; array_list[lenght-1]
    mov edi, ebx; далее используем cmpsb, нам нужна копия
    
    cmp edi, NULL
    jne .sort
    
    mov dword[eax + 4*ecx], esi; создаем голову списка
    jmp .finish
.sort:
    cmp byte[esi], `\0`
    je .twin ;слова совпадают, и мы увеличиваем счетчик
    
    cmpsb
    jg .next
    jl .prev
    jmp .sort
.next:
    cmp dword[ebx + next], NULL
    je .push_back
    ;обновим esi и edi
    mov edi, [ebx + next]
    mov esi, [ebp + 8]
    
    mov edx, ebx; copy ebx; prev list_node
    mov ebx, edi; inc ebx
    mov ecx, ebx; indicator
    jmp .sort
.prev:
    cmp ecx, ebx; если нам нужно поменять голову, то ecx будет хранить мусор,т.к в .next мы не попадем
    jne .head
    
    mov esi, [ebp + 8]; ptr
    mov [edx + next], esi
    mov [esi + next], ebx
    jmp .finish
.head:
    mov esi, [ebp + 8]; ptr
    mov [esi + next], ebx; prev list_node
    
    mov eax, [ebp + 12]
    mov [eax + 4*ecx], esi; изменяем голову
    jmp .finish
.twin:
    inc dword[ebx + volume]
    jmp .finish
.push_back:
    mov esi, [ebp + 8]
    mov [ebx + next], esi
.finish:
    pop edx
    leave
    ret
;функция сканирует текст и вводит в алфавитном порядке в массив листов
MAIN_SCAN_FUNCTION:
    enter 0, 0
    xor edx, edx
.scan:
    cmp edx, MAX_WORD_VOLUME
    je .end
    
    call SCAN_WORD
    cmp eax, 0
    je .end
    mov ecx, eax
    push ecx
    
    push help_array
    call CREATE_LIST
    add esp, 4
    
    pop ecx
    
    push ecx
    push array_list
    push eax
    call PUSH_LIST
    add esp, 12
    
    inc edx
    jmp .scan
.end:
    leave
    ret
    
;функция печатает массив листов    
MAIN_PRINT_FUNCTION:
    enter 0,0
    xor ecx, ecx
.cycle:
    mov esi, [ebp + 8]
    cmp ecx, MAX_WORD_LENGHT
    je .end
    PRINT_STRING 'Arrray list index: '
    PRINT_DEC 4, ecx
    NEWLINE
    
    push dword[esi + 4*ecx]
    call PRINT_LIST
    add esp, 4
    
    NEWLINE
    inc ecx
    jmp .cycle
.end:
    leave
    ret