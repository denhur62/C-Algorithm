#include<stdio.h>
#include<stdlib.h>
int N = 0;
int sorted[101] = { 0 };
int Max(int a,int b) {
	a < b ? b : a;
}
int rMergeSort(int l, int r) {
	int rMax, lMax,Maximum;
	if (l == r) {
		return sorted[l];
	}
	int middle = (l + r) / 2;
	lMax = rMergeSort(l, middle);
	rMax = rMergeSort(middle + 1, r);
	Maximum = Max(rMax, lMax);
	return Maximum;
}
void mergeSort() {
	int Maximum;
	Maximum=rMergeSort(0, N - 1);
	printf("%d", Maximum);
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &sorted[i]);
	mergeSort();
}