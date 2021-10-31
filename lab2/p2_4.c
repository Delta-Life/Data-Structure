#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define INT_MAX 2147483647

bool isZero(int);
bool equal(int, int);
int successor(int);
int add(int, int);
int subtract(int, int);

int main(int argc, char** args){

	int x = atoi(args[1]); //atoi: charatersto int
	int y = atoi(args[2]);

	/*
	if(atol(args[1]) > INT_MAX | atol(args[2]) > INT_MAX){
		printf("args should be smaller than %d.\n", INT_MAX);
		return 0;
	}
	*/
	
	printf("Is %d zero? %s\n", x, isZero(x) ? "True" : "False");
	printf("Is %d zero? %s\n", y, isZero(y) ? "True" : "False");
	printf("Does %d equal %d? %s\n", x, y, equal(x, y) ? "True": "False");
	printf("%d's next number is %d\n", x, successor(x));
	printf("%d's next number is %d\n", y, successor(y));
	printf("%d + %d = %d\n", x, y, add(x, y));
	printf("%d - %d = %d\n", x, y, subtract(x, y));

}

bool isZero(int num){
	if(num == 0)
		return 1;
	return 0;
}

bool equal(int num1, int num2){
	if(num1 == num2)
		return 1;
	return 0;
}

int successor(int num){
	if(num < INT_MAX)
		return ++num;
	return num;
}

int add(int num1, int num2){
	if((long)num1 + num2 < INT_MAX)
		return num1 + num2;
	return INT_MAX;
}

int subtract(int num1, int num2){
	if(num1 > num2)
		return num1-num2;
	return 0;
}
