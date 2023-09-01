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
        search(root->left, key,count++);
    else 
		search(root->right, key, count++);
}


node* delete(node* root, int key){
    node*t;
    if(root == NULL)
		return root;
	else if(key < root->data)
		root->left = delete(root->left, key);
	else if(key > root->data)
		root->right = delete(root->right, key);
	else if(root->left && root->right){
			t = min(root->right);
			root->data = t->data;
			root->right = delete(root->right, key);
		}
		else{
			t = root;
			if(root->left == NULL)
				root = root->right;
			else if(root->right == NULL)
					root = root->left;
			}
	free(t);
	return root;
}

void print_level(node* root, int lavel){
	if(root->left == NULL && root->right == NULL)
		printf("%d in lavel %d", root->data, lavel);
	}

int main(){
	node* root = NULL;
	add(&root,5);
	add(&root,3);
	add(&root,4);
	add(&root,10);
	add(&root,13);
	add(&root,11);
	
	return 777;
	}
