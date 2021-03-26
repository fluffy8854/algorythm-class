#include "L_stack.h"


int Is_empty(Lstack* stack)
{
	return stack->list == NULL;
}

Node* Top(Lstack* stack)
{
	return stack->top;
}

int Get_size(Lstack* stack)
{
	int Count = 0;
	Node* Current = stack->list;
	while (Current != NULL)
	{
		Current = Current->data;
		Count++;
	}
	return Count;
}
Node* Pop(Lstack* stack);

void CreateLstack(Lstack** stack)
{
	*stack = (Lstack*)malloc(sizeof(Lstack));
	(*stack)->top = NULL;
	(*stack)->list = NULL;
}

void DestroyLstack(Lstack* stack)
{
	while (!Is_empty(stack)) {
		Node* poped = Pop(stack);
		DestroyNode(poped);
	}
	free(stack);
}

Node* CreateNode(char* str)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->data = (char*)malloc(sizeof(strlen(str)+1));
	strcpy(NewNode->data, str);
	NewNode->NextNode = NULL;
	return NewNode;
}

void DestroyNode(Node* DelNode) {
	free(DelNode->data);
	free(DelNode);
}

void Push(Lstack* stack, Node* node)
{
	if (stack->list == NULL)
	{
		stack->list = node;
	}
	else{
		Node* oldTop = stack->list;
		while (oldTop->NextNode != NULL) {
			oldTop = oldTop->NextNode;
		}
		oldTop->NextNode = node;
	}
	stack->top = node;
}

Node* Pop(Lstack* stack)
{
	Node* TopNode = stack->top;

	if (stack->top == stack->list)
	{
		stack->list = NULL;
		stack->top = NULL;
	}
	else
	{
		Node* CurrentTop = stack->list;
		while (CurrentTop != NULL && CurrentTop->NextNode != stack->top)
		{
			CurrentTop = CurrentTop->NextNode;
		}
		
		stack->top = CurrentTop;
		CurrentTop->NextNode = NULL;
	}
	return TopNode;
}