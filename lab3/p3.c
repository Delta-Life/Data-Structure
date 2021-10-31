#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
	ElementType element;
	Position next;
};

List MakeEmpty(){
	List L;
	L = (List)malloc(sizeof(struct Node));
	L->element=-1;
	L->next = NULL;
	return L;
}

int IsEmpty(List L){
	return L->next == NULL;
}

int IsLast(Position P,  List L){
	return P->next == NULL;
}

Position Find(ElementType X, List L){
	Position P;
	P = L;
	while(P != NULL && P->element != X)
		P = P->next;
	return P;
}

Position FindPrevious(ElementType X,  List L){
	Position P;
	P = L;
	while(P->next != NULL && P->next->element != X)
		P = P->next;
	return P;
}

void Insert(ElementType X, List L, Position P){
	Position tmp;
	tmp = (Position)malloc(sizeof(struct Node));
	if(P == NULL){
		printf("Insertion(%d) Failed : cannot find the location to be inserted\n", X);
		free(tmp);
	}
	else{
		tmp->element = X;
		tmp->next = P->next;
		P->next = tmp;
	}
}

void PrintList(List L){
	if(L->next==NULL){
		printf("List is empty. There is nothing to print.\n");
	}else{
		L = L->next;
		while(L != NULL){
			printf("key:%d\t",L->element);
			L = L->next;
		}
		printf("\n");
	}
}

void Delete(ElementType X,  List L){
	Position P, tmp;
	P = FindPrevious(X, L);
	if(IsLast(P, L)){
		printf("Deletion failed : element %d is not in the list\n", X);
	}
	else{
		tmp = P->next;
		P->next = tmp->next;
		free(tmp);
	}
}

void DeleteList(List L){
	Position P,tmp;
	P = L->next;
	L->next = NULL;
	while(P != NULL){
		tmp = P->next;
		free(P);
		P = tmp;
	}
	free(L);
}

int main(int argc, char **argv){
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp;
	if(argc== 1){
		printf("No input file\n");
		return 0;
	}
	else
		input = fopen(argv[1], "r");
	header = MakeEmpty();
	while(1) {
		command = fgetc(input);
		if(feof(input))
			break;
		switch(command) {
			case 'i':
				fscanf(input, " %d %d", &key1, &key2);
				tmp= Find(key2, header);
				Insert(key1, header, tmp);
				break;
			case 'd':
				fscanf(input, "%d", &key1);
				Delete(key1, header);
				break;
			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header);
				if(IsLast(tmp, header))
					printf("Could not find %d in the list\n", key1);
				else {
					if(tmp->element>0)
						printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
					else
						printf("Key of the previous node of %d is header.\n", key1);
				}
				break;
			case 'p':
				PrintList(header);
				break;
			default:
				break;
		}
	}
	DeleteList(header); ///free all memory used by linked list
	fclose(input);
	return 0;
}
