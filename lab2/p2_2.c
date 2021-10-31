#include<stdio.h>

void main(int argc, char** args){

	char name[31];

	printf("enter tour name :");
	//gets(name, stdin);
	scanf("%[^\n]s", name);
	printf("your name is %s\n", name);

}
