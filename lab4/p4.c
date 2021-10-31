#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

int IsEmpty(Stack* S){
	if(S->top < 0)
		return 1;
	else
		return 0;
}

int IsFull(Stack* S){
	if(S->top >= (S->max_stack_size - 1))
		return 1;
	else
		return 0;
}


Stack* CreateStack (int max){
	Stack* tmpStack;
       	tmpStack = malloc(sizeof(Stack));
	tmpStack->top = -1;
	tmpStack->max_stack_size = max;
	tmpStack->key = malloc(sizeof(int) * tmpStack->max_stack_size);
	return tmpStack;
}

void Push(Stack* S, int X){
	if(IsFull(S)){
		printf("\nError, Stack is fully pushed.\n");
		exit(0);
	}else{
		S->key[++S->top] = X;
	}
}

int Pop(Stack* S){
	if(IsEmpty(S)){
		printf("\nError, Stack is fully poped\n");
		exit(0);
	}else{
		return S->key[S->top--];
	}
}	

int Top(Stack* S){
	if(IsEmpty(S)){
		printf("\nError, Stack is empty\n");
		return -31337;
	}else{
		return S->key[S->top];
	}
}

void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}

void Postfix(Stack* S, char input_str){
	int tmp1, tmp2;
	switch(input_str){
		case '+':
			tmp1 = Pop(S);
			tmp2 = Pop(S);
			Push(S, tmp2 + tmp1);
			break;
		case '-':
			tmp1 = Pop(S);
                        tmp2 = Pop(S);
			Push(S, tmp2 - tmp1);
			break;
		case '*':
			tmp1 = Pop(S);
                        tmp2 = Pop(S);
			Push(S, tmp2 * tmp1);
			break;
		case '/':
			tmp1 = Pop(S);
                        tmp2 = Pop(S);
			Push(S, tmp2 / tmp1);
			break;
		case '%':
			tmp1 = Pop(S);
                        tmp2 = Pop(S);
			Push(S, tmp2 % tmp1);
			break;
		default :
			Push(S, input_str - '0');
			break;
	}
}

int main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");
	Stack* stack;
	char input_str[101];
	int max, i, result;
	fgets(input_str, 101, fi);
	stack = CreateStack(10);

	printf("Top numbers :");
	for(i = 0; i < strlen(input_str) && input_str[i] != '#'; i++){
		Postfix(stack, input_str[i]);
		printf("%d ", Top(stack));
	}
	result = Pop(stack);
	if(stack->top == -1){
		printf("\nevaluation result : %d\n", result);
	}else{
		printf("\nevaluation result : %d\nError, need more operators.\n", result);
	}
	fclose(fi);
	DeleteStack(stack);
}
