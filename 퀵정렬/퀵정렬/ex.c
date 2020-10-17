#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<math.h>

// 전역 변수 선언 ( mode는 열거형으로 사용 )
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

// 제자리 삽입 정렬 함수
void inPlaceInsertionSort(int* A, int num) {

	int index, horse, save;
	for (index = 1; index < num; ++index) {
		save = A[index];
		horse = index - 1;
		// 알맞는 자리로 한칸씩 이동한다
		while (horse >= 0 && A[horse] > save) {
			A[horse + 1] = A[horse];
			horse--;
		}
		A[horse + 1] = save;
	}
}

// 배열을 생성 후 반환하는 함수
int* createArray() {

	int* A = (int*)malloc(n * sizeof(int));

	int max = 100000;
	int min = 1;

	// min (1) ~ max (100,000) 사이의 난수 n (100,000)개 생성
	for (int i = 0; i < n; ++i) {
		A[i] = ((((long)rand() << 15) | rand()) % 1000000);
		A[i] = A[i] % (max - min + 1) + min;
	}

	return A;
}

// 초기 배열을 복사한 후 복사본을 반환하는 함수
int* copyArray(int* A) {

	int* A2 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		A2[i] = A[i];

	return A2;
}

// 3가지 구간으로 나눈 후 가운데 구간의 시작과 끝을 (Partition 구조체로) 반환하는 함수 
Partition inPlacePartition(int* A, int l, int r, int k) {

	// 반환할 구조체 선언
	Partition partition = { l,r };

	// 매개변수의 배열 범위가 올바른지 확인
	if (l >= r)
		return;

	int pivot = A[k];

	// pivot 맨 오른쪽으로 swap
	swap(&A[k], &A[r]);

	// index는 한칸씩 움직이며 pivot보다 작은 값을 왼쪽으로 swap하며 구간을 나눔 
	int index = l;
	for (int i = l; i < r; ++i) {
		if (A[i] < pivot)
			swap(&A[i], &A[index++]);
	}

	// pivot 알맞는 자리로 swap
	swap(&A[index], &A[r]);

	// 3 way partitioning
	// a,b 시작은 pivot의 자리로 부터 
	// pivot과 같은 값을 찾으면 a는 좌로 b는 우로 한칸씩 늘려가며 가운데 구간으로 모아준다 (swap)
	int a = index;
	int b = index;

	// 왼쪽 구간 확인
	// left 변수를 한칸씩 이동하며 pivot과 같은 값이면 가운데 구간으로 swap
	int left = l;
	while (left < a) {
		if (A[left] == pivot)
			swap(&A[left], &A[--a]);
		else
			left++;
	}

	// 오른쪽 구간 확인 
	// right 변수를 한칸씩 이동하며 pivot과 같은 값이면 가운데 구간으로 swap
	int right = r;
	while (right > b) {
		if (A[right] == pivot)
			swap(&A[right], &A[++b]);
		else
			right--;
	}

	// 가운데 구간에 맞는 값을 넣은 후 구조체 반환
	partition.a = a;
	partition.b = b;

	return partition;
}

// pivot의 위치를 현재 mode에 맞게 정하고 반환하는 함수
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

// (재귀) 제자리 퀵 정렬 함수
void rQuickSort(int* A, int l, int r, int Limit) {

	if (r - l >= Limit) {
		int k = findPivot(A, l, r);
		Partition partition = inPlacePartition(A, l, r, k);
		rQuickSort(A, l, partition.a - 1, Limit);
		rQuickSort(A, partition.b + 1, r, Limit);
	}
}

// 퀵 정렬을 실행하는 함수
void quickSort(int* A, int n, int Limit) {

	rQuickSort(A, 0, n - 1, Limit);
	if (Limit > 1)
		inPlaceInsertionSort(A, n);
}

int main() {

	// 항상 다른 난수를 발생시키기 위해 시드값 설정
	srand(time(NULL));

	// 1.
	int* A = createArray();
	if (A == NULL) return -1;

	// 시간 측정을 위한 변수들 선언
	double time;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	// 출력을 위한 셋팅
	printf("Limit       결정적1     결정적3     무작위1     무작위3 \n");

	// 2.
	// Limit에 대한 반복문
	for (int i = 0; i < 4; ++i) {

		// (열거형) mode에 대한 반복문
		printf("%d	", Limit[i]);
		for (mode = 0; mode < 4; mode++) {

			// 배열 복사 함수 실행 
			int* A2 = copyArray(A);
			if (A2 == NULL) return -1;

			QueryPerformanceFrequency(&ticksPerSec);
			QueryPerformanceCounter(&start);

			// 시간 측정할 함수 실행
			quickSort(A2, n, Limit[i]);

			QueryPerformanceCounter(&end);

			// 측정값으로부터 실행시간 계산
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

