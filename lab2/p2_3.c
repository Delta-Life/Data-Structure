#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* args[]){

	char** name;
	int num = atoi(args[1]);

	printf("enter %d name:\n", num);

	name = (char**)malloc(sizeof(char*) * num);
	for(int i = 0; i < num; i++){
		name[i] = (char*)malloc(sizeof(char) * 31);
		scanf("%s", name[i]);
	}

	printf("the names you entered:\n");

	for(int i = 0; i < num; i++){
		printf("%s\n", name[i]);
	}

	for(int i = 0; i < argc - 1; i++){
		free(name[i]);
	}
	free(name);

}
