#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void downHeap(int* L, int n, int index) {

	// ������ �θ��� �� ������ �ݺ� 
	while (index <= n / 2) {

		// child�� �ʱⰪ�� ���� �ڽ����� 
		int child = index * 2;
		// ���� �ڽĺ��� ������ �ڽ��� �� ���� ��� child�� ������ �ڻ����� 
		if (child + 1 <= n && L[child] > L[child + 1])
			child++;

		// �θ𺸴� �ڽ��� �� ���� ��� swap 
		if (L[index] > L[child]) {
			swap(&L[index], &L[child]);
			index = child;
		}
		else
			break;
	}
}

// ����� ����� �� ����ȭ �Լ�
void buildHeap(int* L, int n) {

	for (int i = n / 2; i >= 1; --i)
		downHeap(L, n, i);
}

// n���� ���ҵ� �� k��°�� ���� ���Ҹ� ã�� �Լ�
int findKthSmallest(int* L, int n, int k) {

	// ���� 2�� ���� - ���� L�� �׻� �ֱٿ� ����� �ʱ� ����Ʈ L�̾�� ��
	// L2�� L�� �����ϰ� L2�� ���� ���Ѵ�. 
	int* L2 = (int*)malloc((n + 1) * sizeof(int));
	if (L2 == NULL) return -1;

	for (int i = 1; i <= n; ++i)
		L2[i] = L[i];

	// ����� ����� �� ����ȭ �Լ� ȣ�� 
	// �ð� ���⵵ O(n)
	buildHeap(L2, n);

	// ���� �迭���� �ּҰ�(index 1)�� �迭�� �� �ڷ� swap, �ٲ� ���� �˸´� �ڸ��� downHeap
	// �迭�� ũ�⸦ 1�� ���̸� k���� �ݺ�
	// �ð� ���⵵ O(k * log n)
	for (int i = 0; i < k; ++i) {
		swap(&L2[n - i], &L2[1]);
		downHeap(L2, n - i - 1, 1);
	}

	//��ȯ�� �� ���� ���� �� �޸� ��ȯ
	int answer = L2[n - k + 1];
	free(L2);

	return answer;
}

int* buildList(int n, int min, int max) {

	// �迭�� �ε����� 1���� �����ϴ� (n+1)���� ���� �ڸ��� �Ҵ�
	int* L = (int*)malloc((n + 1) * sizeof(int));

	// min �̻� max ������ ���� ����
	for (int i = 1; i <= n; ++i) {
		L[i] = ((((long) rand() << 15) | rand()) % 1000000);
		L[i] = L[i] % (max-min+1) + min;
	}
		
	return L;
}

int main() {

	// �Ź� �ٸ� ������ �߻���Ű�� ���� �õ尪 ����
	srand(time(NULL));

	// 1
	// L�� buildList �Լ��� ���� ������ ���ο� �迭 ����
	int* L = buildList(10, 1, 100);
	if (L == NULL) return -1;

	// 2
	for (int i = 1; i <= 10; ++i)
		printf("%d ", L[i]);
	printf("\n");

	// 3
	int output[4];
	for (int k = 1; k <= 3; ++k)
		output[k] = findKthSmallest(L, 10, k);

	// 4
	for (int i = 1; i <= 3; ++i)
		printf("%d ", output[i]);
	printf("\n");

	// 5
	// L�� �Ҵ�� �޸� ���� ���� buildList �Լ��� ���� ������ ���ο� �迭 ����
	free(L);
	L = buildList(100000, 1, 1000000);
	if (L == NULL) return -1;

	// 6
	int karray[4] = { 1, 100, 99900, 99999 };

	// 7
	// k��°�� ���� ���ҿ� ������ �ð��� ���� ���� ����
	int e;
	double t;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	for (int k = 0; k <= 3; ++k) {

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		// �ð� ������ �Լ� ����
		e = findKthSmallest(L, 100000, karray[k]);

		QueryPerformanceCounter(&end);

		// ���������κ��� ����ð� ���
		diff.QuadPart = end.QuadPart - start.QuadPart;

		t = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

		printf("%d  time : %.12lf sec\n", e, t);
	}

	free(L);
	return 0;
}

