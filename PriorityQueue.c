#include "PriorityQueue.h"

PriorityQueue* PQ_Create(int InitialSize) {
	PriorityQueue* PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue)); 
	PQ->Capacity = InitialSize;
	PQ->UsedSize = 0;
	PQ->Nodes = (PQNode*)malloc(sizeof(PQNode)*PQ->Capacity);      // 우선순위큐의 요소를 담는 배열의 크기 선언 -> 수용량의 변화에 따라 realloc으로 조절

	return PQ;
}

void PQ_Destroy(PriorityQueue* PQ) {
	free(PQ->Nodes);                    // 배열과 우선순위 큐를 자유저장소에서 해제
	free(PQ);
}

void PQ_Enqueue(PriorityQueue* PQ, PQNode node) {

	int CurrentPosition = PQ->UsedSize;          // 현재 지닌 index의 +1 = UsedSize
	int ParentPosition = PQ_GetParent(PQ->UsedSize);  


	if (CurrentPosition == PQ->Capacity) {  // 배열의 용량이 가득찼을 떄
		if (PQ->Capacity == 0) {         // 수용량이 처음부터 0일때 1로 바꿈
			PQ->Capacity = 1;
		}

		PQ->Capacity *= 2;               // 수용량을 2배로 늘리고 메모리크기를 재설정한다
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes,sizeof(PQNode)* PQ->Capacity);
	}
	PQ->Nodes[CurrentPosition] = node;        // 새로운 노드 삽입

	while (CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority) { // 현재 포지션이 루트가 아니고 현재 포지션의 데이터값이 부모포지션보다 작으면 값을 교환하기
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
	PQ_SwapNodes(PQ, 0, PQ->UsedSize);             // 맨 꼭대기 노드를 반환하고 최우하단의 노드를 루트로 옮기기

	LeftPosition = PQ_GetLeftChild(0);             // 왼쪽 아래 노드와 오른쪽 아래노드를 지정
	RightPosition = LeftPosition + 1;

	while (1) {                                    
		int SelectedChild = 0;

		if (LeftPosition >= PQ->UsedSize) break;      // 왼쪽 아래 노드가 없을 때 탈출

		if (RightPosition >= PQ->UsedSize) {          // 왼쪽 아래 노드가 있고 오른쪽 아래노드가 없을 때
			SelectedChild = RightPosition;
		}
		else {                                        // 왼쪽 오른쪽 아래 노드 둘다 있을 때
			if (PQ->Nodes[RightPosition].Priority > PQ->Nodes[LeftPosition].Priority) {     // 부모와 비교할 값을 정하기 위해 둘 중 더 작은 값을 골라 변수에 저장 
				SelectedChild = LeftPosition;
			}
			else SelectedChild = RightPosition;
		}

		if (PQ->Nodes[ParentPosition].Priority > PQ->Nodes[SelectedChild].Priority) {    // 부모의 값이 더 크면 노드 교환 후 순환 작으면 순환종료 
			PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else break;

		LeftPosition = PQ_GetLeftChild(SelectedChild);
		RightPosition = LeftPosition + 1;

	}
}
int PQ_GetParent(int index) {
	return (index % 2 == 1) ? (index / 2) : ((index / 2) - 1);                // 부모는 홀수 일 때 2로 나눈 몪 , 짝수 일 때 2로 나눈 몪 -1   
}
int PQ_GetLeftChild(int index) {                                              // 왼쪽 자식은 부모 *2 +1
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