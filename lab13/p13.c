#include<stdio.h>
#include<stdlib.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int size;
	int* key;
	int front;
	int rear;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int X){
	Graph G = malloc(sizeof(Graph));
	G->size = X;
	G->node = malloc(sizeof(int) * G->size);
	G->matrix = malloc(sizeof(int*) * G->size);
	for(int i = 0; i < G->size; i++){
		G->matrix[i] = malloc(sizeof(int) * G->size);
		G->node[i] = 0;
		for(int j = 0; j < G->size; j++)
			G->matrix[i][j] = 0;
	}
	return G;
}

void InsertEdge(Graph G, int nodeS, int nodeD){
	int s = 0;
	int d = 0;
	while(G->node[s] != nodeS)
		s++;
	while(G->node[d] != nodeD)
		d++;
	G->matrix[s][d] = 1;
}

Queue CreateQueue(int X){
	Queue Q = malloc(sizeof(Queue));
	Q->size = X;
	Q->key = malloc(sizeof(int) * Q->size);
	Q->front = 0;
	Q->rear = -1;
	return Q;

}

void Enqueue(Queue Q, int item){
	if(Q->rear + 1 >= Q->size)
		printf("queue is full");
	else
		Q->key[++Q->rear] = item;
}

int Dequeue(Queue Q){
	if(Q->front > Q->rear)
		printf("queue is empty");
	else
		return Q->key[Q->front++];
	return -1;
}

int IsEmpty(Queue Q){
	if(Q->front > Q->rear)
		return 1;
	else
		return 0;
}

void Topsort(Graph G){
	int indegree[G->size];
	Queue Q = CreateQueue(G->size);

	for(int i = 0; i < G->size; i++)
                indegree[i] = 0;

	for(int i = 0; i < G->size; i++){
		for(int j = 0; j < G->size; j++)
			indegree[j] += G->matrix[i][j];
	}
	
	while(Q->front <= G->size - 1){
		for(int i = 0; i < G->size; i++){
			if(indegree[i] == 0){
				indegree[i] = -1;
				Enqueue(Q, i);
			}
		}
		while(!IsEmpty(Q)){
			int Dtmp = Dequeue(Q);
			printf("%d ", G->node[Dtmp]);
			for(int i = 0; i < G->size; i++)
				indegree[i] -= G->matrix[Dtmp][i];
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]){
	FILE * fi = fopen(argv[1], "r");
	int X, node_s, node_d;

	fscanf(fi, "%d", &X);
	Graph G = CreateGraph(X);

	for(int i = 0; i < X; i++)
		fscanf(fi, "%d", &G->node[i]);

	while(fscanf(fi, "%d %d", &node_s, &node_d) != EOF)
		InsertEdge(G, node_s, node_d);

	Topsort(G);
}
