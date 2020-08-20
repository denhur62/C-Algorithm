#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node {
	struct Node *left;
	struct Node *right;
	int leftdata;
	int data;
	int rightdata;
}Node;

Node* MakeNode(int data,int left,int right) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->leftdata = left;
	node->data = data;
	node->rightdata = right;
	node->left = NULL;
	node->right = NULL;
	return node;
}
Node *LinkNode(Node *node[],int a) {
	int i, j;
	Node *root = node[0];

	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++ &&j!=i) {
			if (node[i]->leftdata == node[j]->data &&node[j]->data!=0) {
				node[i]->left = node[j];
			}
			if (node[i]->rightdata == node[j]->data &&node[j]->data != 0) {
				node[i]->right = node[j];
			}
			if (node[i]->left == root || node[i]->right == root)
				root = node[i];
		}
	}

	return root;
}
void PrintTree(Node *node,char *ch) {
	int chlength = strlen(ch);
	if (node == NULL)
		return;
	else {
		printf(" %d",node->data);
		for (int i = 0; i < chlength; i++) {
			if (ch[i] == 'R') {
				node = node->right;
				printf(" %d",node->data);
			}
			else {
				node = node->left;
				printf(" %d", node->data);
			}
		}
		printf("\n");
	}
}

int main() {
	int a, b,center,left,right,i;
	char ch[100] = { NULL };
	Node **node = NULL, *tree = NULL;
	scanf("%d",&a);

	node = (Node**)malloc(sizeof(Node*)*a);
	for (i = 0; i < a; i++) {
		scanf("%d %d %d",&center,&left,&right);
		node[i]=MakeNode(center, left, right);
	}

	tree=LinkNode(node,a);

	scanf("%d",&b);
	getchar();
	for (int i = 0; i < b; i++) {
		scanf("%s",ch);
		PrintTree(tree, ch);
	}
}	