#include "PriorityQueue.h"

PriorityQueue* PQ_Create(int InitialSize) {
	PriorityQueue* PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue)); 
	PQ->Capacity = InitialSize;
	PQ->UsedSize = 0;
	PQ->Nodes = (PQNode*)malloc(sizeof(PQNode)*PQ->Capacity);      // �켱����ť�� ��Ҹ� ��� �迭�� ũ�� ���� -> ���뷮�� ��ȭ�� ���� realloc���� ����

	return PQ;
}

void PQ_Destroy(PriorityQueue* PQ) {
	free(PQ->Nodes);                    // �迭�� �켱���� ť�� ��������ҿ��� ����
	free(PQ);
}

void PQ_Enqueue(PriorityQueue* PQ, PQNode node) {

	int CurrentPosition = PQ->UsedSize;          // ���� ���� index�� +1 = UsedSize
	int ParentPosition = PQ_GetParent(PQ->UsedSize);  


	if (CurrentPosition == PQ->Capacity) {  // �迭�� �뷮�� ����á�� ��
		if (PQ->Capacity == 0) {         // ���뷮�� ó������ 0�϶� 1�� �ٲ�
			PQ->Capacity = 1;
		}

		PQ->Capacity *= 2;               // ���뷮�� 2��� �ø��� �޸�ũ�⸦ �缳���Ѵ�
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes,sizeof(PQNode)* PQ->Capacity);
	}
	PQ->Nodes[CurrentPosition] = node;        // ���ο� ��� ����

	while (CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority) { // ���� �������� ��Ʈ�� �ƴϰ� ���� �������� �����Ͱ��� �θ������Ǻ��� ������ ���� ��ȯ�ϱ�
		PQ_SwapNodes(PQ, CurrentPosition, ParentPosition);
		CurrentPosition = ParentPosition;
		ParentPosition = PQ_GetParent(CurrentPosition);
	}

	PQ->UsedSize++;  
}

void PQ_Dequeue(PriorityQueue* PQ, PQNode* root) {
	int LeftPosition =0;
	int RightPosition =0;
	int ParentPosition =0;

	memcpy(root, &PQ->Nodes[0], sizeof(PQNode));
	memset(&PQ->Nodes[0], 0, sizeof(PQNode));

	PQ->UsedSize--;
	PQ_SwapNodes(PQ, 0, PQ->UsedSize);             // �� ����� ��带 ��ȯ�ϰ� �ֿ��ϴ��� ��带 ��Ʈ�� �ű��

	LeftPosition = PQ_GetLeftChild(0);             // ���� �Ʒ� ���� ������ �Ʒ���带 ����
	RightPosition = LeftPosition + 1;

	while (1) {                                    
		int SelectedChild = 0;

		if (LeftPosition >= PQ->UsedSize) break;      // ���� �Ʒ� ��尡 ���� �� Ż��

		if (RightPosition >= PQ->UsedSize) {          // ���� �Ʒ� ��尡 �ְ� ������ �Ʒ���尡 ���� ��
			SelectedChild = RightPosition;
		}
		else {                                        // ���� ������ �Ʒ� ��� �Ѵ� ���� ��
			if (PQ->Nodes[RightPosition].Priority > PQ->Nodes[LeftPosition].Priority) {     // �θ�� ���� ���� ���ϱ� ���� �� �� �� ���� ���� ��� ������ ���� 
				SelectedChild = LeftPosition;
			}
			else SelectedChild = RightPosition;
		}

		if (PQ->Nodes[ParentPosition].Priority > PQ->Nodes[SelectedChild].Priority) {    // �θ��� ���� �� ũ�� ��� ��ȯ �� ��ȯ ������ ��ȯ���� 
			PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else break;

		LeftPosition = PQ_GetLeftChild(SelectedChild);
		RightPosition = LeftPosition + 1;

	}
}
int PQ_GetParent(int index) {
	return (index % 2 == 1) ? (index / 2) : ((index / 2) - 1);                // �θ�� Ȧ�� �� �� 2�� ���� �� , ¦�� �� �� 2�� ���� �� -1   
}
int PQ_GetLeftChild(int index) {                                              // ���� �ڽ��� �θ� *2 +1
	return index * 2 + 1;
}
void PQ_SwapNodes(PriorityQueue* PQ, int index1, int index2) {
	int CopySize = sizeof(PQNode);
	PQNode* tmp = (PQNode*)malloc(CopySize);

	memcpy(tmp, &PQ->Nodes[index1], CopySize);
	memcpy(&PQ->Nodes[index1] , &PQ->Nodes[index2], CopySize);
	memcpy(&PQ->Nodes[index2], tmp, CopySize);

	free(tmp);
}
int PQ_IsEmpty(PriorityQueue* PQ) {
	if (PQ->UsedSize == 0) {
		return 1;
	 }
	else return 0;
}