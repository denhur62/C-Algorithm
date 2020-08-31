#include<stdio.h>
#include<stdlib.h>
int findElement(int *arr, int l, int r, int k) {
	int mid;

	while (l < r) {
		mid = (l + r) / 2;
		if (k == arr[mid])
			return mid;
		if (k < arr[mid])
			r = mid - 1;
		else
			l = mid + 1;
	}

	if (k > arr[r])
		return r+1;
	else
		return r;
	
}
int main() {
	int a, k, *arr, answer;
	scanf("%d %d", &a, &k);
	arr = (int*)malloc(sizeof(int)*a);
	for (int i = 0; i < a; i++) {
		scanf("%d", &arr[i]);
	}
	answer = findElement(arr, 0, a - 1, k);
	printf("%d", answer);
	free(arr);
}