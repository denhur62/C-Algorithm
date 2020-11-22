#include<stdio.h>
#include<stdlib.h>
int intcmp(const void *pa, const void *pb) {
	return *(int *)pa > *(int *)pb ? 1 : (*(int *)pa < *(int *)pb ? -1 : 0);
}
int binarySearch(int *arr, int key, int size) { //arr = 배열a[], key = 배열b[i], size = 배열a의 길이 n
	int front, mid, rear;
	front = 0; rear = size - 1;
	while (1) {
		mid = (front + rear) / 2;
		if (arr[mid] == key) return 1;
		if (arr[front] == key) return 1;
		if (arr[rear] == key) return 1;

		if (arr[mid] < key) front = mid + 1;
		else rear = mid - 1;
		if (rear <= front) return 0;
	}
}
int main() {
	int i, n, m, a[100000], b[100000];
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	qsort(a, n, sizeof(int), intcmp);

	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		scanf("%d", &b[i]);
		b[i] = binarySearch(a, b[i], n);
	}
	for (i = 0; i < m; i++) printf("%d ", b[i]);
}