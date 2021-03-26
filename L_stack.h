#ifndef L_stack
#define L_stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagNode {
	struct tagNode* NextNode;
	char* data;
}Node;

typedef struct Lstack {
	Node* list;
	Node* top;
}Lstack;

int Is_empty(Lstack* stack);
Node* Top(Lstack* stack);
int Get_size(Lstack* stack);
Node* Pop(Lstack* stack);
void CreateLstack(Lstack** stack);
void DestroyLstack(Lstack* stack);
Node* CreateNode(char* str);
void DestroyNode(Node* DelNode);
void Push(Lstack* stack, Node* node);
Node* Pop(Lstack* stack);

#endif
