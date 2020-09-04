#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define NoSuchKey INT_MIN
// NoSuchKey를 위한 설정

typedef enum { false, true } bool;
typedef struct Node {
	struct Node* parent;
	struct Node* LChild;
	struct Node* RChild;
	int height;
	int key;
} Node;

// 트리의 루트 노드 전역 선언 
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
	// 예외 처리 : 루트 노드일 경우 NULL값 반환 
	if (node->parent == NULL)
		return NULL;

	if (node->parent->LChild == node)
		return node->parent->RChild;
	else
		return node->parent->LChild;
}

Node* treeSearch(Node *node, int key) {

	Node *horse = node;

	// 예외 처리 : 외부노드일 경우 바로 반환 
	if (isExternal(horse))
		return horse;

	if (horse->key < key)
		return treeSearch(horse->RChild, key);
	else if (horse->key > key)
		return treeSearch(horse->LChild, key);
	else
		return horse;
}

// 노드의 높이를 확인하는 함수 
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

// 밸런스가 안맞는 경우 false 반환
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

	// 4가지의 경우로 나눠 진행
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

	// 예외 처리 : z가 루트 노드인 경우 
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

	// 예외 처리 : 루트 노드일 경우 종료 
	if (w->parent == NULL)
		return;

	z = w->parent;

	// 부모 노드로 올라가며 밸런스 확인 
	while (updateHeight(z) && isBalanced(z)) {
		// 예외 처리 : z가 루트일 경우 종료 
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	// 예외 처리 : 밸런스 이상이 없을 시 종료 
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

	// 개조 
	restructure(x, y, z);
	return;
}

// 트리 탐색 함수
void insertItem(Node* w, int key) {

	Node *newNode = treeSearch(w, key);

	// 예외 처리 : 중복 값이 들어올 경우 종료 
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

	// 예외 처리 : 외부노드인 경우 NULL 반환 
	if (isExternal(horse))
		return NULL;

	while (isInternal(horse->LChild))
		horse = horse->LChild;

	return horse;
}

void searchAndFixAfterRemoval(Node *w) {

	Node *x, *y, *z, *b;

	// 예외 처리 : NULL 값 인 경우 종료 
	if (w == NULL)
		return;

	z = w;
	// 높이 재설정 , 밸런스 체크하며 부모 노드로 반복 
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	// 예외 처리 : 밸런스 정상일 시 종료 
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

	// 부모 노드로 올라가며 함수를 반복한다 
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

	// Root 노드 제거가 아닌 일반 노드의 경우 
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

	// 예외 처리 : 제거할 key가 없는 경우 NoSuchKey 반환
	if (isExternal(nodeToRemove))
		return NoSuchKey;

	int removedKey = nodeToRemove->key;
	Node *z = nodeToRemove->LChild;

	// z가 내부노드이면 오른쪽 노드로 변경 
	if (!isExternal(z))
		z = nodeToRemove->RChild;

	Node *zs;
	// z가 외부노드일 경우
	if (isExternal(z))
		zs = reduceExternal(z);
	// 삭제할 노드의 자식 노드가 2개인 경우
	else {
		// 다음 중위순회 후계자를 찾아서 옮겨줌 
		Node *y = inOrderSucc(nodeToRemove);
		z = y->LChild;
		nodeToRemove->key = y->key;
		zs = reduceExternal(z);
	}

	searchAndFixAfterRemoval(zs->parent);
	return removedKey;
}


// 트리 탐색 함수
int findElement(Node *root, int findKey) {

	Node *findNode = treeSearch(root, findKey);

	// 예외 처리 : 찾는 key가 없는 경우 NoSuchKey 반환
	if (isExternal(findNode))
		return NoSuchKey;
	else
		return findNode->key;
}

void preOrderPrint(Node *node) {

	// 예외 처리 : 비어있는 트리인 경우 종료 
	if (isExternal(node))
		return;

	if (isInternal(node))
		printf(" %d", node->key);

	if (isInternal(node->LChild))
		preOrderPrint(node->LChild);

	if (isInternal(node->RChild))
		preOrderPrint(node->RChild);
}

// 후위순회 하며 메모리 해제 
void freeTree(Node *node) {

	if (isInternal(node->LChild))
		freeTree(node->LChild);

	if (isInternal(node->RChild))
		freeTree(node->RChild);

	if (isInternal(node))
		free(node);
}

int main() {

	// 루트 노드 외부 노드로 초기화
	root = getNode();

	char order;
	int num, removedKey, findNum;

	while (1) {

		scanf("%c", &order);
		getchar();

		switch (order) {

			// 종료
		case 'q':
			// 메모리 반환 함수 후 종료 
			freeTree(root);
			return 0;

			// 삽입
		case 'i':
			scanf("%d", &num);
			getchar();
			insertItem(root, num);
			break;

			// 탐색
		case 's':
			scanf("%d", &num);
			getchar();

			findNum = findElement(root, num);

			// 예외 처리 : NoSuchKey가 반환되면 X 출력 
			if (findNum != NoSuchKey)
				printf("%d\n", findNum);
			else
				printf("X\n");
			break;

			// 삭제 
		case 'd':
			scanf("%d", &num);
			getchar();

			removedKey = removeElement(root, num);

			// 예외 처리 : NoSuchKey가 반환되면 X 출력
			if (removedKey != NoSuchKey)
				printf("%d\n", removedKey);
			else
				printf("X\n");
			break;

			// 인쇄 - 전위순회
		case 'p':
			preOrderPrint(root);
			printf("\n");
			break;
		}
	}
}
