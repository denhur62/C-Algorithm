#include<stdlib.h>
#include<stdio.h>
typedef struct node {
	struct node *next;
	int data;
}node;
node *insertfirst(node *head, int data) {
	node *node = (node*)malloc(sizeof(node));
	node->data = data;
	node->next = head;
	return node;
}
void print_a(node *node) {
	while (node) {
		printf("%d ",node->data);
		node = node->next;
	}
}
void free_a(node *node) {
	if (node) {
		free(node->next);
		free(node);
	}
}
int main() {
	node *node = NULL;
	int n, data, i;
	scanf("%d",&n);

	for (i = 0; i < n; i++) {
		scanf("%d",&data);
		node=insertfirst(node, data);

	}
	print_a(node);
	free_b(node);
}
