#include<stdio.h>
#include<stdlib.h>

typedef struct _DisjointSet {
	int size_maze;
	int *ptr_arr;
} DisjointSets;

void init(DisjointSets* sets, DisjointSets* maze_print, int num) {
	sets->size_maze = num * num;
	maze_print->size_maze = num * num * 2;
	sets->ptr_arr = malloc(sizeof(int) * (sets->size_maze + 1));
	maze_print->ptr_arr = malloc(sizeof(int) * (maze_print->size_maze + 1));
	for(int i = 1; i <= sets->size_maze; i++)
		sets->ptr_arr[i] = 0;
	for(int i = 1; i <= maze_print->size_maze; i++)
		maze_print->ptr_arr[i] = -1;
	maze_print->ptr_arr[num * num] = 0;
}

int find(DisjointSets* sets, int i){
	while(sets->ptr_arr[i] > 0)
		i = sets->ptr_arr[i];
	return i;
}

void union_(DisjointSets* sets, int i, int j){
	int p1 = find(sets, i);
	int p2 = find(sets, j);

	if(sets->ptr_arr[p1] > sets->ptr_arr[p2])
		sets->ptr_arr[p1] = p2;
	else {
		if(sets->ptr_arr[p1] == sets->ptr_arr[p2])
			sets->ptr_arr[p1]--;
		sets->ptr_arr[p2] = p1;
	}
}
void createMaze(DisjointSets* sets, DisjointSets* maze_print, int num){
	int randNum = 0;
	while(find(sets, 1) != find(sets, sets->size_maze)){
		randNum = rand() % (maze_print->size_maze);
		if(randNum <= sets->size_maze) {
			if((randNum % num) != 0 && find(sets, randNum) != find(sets, randNum+1)) {
				union_(sets, randNum, randNum + 1);
				maze_print->ptr_arr[randNum] = 0;
			}
		} else if((randNum + num) <= maze_print->size_maze && find(sets, (randNum - sets->size_maze)) != find(sets, (randNum - sets->size_maze + num))) {
			union_(sets, (randNum - sets->size_maze), (randNum - sets->size_maze + num));
			maze_print->ptr_arr[randNum] = 0;			
		}
	}
}
void printMaze(DisjointSets* sets, int num){
	for(int j = 0; j < num; j++)
		printf(" -");
	printf("\n");
	for(int i = 0; i < num; i++){
		if(i != 0)
			printf("|");
		else
			printf(" ");
		for(int j = 1; j <= num; j++){
			if(sets->ptr_arr[i * num + j] == -1)
				printf(" |");
			else
				printf("  ");
		}
		printf("\n");
		for(int j = 1; j <= num; j++){
			if(sets->ptr_arr[(num * num + (i * num) + j)] == -1)
				printf(" -");
			else printf("  ");
		}
		printf("\n");
	}
}
void freeMaze(DisjointSets* sets, DisjointSets* maze_print){
	free(sets->ptr_arr);
	free(maze_print->ptr_arr);
	free(sets);
	free(maze_print);
}

int main(int argc, char* argv[]) {
	int num, i;
	FILE *fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &num);

	DisjointSets * sets, *maze_print;
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));

	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	freeMaze(sets, maze_print);

	return 0;
}
