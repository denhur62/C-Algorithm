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
void addNode(Node *node,int index) {
	Node *newNode = createNode(index);
	Node *Runner = node;
	if (node == NULL)
		node = newNode;
	else {
		while (Runner->next != NULL) {
			Runner = Runner->next;
		}
		Runner->next = newNode;
	}

}
int findLength(Node *node) {
	Node *Runner = node;
	int cnt = 0;
	while (Runner != NULL) {
		cnt++;
		Runner = Runner->next;
	}
	return cnt;
}
Node* merge(Node *L1, Node *L2) {
	Node *newNode = NULL;
	if (L1 == NULL)
		return L2;
	if (L2 == NULL)
		return L1;
	if (L1->data < L2->data) {
		newNode = L1;
		newNode->next = merge(L1->next, L2);
	}
	else {
		newNode = L2;
		newNode->next = merge(L1, L2->next);
	}
	return newNode;
}
Lists partition(Node *node,int key) {
	
	Node *L1 = node;
	Node *L2 = node;
	Node *Runner = node, *before = NULL;
	int index = 0;
	while (index < key / 2) {
		before = Runner;
		Runner = Runner->next;
		index++;
	}
	L2 = Runner;
	before->next = NULL;
	Lists list = { L1, L2 };
	return list;
}
void mergeSort(Node **node) {
	int key = findLength(*node);
	if (key < 2)
		return;
	Lists list = partition(*node,key);
	mergeSort(&list.L1);
	mergeSort(&list.L2);
	*node=merge(list.L1, list.L2);

}

void printNode(Node *node) {
	Node *Runner = node;
	while (Runner!=NULL) {
		printf("%d ",Runner->data);
		Runner = Runner->next;
	}
	printf("\n");
}
int main() {
	Node *node = NULL;
	int a,index;
	scanf("%d",&a);
	for (int i = 0; i < a; i++) {
		scanf("%d",&index);
		addNode(&node,index);
	}

	mergeSort(&node,a);
	printNode(node);
}