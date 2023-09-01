#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int data;
    struct tree *left;
    struct tree *right;
} node;

node* create(int key){
    node *tmp = (node*)calloc(1,sizeof(node));
    tmp -> data = key;
    tmp -> left = NULL;
    tmp -> right = NULL;
    return tmp;
}

void add(node** root, int key){
	if(*root == NULL){
		*root = create(key);
		return;
	}
	if(key < (*root)->data)
		add(&((*root)->left), key);
	else
		add(&((*root)->right), key);
	}
	
int search(node* root, int key, int count){
    if ((root == NULL) || (root->data == key))
        return count;
    if (key < root->data)
        return search(root->left, key, ++count);
    else 
		return search(root->right, key, ++count);
}

int main(){
	node* root = NULL;
	add(&root,5);
	add(&root,3);
	add(&root,4);
	add(&root,10);
	add(&root,13);
	add(&root,11);
	printf("%d",search(root,11,0));
	return 777;
	}
