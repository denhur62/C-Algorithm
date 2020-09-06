#include<stdio.h>
#include<stdlib.h>
typedef struct HashTable {
	int *arr;
	int size;
	int q;
}HashTable;
int hashFunction1(int n, int m) {
	return n%m;
}
int hashFunction2(int n,int m) {
	return m - (n%m);
}
void insertItem(HashTable *hashTable, int item) {
	int hashkey = hashFunction1(item, hashTable->size);
	int index = hashkey;
	int temp,count=1;
	if (hashTable->arr[hashkey] == 0) {
		hashTable->arr[hashkey] = item;
		printf("%d\n",hashkey);
		return;
	}
	while (hashTable->arr[hashkey] != 0) {
		temp = (index + count*hashFunction2(item,hashTable->q)) % hashTable->size;
		hashkey = temp;
		count++;
		printf("C");
	}
	hashTable->arr[temp] = item;
	printf("%d\n",hashkey);
}
void searchItem(HashTable *hashTable, int item) {
	int hashkey = hashFunction1(item, hashTable->size);
	int index = hashkey;
	int temp, count = 0;
	if (hashTable->arr[hashkey] == item) {
		printf("%d %d\n",hashkey,item);
		return;
	}
	while (count<hashTable->size) {
		if (hashTable->arr[hashkey] == item) {
			printf("%d %d\n", hashkey, item);
			return;
		}
		temp = (index + count*hashFunction2(item, hashTable->q)) % hashTable->size;
		hashkey = temp;
		count++;
	}
	printf("-1\n");
}
void printTable(HashTable *hashTable) {
	for (int i = 0; i < hashTable->size; i++) {
			printf(" %d", hashTable->arr[i]);
	}
	printf("\n");
}
int main() {
	int n, m, _q, item;
	char order;
	HashTable table;
	scanf("%d %d %d", &m, &n, &_q);
	table.arr = (int*)malloc(sizeof(int)*m);
	table.size = m;
	table.q = _q;
	for (int i = 0; i < m; i++) {
		table.arr[i] = 0;
	}
	getchar();
	while (1) {
		scanf("%c", &order);
		if (order == 'i') {
			scanf(" %d", &item);
			insertItem(&table, item);
		}
		else if (order == 's') {
			scanf(" %d", &item);
			searchItem(&table, item);
		}
		else if (order == 'p') {
			printTable(&table);
		}
		else if (order == 'e') {
			printTable(&table);
			return;
		}
	}
}