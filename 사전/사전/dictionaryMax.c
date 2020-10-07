#include<stdio.h>
#include<stdlib.h>
int findElement(int *arr, int l, int r, int k) {
	int mid;
	if (arr[l] > k)
		return l - 1;
	if (l == r) 
		return r;
	mid = (l + r) / 2;
	if (k == arr[mid])
		return mid;
	if(k < arr[mid])
		return findElement(arr,l, mid - 1,k);
	else
		return findElement(arr, mid+1,r, k);

}
int main() {
	int a,k,*arr,answer;
	scanf("%d %d",&a,&k);
	arr = (int*)malloc(sizeof(int)*a);
	for (int i = 0; i < a; i++) {
		scanf("%d",&arr[i]);
	}
	answer=findElement(arr,0,a-1,k);
	printf("%d",answer);
	free(arr);
}