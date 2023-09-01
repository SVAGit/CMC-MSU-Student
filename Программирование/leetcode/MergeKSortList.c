#include <stdio.h>
#include <stdlib.h>

tpedef struct ListNode {
     int val;
     struct ListNode *next;
 }ListNode;
 
ListNode* create_node(int key){
	ListNode* ptr = (node*)calloc(1,sizeof(node));
	ptr->val = key;
	ptr->next = NULL;
	return ptr;
}

void add_node(**ListNode head, int key){
	if(*head == NULL){
		*head = create_node(key);
		return;
	}
	return add_node(&((*head)->next), key);
	}

int* mergeKLists(struct ListNode** lists, int listsSize){
    ListNode* head = NULL;
    int n = 10;
    int count = 0;
    int* mas = calloc(n,sizeof(int)); 
    for(int i = 0, j = 0; i < listsSize; i++){
        for(;lists->val->next != NULL; j++){
            if(n<j){
                n *= 2;
                int* mas = realloc(n,sizeof(int));
            }
            mas[j] = lists->val->val;
            lists->val->val = lists->val->next;
        }
    lists->val = lists->next;
    }
	return mas;
}
int main(){
	int listsSize = 1;
	ListNode* head = NULL;
	add_node(*head, 1);
	add_node(*head, 2);
	add_node(*head, 3);
	
	}
