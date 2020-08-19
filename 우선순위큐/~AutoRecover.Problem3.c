#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>


void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void inPlaceSelectionSort(int ar[], int num) {

	for (int i = num - 1; i>0; --i) {
		int maxIndex = i;
		for (int j = 0; j <= i; ++j) {
			if (ar[maxIndex] < ar[j])
				maxIndex = j;
		}
		swap(&ar[maxIndex], &ar[i]);
	}
}

void inPlaceInsertionSort(int ar[], int num) {

	for (int i = 0; i<num - 1; ++i) {

		int index = i;
		while (index >= 0 && ar[index] > ar[index + 1]) {
			swap(&ar[index], &ar[index + 1]);
			index--;
		}
	}
}

void Sort(int ar[], int num) {
	for (int i = 0; i<num - 1; ++i) {

		int index = i;
		while (index >= 0 && ar[index] > ar[index + 1]) {
			swap(&ar[index], &ar[index + 1]);
			index--;
		}
	}
}

void reverseSort(int ar[], int num) {
	for (int i = 0; i<num - 1; ++i) {

		int index = i;
		while (index >= 0 && ar[index] < ar[index + 1]) {
			swap(&ar[index], &ar[index + 1]);
			index--;
		}
	}
}
int main() {

	//시간측정 함수 사용 준비 (출력시 ms단위로) 
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	for (int z = 0; z<3; ++z) {
		int n;
		scanf("%d", &n);

		int *A = (int*)malloc(n * sizeof(int));
		int *B = (int*)malloc(n * sizeof(int));

		srand(time(NULL));

		//난수 초기화 이후 생성한 난수를 A,B 배열에 동일하게 넣어준다. 
		for (int i = 0; i<n; ++i) {
			int num = rand();
			A[i] = num;
			B[i] = num;
		}

		// 1. 정렬되어 있지 않은 경우 
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//A 배열 선택 정렬 수행 
		inPlaceSelectionSort(A, n);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//B 배열 삽입 정렬 수행 
		inPlaceInsertionSort(B, n);

		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


		// 2. 정렬되어 있는 경우 

		Sort(A, n);
		Sort(B, n);

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//A 배열 선택 정렬 수행 
		inPlaceSelectionSort(A, n);

		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//B 배열 삽입 정렬 수행 
		inPlaceInsertionSort(B, n);

		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		// 3. 역정렬되어 있는 경우 

		reverseSort(A, n);
		reverseSort(B, n);

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//A 배열 선택 정렬 수행 
		inPlaceSelectionSort(A, n);

		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);

		//B 배열 삽입 정렬 수행 
		inPlaceInsertionSort(B, n);

		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B time: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
	}

}