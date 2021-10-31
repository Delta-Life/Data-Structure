#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree * Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree getMaxValueInTree(Tree root){
	if (root == NULL)
		return NULL;
	else if (root->right == NULL)
		return root;
	else
		return getMaxValueInTree(root->right);
}

Tree insertNode(Tree root, int key){
	if (root == NULL){
		root = malloc(sizeof(struct BinarySearchTree));
		root->value = key;
		root->left = NULL;
		root->right = NULL;
		printf("insert %d\n", key);
	} else if (key < root->value){
		root->left = insertNode(root->left, key);
	} else if (key > root->value){
		root->right = insertNode(root->right, key);
	} else{
		printf("Insertion Error : There is already %d in the tree.\n", key);
	}
	return root;
}

Tree deleteNode(Tree root, int key){
	Tree tmp;

	if (root == NULL){
		printf("Deletion Error : %d is not in the tree.\n", key);
	} else if (key < root->value){
		root->left = deleteNode(root->left, key);
	} else if (key > root->value){
		root->right = deleteNode(root->right, key);
	} else if (root->left && root->right) {
		tmp = getMaxValueInTree(root->left);
		root->value = tmp->value;
		root->left = deleteNode(root->left, root->value);
	} else{
		tmp = root;
		if (root->right == NULL)
			root = root->left;
		else if (root->left == NULL)
			root = root->right;
		free(tmp);
	}
	return root;
}

void findNode(Tree root, int key){
	if (root == NULL)
		printf("%d is not in the tree.\n", key);
	else if (key < root->value)
		findNode(root->left, key);
	else if (key > root->value)
		findNode(root->right, key);
	else
		printf("%d is in the tree.\n", key);
}

void printInorder(Tree root){
	if(root->left != NULL){
		printInorder(root->left);
	}
	printf("%d ", root->value);
	if(root->right != NULL){
		printInorder(root->right);
	}
}

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;

	while (!feof(fi)){
		fscanf(fi, "%c", &cv);
		switch(cv){
		case 'i':
			fscanf(fi, "%d", &key);
			root = insertNode(root, key);
			break;
		case 'd':
			fscanf(fi, "%d", &key);
                        deleteNode(root, key);
                        break;
		case 'f':
			fscanf(fi, "%d", &key);
                        findNode(root, key);
                        break;
		case 'p':
			fscanf(fi, "%c", &cv);
			if (cv == 'i')
				printInorder(root);
			printf("\n");
                        break;
		}
	}
}
