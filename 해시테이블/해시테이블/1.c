#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	struct Node *next;
	int key;
}Node;
int hashFunction(int n,int m) {
	return n%m;
}
Node* getNode(int key) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->next = NULL;
	return newNode;
}
void insertItem(Node **hashTable, int n, int m) {
	int hashkey = hashFunction(n, m);
	Node *newNode = getNode(n);
	Node *horse= hashTable[hashkey];
	if (horse->next != NULL) {

		newNode->next = horse->next;
		horse->next = newNode;
	}
	else {
		horse->next = newNode;
	}

}
void searchHash(Node **hashTable, int n, int m) {

	int hashkey = hashFunction(n, m);
 	Node *horse = hashTable[hashkey];
	if (horse->next != NULL) {
		int index = 1;
		horse = horse->next;
		while (horse != NULL&& horse->key != n) {
			horse = horse->next;
			index++;
		}
		if (horse != NULL)
			printf("%d\n", index);
		else
			printf("0\n");
	}
	else
		printf("0\n");
}
void deleteItem(Node **hashTable, int n, int m) {
	int hashkey = hashFunction(n, m);
	Node *horse = hashTable[hashkey];
	Node *before = horse;
	if (horse->next != NULL) {
		int index = 1;
		horse = horse->next;
		while (horse != NULL&&horse->key != n) {
			before = horse;
			horse = horse->next;
			index++;
		}
		if (horse == NULL)
			printf("0\n");
		else {

			if (horse->next != NULL) {
				before->next = horse->next;
				free(horse);
			}
			else {
				before->next = NULL;
				free(horse);
			}
			printf("%d\n",index);
		}
	}
	else
		printf("0\n");

}
void printHash(Node **hasTable, int m) {

	Node *horse = NULL;
	for (int i = 0; i < m; i++) {
		horse = hasTable[i];
		while(horse->next != NULL) {
			horse = horse->next;
			printf(" %d",horse->key);
		}
	}
	printf("\n");
}
void freeHash(Node **hashTable, int m) {
	for (int i = 0; i < m; i++) {
		Node *horse = hashTable[i];
		while (horse != NULL) {
			Node *toFree = horse;
			horse = horse->next;
			free(toFree);
		}
	}
}
int main() {
	Node **hashTable;
	int i, m, n;
	char order;
	scanf("%d", &m);
	hashTable = (Node**)malloc(sizeof(Node*)*m);
	for (i = 0; i < m; i++) {
		hashTable[i] = getNode(NULL);
	}
	getchar();
	while (1) {

		scanf("%c", &order);
		if (order == 'i') {
			scanf(" %d", &n);
			insertItem(hashTable, n, m);
		}
		else if (order == 's') {
			scanf(" %d", &n);
			searchHash(hashTable, n, m);
		}
		else if (order == 'd') {
			scanf(" %d", &n);
			deleteItem(hashTable, n, m);
		}
		else if (order == 'p') {
			printHash(hashTable, m);
		}
		else if (order == 'e') {
			return;
		}
		getchar();
	}
	freeHash(hashTable,m);
}