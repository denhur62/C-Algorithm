#include<stdio.h>
#include<stdlib.h>
int H[100];
int N, M;
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
void printHeap(int n) {

	if (n > N)
		return;
	if (H[n] <= M)
		printf("%d ",H[n]);

	if (H[n * 2] > M && H[n * 2 + 1] > M)
		return;
	
		printHeap(n * 2);
		printHeap(n * 2 + 1);
}
int main() {
	int cnt = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &H[i]);
	buildHeap();
	scanf("%d", &M);
	printHeap(1);
}