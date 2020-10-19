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

	// 마지막 부모일 때 까지만 반복 
	while (index <= n / 2) {

		// child의 초기값은 왼쪽 자식으로 
		int child = index * 2;
		// 왼쪽 자식보다 오른쪽 자식이 더 작을 경우 child를 오른쪽 자삭으로 
		if (child + 1 <= n && L[child] > L[child + 1])
			child++;

		// 부모보다 자식이 더 작을 경우 swap 
		if (L[index] > L[child]) {
			swap(&L[index], &L[child]);
			index = child;
		}
		else
			break;
	}
}

// 비재귀 상향식 힙 구조화 함수
void buildHeap(int* L, int n) {

	for (int i = n / 2; i >= 1; --i)
		downHeap(L, n, i);
}

// n개의 원소들 중 k번째로 작은 원소를 찾는 함수
int findKthSmallest(int* L, int n, int k) {

	// 주의 2번 조건 - 인자 L은 항상 최근에 구축된 초기 리스트 L이어야 함
	// L2에 L을 복사하고 L2로 값을 구한다. 
	int* L2 = (int*)malloc((n + 1) * sizeof(int));
	if (L2 == NULL) return -1;

	for (int i = 1; i <= n; ++i)
		L2[i] = L[i];

	// 비재귀 상향식 힙 구조화 함수 호출 
	// 시간 복잡도 O(n)
	buildHeap(L2, n);

	// 현재 배열에서 최소값(index 1)을 배열의 맨 뒤로 swap, 바뀐 값은 알맞는 자리로 downHeap
	// 배열의 크기를 1씩 줄이며 k번만 반복
	// 시간 복잡도 O(k * log n)
	for (int i = 0; i < k; ++i) {
		swap(&L2[n - i], &L2[1]);
		downHeap(L2, n - i - 1, 1);
	}

	//반환할 값 따로 저장 후 메모리 반환
	int answer = L2[n - k + 1];
	free(L2);

	return answer;
}

int* buildList(int n, int min, int max) {

	// 배열의 인덱스가 1부터 시작하니 (n+1)개의 정수 자리를 할당
	int* L = (int*)malloc((n + 1) * sizeof(int));

	// min 이상 max 이하의 난수 생성
	for (int i = 1; i <= n; ++i) {
		L[i] = ((((long) rand() << 15) | rand()) % 1000000);
		L[i] = L[i] % (max-min+1) + min;
	}
		
	return L;
}

int main() {

	// 매번 다른 난수를 발생시키기 위해 시드값 설정
	srand(time(NULL));

	// 1
	// L에 buildList 함수를 통해 생성한 새로운 배열 연결
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
	// L에 할당된 메모리 해제 이후 buildList 함수를 통해 생성한 새로운 배열 연결
	free(L);
	L = buildList(100000, 1, 1000000);
	if (L == NULL) return -1;

	// 6
	int karray[4] = { 1, 100, 99900, 99999 };

	// 7
	// k번째로 작은 원소와 측정한 시간을 담을 변수 선언
	int e;
	double t;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	for (int k = 0; k <= 3; ++k) {

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		// 시간 측정할 함수 실행
		e = findKthSmallest(L, 100000, karray[k]);

		QueryPerformanceCounter(&end);

		// 측정값으로부터 실행시간 계산
		diff.QuadPart = end.QuadPart - start.QuadPart;

		t = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

		printf("%d  time : %.12lf sec\n", e, t);
	}

	free(L);
	return 0;
}

