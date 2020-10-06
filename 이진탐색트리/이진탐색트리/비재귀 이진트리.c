#include<stdio.h>
#include<stdlib.h>
int nonrecurive(int arr[],int n) {
	int start = 0, end = 9;
	while (start <= end) {
		int mid = (start + end) / 2;
		if (arr[mid] == n)
			return mid;
		else if (arr[mid] < n)
			start = mid + 1;
		else if (arr[mid] > n)
			end = mid - 1;
	}
	return 0;
}
int main() {
	int n,b;
	int a[10] = { 1,2,3,4,5,6,7,9,10,12 };
	scanf("%d",&n);
	b = nonrecurive(a, n);
	printf("%d", b);
}