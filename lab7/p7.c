#include<stdio.h>
#include<stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
	int Capacity;
	int Size;
	int* Element;
};

Heap CreateHeap(int heapSize){
	int i;
	Heap heap = malloc(sizeof(Heap));
	heap->Element = malloc(sizeof(int) * (heapSize +1));
	for(i = 0; i <= heapSize; i++)
		heap->Element[i] = -1;
	heap->Capacity = heapSize;
	heap->Size = 0;
}

int Find(Heap heap, int value){
        int i, flag = 0;
        for(i = 1; i <= heap->Size; i++){
                if(heap->Element[i]==value)
                        flag++;
        }
        return flag;
}

void Insert(Heap heap, int value){
	int i;
	if(heap->Capacity <= heap->Size){
		printf("Insertion Error : Max Heap is full.\n");
		return;
	}else if(Find(heap, value)){
		printf("%d is already in the heap.\n", value);
	}else{
		for(i = ++heap->Size; i != 1 && value > heap->Element[i/2]; i /= 2){
			heap->Element[i] = heap->Element[i/2];
		}
		heap->Element[i] = value;
		printf("insert %d\n", value);
	}
}

int DeleteMax(Heap heap){
	if(heap->Size == 0){
		printf("Deletion Error : Max Heap is empty!\n");
		return 0;
	}else{
		int i, child;
		int maxElement, lastElement;
	
		maxElement = heap->Element[1];
		lastElement = heap->Element[heap->Size--];

		for(i = 1; i * 2 <= heap->Size; i = child){
			child = i * 2;
			if(child != heap->Size && heap->Element[child] < heap->Element[child + 1])
				child++;
			if(lastElement < heap->Element[child])
				heap->Element[i] = heap->Element[child];
			else
				break;
		}
		heap->Element[i] = lastElement;
		heap->Element[heap->Size + 1] = -1;
		printf("Max Element : %d deleted\n", maxElement);
		return maxElement;
	}
}

void PrintHeap(Heap heap){
	int index, i;
	int count = 0;

	if (heap->Size == 0){
		printf("Print Error : Max heap is empty!\n");
		return;
	}
	for(index = 1; index <= heap->Size; index++){
		printf("%d ", heap->Element[index]);
	}
	printf("\n");
}

void main(int argc, char*argv[])
{
	FILE * fi = fopen(argv[1], "r");
	char cv;
	Heap maxHeap;
	int heapSize, key;
	while(!feof(fi)){
		fscanf(fi, "%c", &cv);
		switch(cv){
		case 'n':
			fscanf(fi, "%d", &heapSize);
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fi, "%d", &key);
			Insert(maxHeap, key);
			break;
		case 'd' :
			DeleteMax(maxHeap);
			break;
		case 'p':
			PrintHeap(maxHeap);
			break;
		case 'f':
			fscanf(fi, "%d", &key);
			if(Find(maxHeap, key))
				printf("%d is in the heap.\n", key);
			else
				printf("%d is not in the heap.\n", key);
			break;
		}
	}
}

