#include<stdio.h>
#include<stdlib.h>

struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;

struct AVLNode{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

Position SingleRotateWithLeft(Position node);
Position DoubleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithRight(Position node);

ElementType Max(ElementType X, ElementType Y){
	return X > Y ? X : Y;
}

int Height(AVLTree T){
	return T != NULL ? T->Height : -1;
}

Position SingleRotateWithLeft(Position node){
	Position node2 = node->Left;
	node->Left = node2->Right;
	node2->Right = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	node2->Height = Max(Height(node2->Left), Height(node2->Right)) + 1;

	return node2;
}

Position DoubleRotateWithLeft(Position node){
	node->Left = SingleRotateWithRight(node->Left);
	return SingleRotateWithLeft(node);
}

Position SingleRotateWithRight(Position node){
	Position node2 = node->Right;
        node->Right = node2->Left;
        node2->Left = node;

        node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
        node2->Height = Max(Height(node2->Left), Height(node2->Right)) + 1;

	return node2;
}
Position DoubleRotateWithRight(Position node){
	node->Right = SingleRotateWithLeft(node->Right);
        return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T){
	if(T == NULL){
		T = malloc(sizeof(struct AVLNode));
		T->Element = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}else if(X == T->Element){
		printf("[Error] %d already in the tree!\n", X);
	}else if(X < T->Element){
		T->Left = Insert(X, T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)
			if(X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}else if(X > T->Element){
		T->Right = Insert(X, T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
			if(X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}


void PrintInorder(AVLTree T){
	if(T->Left != NULL)
		PrintInorder(T->Left);
	printf("%d(%d) ", T->Element, T->Height);
	if(T->Right != NULL)
		PrintInorder(T->Right);
}

void DeleteTree(AVLTree T){
	if(T->Left != NULL)
		DeleteTree(T->Left);
	if(T->Right != NULL)
		DeleteTree(T->Right);
	free(T);
}

int main(int argc, char** argv){

	FILE *fp = fopen(argv[1], "r");
	AVLTree myTree = NULL;
	int num;

	if(fp == NULL){
		printf("There is no File : %s\n", argv[1]);
		exit(-1);
	}

	while(fscanf(fp, "%d", &num) != EOF){
		myTree = Insert(num, myTree);
		PrintInorder(myTree);
		printf("\n");
	}
	fclose(fp);
	DeleteTree(myTree);
	return 0;
}
