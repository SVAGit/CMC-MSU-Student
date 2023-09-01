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
	if((*head)->data == key){
		node* ptr = *head;
		*head = (*head)->next;
		free(ptr);
		return;
		}
	if((*head)->next->data == key){
		node* ptr = (*head)->next;
		(*head)->next = ((*head)->next)->next;
		free(ptr);
		return;
	}
	return del_elem(&((*head)->next), key);
	}
	
void del_input(node* head,int key){
	while(head != NULL){
		if(head->data == key)
			del_elem(&head, key);
		printf("%d ", head->data);
		head = head->next;
		}
	}
	
int main(){
	node* head = NULL;
	add_node(&head,10);
	add_node(&head,3);
	add_node(&head,11);
	add_node(&head,10);
	add_node(&head,11);
	printf("\n%d", head->data);
}
