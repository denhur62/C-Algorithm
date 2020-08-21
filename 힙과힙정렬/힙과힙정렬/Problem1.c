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
void upHeap(int i) {
	while (i > 1 && H[i] > H[i / 2]) {
		swap(&H[i], &H[i / 2]);
		i /= 2;
	}
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
			index =child;
		}
		else {
			break;
		}

	}
}
void insertItem(int key) {
	N = N + 1;
	H[N] = key;
	upHeap(N);
	printf("0\n");
}
int removeMax() {
	int max = H[1];
	H[1] = H[N];
	N--;
	downHeap(1);
	return max;
}

void printHeap() {
	for (int i = 1; i <= N; i++)
		printf(" %d",H[i]);
	printf("\n");
}
int main() {
	int num;
	while(1) {
		char ch;
		scanf("%c",&ch);
		switch(ch) {
			case 'i':
				scanf("%d", &num);
				getchar();
				insertItem(num);
				break;
			case 'd':
				num = removeMax();
				printf("%d\n", num);
				break;
			case 'p':
				printHeap();
				break;
			case 'q':
				return;
		}
	}
}