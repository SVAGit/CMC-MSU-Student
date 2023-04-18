#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	int data;
	struct list* prev;
	struct list* next;
	}list;
//функции для списка
list* create_node(int item, list* reserv){
	list* ptr = calloc(1, sizeof(list));
	ptr->next = NULL;
	ptr->prev = reserv;
	ptr->data = item;
	return ptr;
	}

void add_node(list** head, list* reserv ,int item){
	if(*head == NULL){
		*head = create_node(item, reserv);
		}
	else add_node(&((*head)->next), *head, item); 
	}
	
void del_node(list* head){
	if(head->next == NULL){
		if(head->prev == NULL){
			free(head);
			head = NULL;
			return;
		}
		head->prev->next = NULL;
		free(head);
		head = NULL;
		return;
		}
	del_node(head->next);
	}
int main(){
	list* head = NULL;
	add_node(&head, NULL, 5);
	add_node(&head, NULL, 6);
	del_node(head);
	if(head->next == NULL)
		printf("%d", 0);
	Danik;
	return 0;
	}
