#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	int data;
	struct Node * next;
}Node;
typedef struct List {
	struct Node * head;
}List;
Node * getNode(int nData) {
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = nData;
	newNode->next = NULL;
	return newNode;
}
void addLast(List *L, int data) {
	Node * cur = L->head;
	Node * node = getNode(data);
	if (L->head == NULL) {
		L->head = node;
		return;
	}
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = node;
	return;

}
void printList(List*L) {
	Node*cur = L->head;
	while (cur != NULL)
	{
		printf(" %d", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
int sizeList(List*L) {//리스트 사이즈 구하기 함수..
	Node*cur = L->head;
	int cnt = 0;
	while (cur != NULL) {
		cnt++;
		cur = cur->next;
	}
	return cnt;
}
List partition(List* L, int k) {//K=5/2 = 2
	int cnt = 0;
	Node * tmp;
	Node * cur = L->head;
	List L2;
	while (cnt != k) {
		cnt++;
		tmp = cur;
		cur = cur->next;
	}
	tmp->next = NULL;
	L2.head = cur;
	return L2;
}

void print(Node*head) {
	Node*cur = head;
	while (cur != NULL) {
		printf(" %d", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
Node* merge(List*L1, List*L2) {
	List L;//empty
	Node*H = NULL;
	Node*Runner = NULL;
	Node*cur = H;
	Node*cur1 = L1->head;
	Node*cur2 = L2->head;
	while (cur1 != NULL && cur2 != NULL) {
		if (cur1->data < cur2->data) {
			if (H == NULL) {
				H = cur1;
				cur = cur1;
				cur1 = cur1->next;
				cur->next = NULL;
			}
			else {
				cur->next = cur1;
				cur1 = cur1->next;
				cur = cur->next;
				cur->next = NULL;
			}
		}
		else {
			if (H == NULL) {
				H = cur2;
				cur = cur2;
				cur2 = cur2->next;
				cur->next = NULL;
			}
			else {
				cur->next = cur2;
				cur2 = cur2->next;
				cur = cur->next;
				cur->next = NULL;
			}
		}
	}
	while (cur1 != NULL) {
		cur->next = cur1;
		cur1 = cur1->next;
		cur = cur->next;
		cur->next = NULL;
	}

	while (cur2 != NULL) {
		cur->next = cur2;
		cur2 = cur2->next;
		cur = cur->next;
		cur->next = NULL;
	}
	Runner = H;
	while (Runner != NULL) {
		printf("%d ",Runner->data);
		Runner = Runner->next;
	}
	printf("\n");
	return H;
}
void mergeSort(List * L) {
	List L2, L1;
	Node*h;
	if (sizeList(L) <= 1)
		return;
	L2 = partition(L, sizeList(L) / 2);//partitiON
	L1 = *L;
	mergeSort(&L1);//L1에 대한 재귀호출
	mergeSort(&L2);//L2에 대한 재귀호출	

	h = merge(&L1, &L2);
	L->head = h;
}
int main() {
	int n;
	int data;
	List L;
	L.head = NULL;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		addLast(&L, data);
	}

	mergeSort(&L);
	printList(&L);
}