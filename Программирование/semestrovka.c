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

int maxi(node* head){
	int max=0;
	while(head!=NULL){
		if(head->data > max)
			max = head->data;
		head = head->next;
	}
	return max;
}

int mini(node* head){
	node* ptr = head;
	int min = ptr->data;
	while(ptr != NULL){
		if(ptr->data < min)
			min = ptr->data;
		ptr = ptr->next;
	}
	return min;
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

void sort0(node* head){
	node* max = NULL;
	max->data = 0;
	node* ptr = head;
	while(ptr->next != NULL){
		node* iter = ptr;
		while(iter != NULL){
			if(iter->next->data > max->data){
				max->data = iter->next->data;
			}
			iter = iter->next;
		}
		ptr = max;
		ptr = ptr->next;
		}
	head = ptr;
	}
	
void sort1(node* head){
	if(head == NULL)
		return;
	printf("%d ", mini(head));
	del_elem(&head, mini(head));
	return sort1(head);
	}
	
void scan_list(node* head){
	int n;
	while(scanf("%d", &n) != '\n'){
		scanf("%d", &n);
		add_node(&head, n);
	}
	return;
	}
	
int main(){
	node* head = NULL;
	add_node(&head,1);
	add_node(&head,4);
	add_node(&head,7);
	add_node(&head,2);
	add_node(&head,1);
	char count;
		printf("Get '0' if you need descending order, or '1' if ascending order:\n");
		count = getchar();
		if (count == '0'){
			sort0(head);
			return 0;
		}
		if(count == '1'){
			sort1(head);
			return 1;
		}
	return 0;
}
