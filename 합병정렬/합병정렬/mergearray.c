#include<stdio.h>
#include<stdlib.h>
int N = 0;
int sorted[101] = { 0 };
void Merge(int l,int middle,int r) {
	int i = l;
	int k = l;
	int j = middle + 1;
	int B[101];
	while (i <= middle && j <= r) {
		if (sorted[i] <= sorted[j])
			B[k++] = sorted[i++];
		else
			B[k++] = sorted[j++];
	}
	while (i <= middle) {
		B[k++] = sorted[i++];
	}
	while (j <= r) {
		B[k++] = sorted[j++];
	}
	for (int k = l; k <= r; k++)
		sorted[k] = B[k];
}
void rMergeSort(int l, int r) {
	if (l < r) {
		int middle = (l + r) / 2;
		rMergeSort(l, middle);
		rMergeSort(middle + 1, r);
		Merge(l, middle, r);
	}
}
void mergeSort() {
	rMergeSort(0, N - 1);
}
int main() {
	scanf("%d",&N);
	for (int i = 0; i < N; i++)
		scanf("%d",&sorted[i]);
	mergeSort();
	for (int i = 0; i < N; i++)
		printf("%d ", sorted[i]);
}