#include<stdio.h>
#include<stdlib.h>
int H[100];
int N = 0;
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void downHeap(int i) {

	int index = i, child;
	while (index <= N / 2) {
		child = index * 2;
		if (child + 1 <= N && H[child] < H[child + 1]) {
			child++;
		}
		if (H[child] > H[index]) {
			swap(&H[child], &H[index]);
			index = child;
		}
		else {
			break;
		}

	}
}
void rBuildHeap(int index) {
	if (index > N)
		return;
	rBuildHeap(2 * index);
	rBuildHeap(2 * index + 1);
	downHeap(index);
}
void printHeap() {
	for (int i = 1; i <= N; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void inPlaceHeapSort(int i) {
	rBuildHeap(1);
	swap(&H[1], &H[N]);
	N--,i--;
	if(i>1)
		inPlaceHeapSort(i);
}
int main() {
	int num;
	scanf("%d", &num);
	N = num;
	for (int i = 1; i <= num; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	inPlaceHeapSort(num);
	N = num;
	printHeap();
}