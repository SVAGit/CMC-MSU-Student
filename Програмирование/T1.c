#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}node;

node* create_node(int key){
	node* ptr = (node*)calloc(1,sizeof(node));
	ptr->data = key;
	ptr->next = NULL;
	return ptr;
}

void add_node(node** head, int key){
	if(*head == NULL){
		*head = create_node(key);
		return;
	}
	return add_node(&((*head)->next), key);
	}

int pop(node** head){
    node* prev = NULL;
    int val;
    if(head == NULL){
        exit(-1);
    }
    prev = (*head);
    val = prev->data;
    (*head) = (*head)->next;
    free(prev);
    return val;
}
	
node* search_Nelem(node* head, int n) {
    int count = 1;
    while (count < n){
        head = head->next;
        count++;
    }
    return head;
}

node* search_elem(node* head, int key){
	while(head->data != key){
		if(head == NULL)
			return head;
		head = head->next;
	}
	return head;
}

int maxi(node* head){
	int max=0;
	while(head!=NULL){
		if(head->data > max)
		max = head->data;
		head = head->next;
	}
	return max;
}
		
void del_elem(node** head, int key){
	if(*head == NULL)
		return;
	
	if((*head)->data == key){
		node* ptr = *head;
		*head = (*head)->next;
		free(ptr);
		return;
		}
	/*if((*head)->next->data == key){
		node* ptr = (*head)->next;
		(*head)->next = ((*head)->next)->next;
		free(ptr);
		return;
	}*/
	del_elem(&((*head)->next), key);
	}
	
/*void del_input(node** head,int key){
	node* ptr = *head;
	int count = 0;
	while(ptr != NULL){
		if(ptr->data == key)
			count++;
		ptr = ptr->next;
		}
	for(int i = 0; i < count; i++)
		del_elem(head,key);
	}*/
	
void del(node* head){
	if(head == NULL)
	 return;
	int item = head->data;
	del_elem(&(head->next), item);
	del(head->next);
	}

void print_list(node* head){
	node* ptr = head;
	while(ptr != NULL){
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	free(ptr);
	}
	
int main(){
	node* head = NULL;
	add_node(&head,10);
	add_node(&head,3);
	add_node(&head,11);
	add_node(&head,10);
	add_node(&head,11);
	print_list(head);
	del(head);
	
	print_list(head);
}
