#include<stdio.h>

typedef struct HashTable {
	int *arr;
	int size;
}HashTable;
int hashFunction(int x, int m) {
	return x%m;
}
void insertItem(HashTable *hashTable,int key) {
	int hashkey = hashFunction(key, hashTable->size);
	if (hashTable->arr[hashkey] != 0) {
		while (hashTable->arr[hashkey] != 0) {
			hashkey = (++hashkey)%hashTable->size;
			printf("C");
		}
		hashTable->arr[hashkey] = key;
		printf("%d\n",hashkey);
	}
	else
	{
		hashTable->arr[hashkey] = key;
		printf("%d\n", hashkey);
	}
}
void searchItem(HashTable *hashTable, int key) {
	int count=0;
	int hashValue = hashFunction(key, hashTable->size);
	while (count < hashTable->size) {
		// key 값을 찾을 경우
		if (hashTable->arr[hashValue] == key) {
			printf("%d %d\n", hashValue, key);
			return;
		}
		hashValue = (hashValue + 1) % hashTable->size;
		count++;
	}
	printf("-1\n");
}
int main() {
	int m, n, i;
	char order;
	int key;
	HashTable table;
	scanf("%d %d", &m, &n);
	getchar();
	table.arr = (int*)malloc(sizeof(int)*m);
	table.size = m;
	for (i = 0; i < m; i++) {
		table.arr[i] = 0;
	}

	while (1) {
		scanf("%c", &order);
		if (order == 'i') {
			scanf(" %d", &key);
			insertItem(&table, key);
		}
		else if (order == 's') {
			scanf(" %d", &key);
			searchItem(&table, key);
		}
		else return;
		getchar();
	}
}