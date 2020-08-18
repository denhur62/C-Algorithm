#include<stdlib.h>
#include<stdio.h>
typedef struct Node {
	struct Node *next;
	int data;
} Node; 
typedef struct List {
	struct Node *head;
} List; 
void InsertFirst(List *list, int data) { 
	Node *node = (Node *)malloc(sizeof(Node)); 
	node->data = data; 
	node->next = list->head; 
	list->head = node; 
}
void Print_C(Node *node) {
	while (node) {
		printf("%d ", node->data); 
		node = node->next; 
	}
}
void Free_C(Node *node) {
	if (node) {
		Free_C(node->next);
		free(node); 
	}
}
int main() {
	List list = { NULL };
	int n, data, i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &data);
		InsertFirst(&list, data);
	}
	Print_C(list.head);
	Free_C(list.head);
	return 0;
}
