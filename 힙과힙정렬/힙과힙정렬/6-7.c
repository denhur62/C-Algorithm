#include<stdio.h>
#include<stdlib.h>
int H[100];
int N,M;
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void downHeap(int index) {
	while (index <= N / 2) {
		int child = index * 2;
		if (child + 1 <= N && H[child] > H[child + 1])
			child++;
		if (H[index] > H[child]) {
			swap(&H[index], &H[child]);
			index = child;
		}
		else
			break;
	}
		
}
int buildHeap() {
	for (int i = N / 2; i >= 1; i--)
		downHeap(i);
}
int main() {
	scanf("%d",&N);
	for (int i = 1; i <= N; i++)
		scanf("%d",&H[i]);
	buildHeap();
	scanf("%d",&M);
	while (M >= H[1]) {
		printf("%d ", H[1]);
		H[1] = H[N--];
		buildHeap();
	}
}