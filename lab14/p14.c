#include<stdio.h>
#include<stdlib.h>

const int INF = (int)2e9;

typedef struct Node{
	int vertex;
	int dist;
	int prev;
	int visit;
}Node;

typedef struct Graph{
	int size;
	Node* nodes;
	int** matrix;
}Graph;

typedef struct Heap{
	int capacity;
	int size;
	Node* elements;
}Heap;

Graph* createGraph(int size){
	Graph* G = malloc(sizeof(Graph*));
	G->size = size;
	G->nodes = malloc(sizeof(Node) * (G->size + 1));
	G->matrix = malloc(sizeof(int*) * (G->size + 1));
	for(int i = 0; i < G->size + 1; i++){
		//printf("%d", i);
		G->matrix[i] = malloc(sizeof(int) * (G->size + 1));
		G->nodes[i].vertex = i;
		G->nodes[i].dist = INF;
		G->nodes[i].prev = i;
		G->nodes[i].visit = 0;
		for(int j = 0; j < G->size + 1; j++)
			G->matrix[i][j] = 0;
	}
	return G;
}

Heap* createMinHeap(int heap_size){
	Heap* heap = malloc(sizeof(Heap*));
	heap->capacity = heap_size;
	heap->size = 0;
	heap->elements = malloc(sizeof(Node) * heap_size);
	return heap;
}

void insertToMinHeap(Heap* minHeap, Node newNode){
	int i;
	if(minHeap->capacity <= minHeap->size)
		return;
	else{
		for(i = ++minHeap->size; i != 1 && minHeap->elements[i].dist > minHeap->elements[i/2].dist; i /= 2)
			minHeap->elements[i] = minHeap->elements[i/2];
		minHeap->elements[i] = newNode;
	}
}

Node deleteMin(Heap* minHeap){
	Node min_element = minHeap->elements[1];
	Node last_element = minHeap->elements[minHeap->size--];
	int i, child;
	
	for(i = 1; i * 2 <= minHeap->size; i = child){
		child = i *2;
		if(child != minHeap->size && minHeap->elements[child].dist > minHeap->elements[child + 1].dist)
			child++;
		if(last_element.dist > minHeap->elements[child].dist)
			minHeap->elements[i] = minHeap->elements[child];
		else
			break;
	}
	minHeap->elements[i] = last_element;

	return min_element;
}

void printShortestPath(Graph* G){
	Heap* minHeap = createMinHeap(G->size);
	Node tmp;
	int now;

	G->nodes[1].dist = 0;
	insertToMinHeap(minHeap, G->nodes[1]);

	while(minHeap->size != 0){
		tmp = deleteMin(minHeap);
		for(int i = 0; i < G->size + 1; i++){
			if(G->matrix[tmp.vertex][i] !=0){
				if(tmp.dist + G->matrix[tmp.vertex][i] < G->nodes[i].dist){
					G->nodes[i].dist = tmp.dist + G->matrix[tmp.vertex][i];
					G->nodes[i].prev = tmp.vertex;
					G->nodes[i].visit++;
					insertToMinHeap(minHeap, G->nodes[i]);
				}
			}
		}
	}

	for(int i = 2; i < G->size + 1; i++){
		if(G->nodes[i].visit != 0){
			now = i;
			while(G->nodes[now].vertex != 1){
				printf("%d<-", now);
				now = G->nodes[now].prev;
			}
			printf("%d cost: %d\n", now, G->nodes[i].dist);
		}else 
			printf("%d can not be reached.\n", i);
	}
}

int main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	int size;
	fscanf(fi, "%d", &size);

	Graph* G = createGraph(size);

	int node_s, node_d, weight;
	while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF)
		G->matrix[node_s][node_d] = weight;

	printShortestPath(G);
	return 0;
}
