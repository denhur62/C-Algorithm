#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define NoSuchKey INT_MIN
// NoSuchKey�� ���� ����

typedef enum { false, true } bool;
typedef struct Node {
	struct Node* parent;
	struct Node* LChild;
	struct Node* RChild;
	int height;
	int key;
} Node;

// Ʈ���� ��Ʈ ��� ���� ���� 
Node* root;

bool isExternal(Node* w) {
	if (w->LChild == NULL && w->RChild == NULL)
		return true;
	else
		return false;
}

bool isInternal(Node* w) {
	if (w->LChild != NULL || w->RChild != NULL)
		return true;
	else
		return false;
}

Node* getNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->parent = NULL;
	newNode->LChild = NULL;
	newNode->RChild = NULL;

	return newNode;
}

void expandExternal(Node* z) {

	Node* l = getNode();
	Node* r = getNode();

	l->LChild = NULL; l->RChild = NULL; l->parent = z; l->height = 0;
	r->LChild = NULL; r->RChild = NULL; r->parent = z; r->height = 0;

	z->LChild = l;
	z->RChild = r;
	z->height = 1;
}

Node* sibling(Node *node) {
	// ���� ó�� : ��Ʈ ����� ��� NULL�� ��ȯ 
	if (node->parent == NULL)
		return NULL;

	if (node->parent->LChild == node)
		return node->parent->RChild;
	else
		return node->parent->LChild;
}

Node* treeSearch(Node *node, int key) {

	Node *horse = node;

	// ���� ó�� : �ܺγ���� ��� �ٷ� ��ȯ 
	if (isExternal(horse))
		return horse;

	if (horse->key < key)
		return treeSearch(horse->RChild, key);
	else if (horse->key > key)
		return treeSearch(horse->LChild, key);
	else
		return horse;
}

// ����� ���̸� Ȯ���ϴ� �Լ� 
bool updateHeight(Node *w) {

	Node *l = w->LChild;
	Node *r = w->RChild;

	int h;
	if (l->height > r->height)
		h = l->height + 1;
	else
		h = r->height + 1;

	if (h != w->height) {
		w->height = h;
		return true;
	}
	else
		return false;
}

// �뷱���� �ȸ´� ��� false ��ȯ
bool isBalanced(Node *w) {
	int diff = w->LChild->height - w->RChild->height;
	if (diff > -2 && diff < 2)
		return true;
	return false;
}

Node* restructure(Node *x, Node *y, Node *z) {

	int xKey = x->key;
	int yKey = y->key;
	int zKey = z->key;

	Node *a, *b, *c;
	Node *T0, *T1, *T2, *T3;

	// 4������ ���� ���� ����
	// RR 
	if (zKey < yKey && yKey < xKey) {
		a = z;
		b = y;
		c = x;
		T0 = a->LChild;
		T1 = b->LChild;
		T2 = c->LChild;
		T3 = c->RChild;
	}
	// LL
	else if (xKey < yKey && yKey < zKey) {
		a = x;
		b = y;
		c = z;
		T0 = a->LChild;
		T1 = a->RChild;
		T2 = b->RChild;
		T3 = c->RChild;
	}
	// RL
	else if (zKey < xKey && xKey < yKey) {
		a = z;
		b = x;
		c = y;
		T0 = a->LChild;
		T1 = b->LChild;
		T2 = b->RChild;
		T3 = c->RChild;
	}
	// LR
	else {
		a = y;
		b = x;
		c = z;
		T0 = a->LChild;
		T1 = b->LChild;
		T2 = b->RChild;
		T3 = c->RChild;
	}

	// ���� ó�� : z�� ��Ʈ ����� ��� 
	if (z->parent == NULL) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->LChild == z) {
		z->parent->LChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->RChild == z) {
		z->parent->RChild = b;
		b->parent = z->parent;
	}

	a->LChild = T0;
	T0->parent = a;
	a->RChild = T1;
	T1->parent = a;
	updateHeight(a);

	c->LChild = T2;
	T2->parent = c;
	c->RChild = T3;
	T3->parent = c;
	updateHeight(c);

	b->LChild = a;
	a->parent = b;
	b->RChild = c;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(Node* w) {

	Node *x, *y, *z;

	w->LChild->height = 0;
	w->RChild->height = 0;
	w->height = 1;

	// ���� ó�� : ��Ʈ ����� ��� ���� 
	if (w->parent == NULL)
		return;

	z = w->parent;

	// �θ� ���� �ö󰡸� �뷱�� Ȯ�� 
	while (updateHeight(z) && isBalanced(z)) {
		// ���� ó�� : z�� ��Ʈ�� ��� ���� 
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	// ���� ó�� : �뷱�� �̻��� ���� �� ���� 
	if (isBalanced(z))
		return;

	if (z->LChild->height > z->RChild->height)
		y = z->LChild;
	else
		y = z->RChild;

	if (y->LChild->height > y->RChild->height)
		x = y->LChild;
	else
		x = y->RChild;

	// ���� 
	restructure(x, y, z);
	return;
}

// Ʈ�� Ž�� �Լ�
void insertItem(Node* w, int key) {

	Node *newNode = treeSearch(w, key);

	// ���� ó�� : �ߺ� ���� ���� ��� ���� 
	if (isInternal(newNode))
		return;
	else {
		newNode->key = key;
		expandExternal(newNode);
		searchAndFixAfterInsertion(newNode);
	}
}

Node* inOrderSucc(Node *node) {

	Node *horse = node->RChild;

	// ���� ó�� : �ܺγ���� ��� NULL ��ȯ 
	if (isExternal(horse))
		return NULL;

	while (isInternal(horse->LChild))
		horse = horse->LChild;

	return horse;
}

void searchAndFixAfterRemoval(Node *w) {

	Node *x, *y, *z, *b;

	// ���� ó�� : NULL �� �� ��� ���� 
	if (w == NULL)
		return;

	z = w;
	// ���� �缳�� , �뷱�� üũ�ϸ� �θ� ���� �ݺ� 
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	// ���� ó�� : �뷱�� ������ �� ���� 
	if (isBalanced(z))
		return;

	// Fix
	if (z->LChild->height > z->RChild->height)
		y = z->LChild;
	else
		y = z->RChild;

	if (y->LChild->height > y->RChild->height)
		x = y->LChild;
	else if (y->LChild->height < y->RChild->height)
		x = y->RChild;
	else {
		if (z->LChild == y)
			x = y->LChild;
		else
			x = y->RChild;
	}

	// �θ� ���� �ö󰡸� �Լ��� �ݺ��Ѵ� 
	b = restructure(x, y, z);
	searchAndFixAfterRemoval(b->parent);
}

Node* reduceExternal(Node *z) {

	Node *w = z->parent;
	Node *zs = sibling(z);

	if (w->parent == NULL) {
		root = zs;
		zs->parent = NULL;
	}

	// Root ��� ���Ű� �ƴ� �Ϲ� ����� ��� 
	else {
		Node *g = w->parent;
		zs->parent = g;

		if (w == g->LChild)
			g->LChild = zs;
		else
			g->RChild = zs;

		free(z);
		free(w);
	}

	return zs;
}

int removeElement(Node *root, int removeKey) {

	Node *nodeToRemove = treeSearch(root, removeKey);

	// ���� ó�� : ������ key�� ���� ��� NoSuchKey ��ȯ
	if (isExternal(nodeToRemove))
		return NoSuchKey;

	int removedKey = nodeToRemove->key;
	Node *z = nodeToRemove->LChild;

	// z�� ���γ���̸� ������ ���� ���� 
	if (!isExternal(z))
		z = nodeToRemove->RChild;

	Node *zs;
	// z�� �ܺγ���� ���
	if (isExternal(z))
		zs = reduceExternal(z);
	// ������ ����� �ڽ� ��尡 2���� ���
	else {
		// ���� ������ȸ �İ��ڸ� ã�Ƽ� �Ű��� 
		Node *y = inOrderSucc(nodeToRemove);
		z = y->LChild;
		nodeToRemove->key = y->key;
		zs = reduceExternal(z);
	}

	searchAndFixAfterRemoval(zs->parent);
	return removedKey;
}


// Ʈ�� Ž�� �Լ�
int findElement(Node *root, int findKey) {

	Node *findNode = treeSearch(root, findKey);

	// ���� ó�� : ã�� key�� ���� ��� NoSuchKey ��ȯ
	if (isExternal(findNode))
		return NoSuchKey;
	else
		return findNode->key;
}

void preOrderPrint(Node *node) {

	// ���� ó�� : ����ִ� Ʈ���� ��� ���� 
	if (isExternal(node))
		return;

	if (isInternal(node))
		printf(" %d", node->key);

	if (isInternal(node->LChild))
		preOrderPrint(node->LChild);

	if (isInternal(node->RChild))
		preOrderPrint(node->RChild);
}

// ������ȸ �ϸ� �޸� ���� 
void freeTree(Node *node) {

	if (isInternal(node->LChild))
		freeTree(node->LChild);

	if (isInternal(node->RChild))
		freeTree(node->RChild);

	if (isInternal(node))
		free(node);
}

int main() {

	// ��Ʈ ��� �ܺ� ���� �ʱ�ȭ
	root = getNode();

	char order;
	int num, removedKey, findNum;

	while (1) {

		scanf("%c", &order);
		getchar();

		switch (order) {

			// ����
		case 'q':
			// �޸� ��ȯ �Լ� �� ���� 
			freeTree(root);
			return 0;

			// ����
		case 'i':
			scanf("%d", &num);
			getchar();
			insertItem(root, num);
			break;

			// Ž��
		case 's':
			scanf("%d", &num);
			getchar();

			findNum = findElement(root, num);

			// ���� ó�� : NoSuchKey�� ��ȯ�Ǹ� X ��� 
			if (findNum != NoSuchKey)
				printf("%d\n", findNum);
			else
				printf("X\n");
			break;

			// ���� 
		case 'd':
			scanf("%d", &num);
			getchar();

			removedKey = removeElement(root, num);

			// ���� ó�� : NoSuchKey�� ��ȯ�Ǹ� X ���
			if (removedKey != NoSuchKey)
				printf("%d\n", removedKey);
			else
				printf("X\n");
			break;

			// �μ� - ������ȸ
		case 'p':
			preOrderPrint(root);
			printf("\n");
			break;
		}
	}
}
