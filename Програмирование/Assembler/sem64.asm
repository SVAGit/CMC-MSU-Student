section .data
    HEAP_MAX_SIZE equ 256
    NULL equ 0
    MAX_WORD_LENGHT equ 8
    MAX_WORD_VOLUME equ 20
    heap_format db "Heap is empty", `\n`, `\0`
    printf_format db "%s ", `\0`
    index db "Array list index: %d", `\n`, `\0`
    newline db `\n`, `\0`
section .bss
    struc memory_node
        next_node resq 2
    endstruc
    
    struc list_node
        data resb 9
        volume resq 1
        next resq 1 
    endstruc
    
    heap resb HEAP_MAX_SIZE * memory_node_size
    heap_ptr resq 1
    
    array_list resq 8 ; используем для нашей структуры
    help_array resb 9 ; используется для заполнения поля data листа
section .text
extern printf
extern getchar
global main
main:
    enter 0, 0
    call init_heap
    mov rdi, help_array
    mov rsi, array_list
    call MAIN_SCAN_FUNCTION
    mov rdi, array_list
    call MAIN_PRINT_FUNCTION
    leave
    ret


init_heap:
    enter 0, 0
    lea rsi, [heap]
    mov [heap_ptr], rsi
    mov rdi, rsi
    add rdi, memory_node_size
    mov rcx, HEAP_MAX_SIZE
.cycle:
    mov [rsi + next_node], rdi
    add rsi, memory_node_size
    add rdi, memory_node_size
    loop .cycle

    mov qword[rsi - memory_node_size + next_node], NULL    
    leave
    ret
    
new:
    enter 0, 0
    
    xor rcx, rcx
.cycle:
    cmp rcx, rdi
    jnl .end
    add rcx, memory_node_size
    jmp .cycle
.end:
    mov rax, [heap_ptr]
    cmp rax, NULL
    je .bad_alloc
    
    add [heap_ptr], rcx
    
   jmp .finish 
.bad_alloc:
    mov rdi, heap_format
    call printf
.finish:    
    leave
    ret

;вспомогательная функция, читает лист и печатает все слова, которые встречаются один раз
;void PRINT_LIST(struct list_node* head)    
PRINT_LIST:
    enter 0, 0
.cycle:
    cmp rdi, NULL
    je .finish
    
    mov rcx, [rdi + volume]
    cmp rcx, 1
    jg .next   
    
    push rdi
    mov rsi, rdi
    mov rdi, printf_format
    call printf
    pop rdi
.next:
    mov rdi, [rdi + next]
    jmp .cycle
.finish: 
    leave
    ret 
     
; эта функция будет считывать одно словo в массив, а вернем длину этого слова через EAX 
; int SCAN_WORD(void)
SCAN_WORD:
    enter 0, 0
    xor rbx, rbx; счетчик букв в слове
    xor rax, rax
.scan:
    mov r15, rdi
    call getchar
    mov rdi, r15
    
    cmp rax, '.'
    je .finish
    
    cmp rax, ','
    je .finish
    
    stosb
    inc rbx
    jmp .scan
.finish:
    mov byte[rdi], `\0`
    mov rax, rbx
    leave
    ret
    
; создает лист с заполненым массивом, и возвращает адрес на ячейку
; struct list_node* CREATE_LIST(*char help_array)   
CREATE_LIST:
    enter 0, 0
    
    push rdi
    
    mov rdi, list_node_size
    call new
    
    pop rsi
    
    mov rdi, rax
.cycle:
    cmp byte[rsi], `\0`
    je .end
    
    movsb
    jmp .cycle
.end:
    mov byte[rdi], `\0`
    mov qword[rax + volume], 1
    mov qword[rax + next], NULL
    leave
    ret
    
; вспомогательная функция, принимает адрес листа,адрес массива,размер, и вставляет его в массив списков
; void PUSH_LIST(struct list_node* ptr, struct list_node* array_list, int lenght)
PUSH_LIST:
    enter 0, 0
    dec rdx
    mov r8, rdi
    mov r9, rsi
    mov r10, rdx
    mov rbx, [r9 + 8*r10]; array_list[lenght-1]
    mov rsi, rbx; далее используем cmpsb, нам нужна копия
    
    cmp rsi, NULL
    jne .sort
    
    mov [r9 + 8*r10], r8; создаем голову списка
    jmp .finish
.sort:
    cmp byte[rsi], `\0`
    je .twin ;слова совпадают, и мы увеличиваем счетчик
    
    cmpsb
    jl .next
    jg .prev
    jmp .sort
.next:
    cmp qword[rbx + next], NULL
    je .push_back
    ;обновим esi и edi
    mov r11, rbx; copy ebx; prev list_node
    mov rbx, [rbx + next]; inc ebx
    mov rcx, rbx; indicator
    
    mov rsi, rbx
    mov rdi, r8
    jmp .sort
.prev:
    cmp rcx, rbx; если нам нужно поменять голову, то ecx будет хранить мусор,т.к в .next мы не попадем
    jne .head
    
    mov [r11 + next], r8
    mov [r8 + next], rbx
    jmp .finish
.head:
    mov [r8 + next], rbx; prev list_node
    mov [r9 + 8*r10], r8; изменяем голову
    jmp .finish
.twin:
    inc qword[rbx + volume]
    jmp .finish
.push_back:
    mov [rbx + next], r8
.finish:
    leave
    ret

;функция сканирует текст и вводит в алфавитном порядке в массив листов
MAIN_SCAN_FUNCTION:
    enter 0, 0
    xor r8, r8
.scan:
    cmp r8, MAX_WORD_VOLUME
    je .end
    
    mov rdi, help_array
    call SCAN_WORD
    
    cmp rax, 0
    je .end

    push rax

    mov rdi, help_array
    call CREATE_LIST

    mov rdi, rax
    mov rsi, array_list
    pop rdx
    push r8
    call PUSH_LIST
    pop r8
    
    inc r8
    jmp .scan
.end:
    leave
    ret
    
;функция печатает массив листов    
MAIN_PRINT_FUNCTION:
    enter 0, 0
    xor r15, r15
.cycle:
    cmp r15, MAX_WORD_LENGHT
    je .end
    
    push rdi
    mov rdi, index
    mov rsi, r15
    call printf
    pop rdi
    ;PRINT_STRING 'Arrray list index: '
    ;PRINT_DEC 8, r15
    ;NEWLINE
    
    push rdi
    mov rdi, [rdi + 8*r15]
    call PRINT_LIST
    pop rdi
    
    push rdi
    mov rdi, newline
    call printf
    pop rdi
    ;NEWLINE

    inc r15
    jmp .cycle
.end:
    leave
    ret