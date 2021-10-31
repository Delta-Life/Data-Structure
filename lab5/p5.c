#include<stdio.h>
#include<stdlib.h>

struct TreeStruct{
	int Size;
	int NodeNum;
	int* Element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int TreeSize){
	Tree tree = malloc(sizeof(struct TreeStruct));
	tree->Element = malloc(sizeof(int) * (TreeSize + 1));
	tree->Size = TreeSize;
	tree->NodeNum = 0;
	return tree;
}

void Insert(Tree tree, int value){
	if(tree->NodeNum + 1 > tree->Size){
		printf("Error, Tree is full.\n");
	}else{
		tree->Element[++tree->NodeNum] = value;
	}
}

void printInorder(Tree tree, int index){
	if(index * 2 <= tree->NodeNum){
		printInorder(tree, index * 2);
	}
	printf("%d ", tree->Element[index]);
	if(index * 2 + 1 <= tree->NodeNum){
		printInorder(tree, index * 2 + 1);
	}
}

void printPreorder(Tree tree, int index){
	printf("%d ", tree->Element[index]);
	if(index * 2 <=tree->NodeNum){
		printPreorder(tree, index * 2);
	}
	if(index * 2 + 1 <= tree->NodeNum){
		printPreorder(tree, index * 2 + 1);
	}

}

void printPostorder(Tree tree, int index){
	if(index * 2 <=tree->NodeNum){
		printPostorder(tree, index * 2);
	}
	if(index * 2 + 1 <= tree->NodeNum){
		printPostorder(tree, index * 2 + 1);
	}
	printf("%d ", tree->Element[index]);
}

void printTree(Tree tree){
	printf("Preorder: ");
	printPreorder(tree, 1);
	printf("\nInorder: ");
	printInorder(tree, 1);
	printf("\nPostorder: ");
	printPostorder(tree, 1);
	printf("\n");
	free(tree->Element);
	free(tree);
 }

void main(int argc, char* argv[]){
	FILE* fi;
	Tree tree;
	int treeSize;
	int tempNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);
	tree = CreateTree(treeSize);
	while(fscanf(fi, "%d", &tempNum)==1){
		Insert(tree, tempNum);
	}
	printTree(tree);
}
