#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct Partition {
	int L, R;
} Partition;

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int find_pivot_index(int *L, int l, int r) {

	int index = rand() % (r - l + 1) + l;

	return index;
}

Partition inPlacePartition(int *L, int l, int r, int pivotIndex) {

	if (l >= r)
		return;

	int pivot = L[pivotIndex];

	//pivot 맨 오른쪽으로 
	swap(&L[pivotIndex], &L[r]);

	int toRight = l;
	int toLeft = r - 1;

	while (toRight <= toLeft) {

		//피벗보다 크거나 같은 값을 찾아서 
		while (L[toRight] < pivot && toRight < r)
			toRight++;
		//피벗보다 작거나 같은 값을 찾아서	
		while (L[toLeft] > pivot && toLeft >= l)
			toLeft--;

		//엇갈리지 않은 경우 값만 변경
		if (toRight <= toLeft)
			swap(&L[toRight++], &L[toLeft--]);
	}

	//엇갈린 경우 피벗과 swap
	swap(&L[r], &L[toRight]);

	int a = toRight;
	int b = toRight;

	while (a > l && L[a - 1] == L[toRight])
		a--;
	while (b < r && L[b + 1] == L[toRight])
		b++;

	Partition partition = { a,b };
	return partition;
}

void inPlaceQuickSort(int *L, int l, int r) {

	if (l >= r)
		return;

	int pivotIndex = find_pivot_index(L, l, r);

	Partition partition = inPlacePartition(L, l, r, pivotIndex);

	inPlaceQuickSort(L, l, partition.L - 1);
	inPlaceQuickSort(L, partition.R + 1, r);
}

void printArray(int *L, int l, int r) {
	for (int i = l; i <= r; ++i)
		printf(" %d", L[i]);
}

int main() {

	srand(time(NULL));

	int N;
	scanf("%d", &N);

	int *L = (int*)malloc((N + 1) * sizeof(int));

	for (int i = 1; i <= N; ++i)
		scanf("%d", &L[i]);

	inPlaceQuickSort(L, 1, N);

	printArray(L, 1, N);
	free(L);
}
