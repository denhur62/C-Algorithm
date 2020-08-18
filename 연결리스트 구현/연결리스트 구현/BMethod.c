#include<stdlib.h>
#include<stdio.h>
typedef struct Node {
	struct Node *next;
	int data;
}Node;
void InsertFirst(Node **phead, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = *phead;
	*phead = node;
}
void Print_B(Node *node) {
	while (node) {
		printf("%d ", node->data);
		node = node->next;
	}
}
void Free_B(Node *node) {
	if (node) {
		Free_B(node->next);
		free(node);
	}
}
int main() {
	Node *head = NULL;
	int n, data, i;
	scanf("%d",&n);
	for (i = 0; i < n; i++) {
		scanf("%d",&data);
		InsertFirst(&head, data);
	}
	Print_B(head);
	Free_B(head);

}