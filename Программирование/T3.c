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

int proverka(node* root1,node* root2){
	if(root1 == NULL || root2 == NULL)
		return 0;
	if(root1->data != root2->data)
		return 0;
}	return(root1->left, root2->left);
		
		
	}

int main(){
	node* root1 = NULL;
	node* root2 = NULL;
	add(&root1,5);
	add(&root1,3);
	add(&root1,4);
	add(&root1,10);
	add(&root1,13);
	add(&root1,11);
	return 777;
	}
