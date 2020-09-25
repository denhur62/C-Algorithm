#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	struct Node* next;
	int data;
} Node;

typedef struct Lists {
	Node* L1;
	Node* L2;
} Lists;

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = data;

	return newNode;
}

int findLength(Node *L) {

	int size = 0;

	Node *horse = L;
	while (horse != NULL) {
		horse = horse->next;
		size++;
	}

	return size;
}

void addNode(Node* L, int data) {

	Node* newNode = createNode(data);
	Node* horse = L;

	if (horse == NULL)
		horse = newNode;

	else {
		while (horse->next != NULL)
			horse = horse->next;

		horse->next = newNode;
	}
}

Node* merge(Node* L1, Node* L2) {

	Node* mergedList = NULL;

	if (L1 == NULL)
		return L2;
	if (L2 == NULL)
		return L1;

	if (L1->data < L2->data) {
		mergedList = L1;
		mergedList->next = merge(L1->next, L2);
	}
	else {
		mergedList = L2;
		mergedList->next = merge(L1, L2->next);
	}

	return mergedList;
}

Lists mg_partition(Node* L, int k) {

	Node* L1;
	Node* L2;

	Node* horse = L;
	Node* before = L;

	int index = 0;
	while (index < k / 2) {
		before = horse;
		horse = horse->next;
		index++;
	}

	L1 = L;
	L2 = horse;
	before->next = NULL;

	Lists lists = { L1, L2 };
	return lists;
}

void mergeSort(Node** L) {

	int k = findLength(*L);
	if (k < 2)
		return;

	Lists lists = mg_partition(*L, k);
	mergeSort(&lists.L1);
	mergeSort(&lists.L2);
	*L = merge(lists.L1, lists.L2);
}

void printList(Node* L) {

	Node* horse = L;

	while (horse != NULL) {
		printf(" %d", horse->data);
		horse = horse->next;
	}
	printf("\n");
}

int main() {

	Node *list = NULL;

	int N;
	scanf("%d", &N);

	int num;
	for (int i = 0; i < N; ++i) {
		scanf("%d", &num);
		addNode(&list, num);
	}

	mergeSort(&list);

	printList(list);
}
