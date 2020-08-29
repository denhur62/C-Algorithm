#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct Partition {
	int L, R;
}Partition;
void swap(int *a,int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int find_pivot_index(int *L, int l, int r) {

	int index = rand() % (r - l + 1) + l;

	return index;
}
Partition inPlacePartition(int *L,int l,int r,int k) {
	int a = l;
	int i = l;
	int b = r;
	int pivot = L[k];
	int tmp;
	Partition eq;
	while (i <= b) {
		if (L[i] < pivot) {
			tmp = L[i];
			L[i] = L[a];
			L[a] = tmp;
			a++;
			i++;
		}
		else if (L[i] > pivot) {
			tmp = L[i];
			L[i] = L[b];
			L[b] = tmp;
			b--;
		}
		else
			i++;
	}
	eq = { a,b };
	return eq;
}
void inPlaceQuickSort(int *L,int l, int r) {
	int k;
	if (l >= r)
		return;
	k = find_pivot_index(L, l, r);
	Partition partn = inPlacePartition(L, l, r, k);
	inPlaceQuickSort(L, 1, partn.L- 1);
	inPlaceQuickSort(L, partn.R + 1, r);
}
void printQuickSort(int a[],int N) {
	for (int i = 1; i <= N; i++) {
		printf(" %d",a[i]);
	}
	printf("\n");
}
int main() {
	int N,*arr;
	scanf("%d",&N);
	arr = (int*)malloc(sizeof(int) *(N+1));
	for (int i = 1; i <= N; i++) {
		scanf("%d",&arr[i]);
	}
	inPlaceQuickSort(arr, 1, N);

	printQuickSort(arr,N);
	free(arr);
}