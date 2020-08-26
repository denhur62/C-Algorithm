#include<stdio.h>
#include<stdlib.h>
int N = 0;
int sorted[101] = { 0 };
void merge(int a[], int m, int middle, int n) {
	int i = m; 
	int j = middle + 1;
	int k = m;
	while (i <= middle && j <= n) {
		if (a[i] <= a[j]) {
			sorted[k] = a[i];
			i++;
		}
		else {
			sorted[k] = a[j];
			j++;
		}
		k++;
	}
	if (i > middle) {
		for (int t = j; t <= n; t++) {
			sorted[k] = a[t];
			k++;
		}
	}
	else {
		for (int t = i; t <= middle; t++) {
			sorted[k] = a[t];
			k++;
		}
	}
	for (int t = m; t <= n; t++) {
		a[t] = sorted[t];
	}
}
void mergeSort(int a[], int m, int n) {
	if (m < n) {
		int middle = (m + n) / 2;
		mergeSort(a, m, middle);
		mergeSort(a, middle + 1, n);
		merge(a, m, middle, n);
	}
}
int main() {
	int *array = NULL, a;
	scanf("%d",&a);
	array = (int*)malloc(sizeof(int)*a);
	for (int i = 0; i < a; i++) {
		scanf("%d",&array[i]);
	}
	mergeSort(array, 0, a - 1);
	for (int i = 0; i < a; i++) {
		printf("%d ",array[i]);
	}
}