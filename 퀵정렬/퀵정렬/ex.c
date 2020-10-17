#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<math.h>

// ���� ���� ���� ( mode�� ���������� ��� )
int n = 100000;
int Limit[4] = { 1, 100, 500, 1000 };
enum Mode { deterministic1, deterministic3, randomized1, randomized3 };
int mode;

typedef struct Partition {
	int a, b;
} Partition;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// ���ڸ� ���� ���� �Լ�
void inPlaceInsertionSort(int* A, int num) {

	int index, horse, save;
	for (index = 1; index < num; ++index) {
		save = A[index];
		horse = index - 1;
		// �˸´� �ڸ��� ��ĭ�� �̵��Ѵ�
		while (horse >= 0 && A[horse] > save) {
			A[horse + 1] = A[horse];
			horse--;
		}
		A[horse + 1] = save;
	}
}

// �迭�� ���� �� ��ȯ�ϴ� �Լ�
int* createArray() {

	int* A = (int*)malloc(n * sizeof(int));

	int max = 100000;
	int min = 1;

	// min (1) ~ max (100,000) ������ ���� n (100,000)�� ����
	for (int i = 0; i < n; ++i) {
		A[i] = ((((long)rand() << 15) | rand()) % 1000000);
		A[i] = A[i] % (max - min + 1) + min;
	}

	return A;
}

// �ʱ� �迭�� ������ �� ���纻�� ��ȯ�ϴ� �Լ�
int* copyArray(int* A) {

	int* A2 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		A2[i] = A[i];

	return A2;
}

// 3���� �������� ���� �� ��� ������ ���۰� ���� (Partition ����ü��) ��ȯ�ϴ� �Լ� 
Partition inPlacePartition(int* A, int l, int r, int k) {

	// ��ȯ�� ����ü ����
	Partition partition = { l,r };

	// �Ű������� �迭 ������ �ùٸ��� Ȯ��
	if (l >= r)
		return;

	int pivot = A[k];

	// pivot �� ���������� swap
	swap(&A[k], &A[r]);

	// index�� ��ĭ�� �����̸� pivot���� ���� ���� �������� swap�ϸ� ������ ���� 
	int index = l;
	for (int i = l; i < r; ++i) {
		if (A[i] < pivot)
			swap(&A[i], &A[index++]);
	}

	// pivot �˸´� �ڸ��� swap
	swap(&A[index], &A[r]);

	// 3 way partitioning
	// a,b ������ pivot�� �ڸ��� ���� 
	// pivot�� ���� ���� ã���� a�� �·� b�� ��� ��ĭ�� �÷����� ��� �������� ����ش� (swap)
	int a = index;
	int b = index;

	// ���� ���� Ȯ��
	// left ������ ��ĭ�� �̵��ϸ� pivot�� ���� ���̸� ��� �������� swap
	int left = l;
	while (left < a) {
		if (A[left] == pivot)
			swap(&A[left], &A[--a]);
		else
			left++;
	}

	// ������ ���� Ȯ�� 
	// right ������ ��ĭ�� �̵��ϸ� pivot�� ���� ���̸� ��� �������� swap
	int right = r;
	while (right > b) {
		if (A[right] == pivot)
			swap(&A[right], &A[++b]);
		else
			right--;
	}

	// ��� ������ �´� ���� ���� �� ����ü ��ȯ
	partition.a = a;
	partition.b = b;

	return partition;
}

// pivot�� ��ġ�� ���� mode�� �°� ���ϰ� ��ȯ�ϴ� �Լ�
int findPivot(int* A, int l, int r) {

	// 1.
	if (mode == deterministic1)
		return r;

	// 2.
	if (mode == randomized1) {
		int randNum = ((((long)rand() << 15) | rand()) % 1000000);
		return randNum % (r - l + 1) + l;
	}

	// 3.
	if (r - l == 1)
		return l;

	// 4. select three positions
	int a, b, c;
	switch (mode) {
	case deterministic3:
		a = l;
		b = (l + r) / 2;
		c = r;
		break;
	case randomized3:
		a = ((((long)rand() << 15) | rand()) % 1000000);
		a = a % (r - l + 1) + l;
		b = ((((long)rand() << 15) | rand()) % 1000000);
		b = b % (r - l + 1) + l;
		c = ((((long)rand() << 15) | rand()) % 1000000);
		c = c % (r - l + 1) + l;
		break;
	}

	// 5. find median-of-3
	if (A[a] <= A[b]) {
		if (A[b] <= A[c])
			return b;
		else if (A[a] <= A[c])
			return c;
		else
			return a;
	}
	else {
		if (A[a] <= A[c])
			return a;
		else if (A[b] <= A[c])
			return c;
		else
			return b;
	}
}

// (���) ���ڸ� �� ���� �Լ�
void rQuickSort(int* A, int l, int r, int Limit) {

	if (r - l >= Limit) {
		int k = findPivot(A, l, r);
		Partition partition = inPlacePartition(A, l, r, k);
		rQuickSort(A, l, partition.a - 1, Limit);
		rQuickSort(A, partition.b + 1, r, Limit);
	}
}

// �� ������ �����ϴ� �Լ�
void quickSort(int* A, int n, int Limit) {

	rQuickSort(A, 0, n - 1, Limit);
	if (Limit > 1)
		inPlaceInsertionSort(A, n);
}

int main() {

	// �׻� �ٸ� ������ �߻���Ű�� ���� �õ尪 ����
	srand(time(NULL));

	// 1.
	int* A = createArray();
	if (A == NULL) return -1;

	// �ð� ������ ���� ������ ����
	double time;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	// ����� ���� ����
	printf("Limit       ������1     ������3     ������1     ������3 \n");

	// 2.
	// Limit�� ���� �ݺ���
	for (int i = 0; i < 4; ++i) {

		// (������) mode�� ���� �ݺ���
		printf("%d	", Limit[i]);
		for (mode = 0; mode < 4; mode++) {

			// �迭 ���� �Լ� ���� 
			int* A2 = copyArray(A);
			if (A2 == NULL) return -1;

			QueryPerformanceFrequency(&ticksPerSec);
			QueryPerformanceCounter(&start);

			// �ð� ������ �Լ� ����
			quickSort(A2, n, Limit[i]);

			QueryPerformanceCounter(&end);

			// ���������κ��� ����ð� ���
			diff.QuadPart = end.QuadPart - start.QuadPart;

			time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
			printf("  %.8lf", time);

			free(A2);
		}
		printf("\n");
	}

	// 3.
	free(A);
	return 0;
}

