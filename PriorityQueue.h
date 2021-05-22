#ifndef PRIORITYQUEUE_H
#define PRIORITIQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int  PriorityType;

typedef struct tagePQNode {
	PriorityType Priority;
	void* data;
}PQNode;

typedef struct tagPriorityQueue {
	PQNode* Nodes;
	int Capacity;
	int UsedSize;
}PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize);
void PQ_Destroy(PriorityQueue* PQ);
void PQ_Enqueue(PriorityQueue* PQ, PQNode data);
void PQ_Dequeue(PriorityQueue* PQ, PQNode* root);
int PQ_GetParent(int index);
int PQ_GetLeftChild(int index);
void PQ_SwapNodes(PriorityQueue* PQ, int index1, int index2);
int PQ_IsEmpty(PriorityQueue* PQ);


#endif