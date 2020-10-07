#include<stdio.h>
#include<stdlib.h>

int partition(int arr[],int l,int r) {

	int i = l, j = r-1;
	int temp;
	int pivot = (l + r) / 2;
	temp = arr[pivot];
	arr[pivot] = arr[r];
	arr[r] = temp;
	while (i <= j) {

		while(i <= j && arr[i] < arr[r])
			i++;
		while(i <= j && arr[j] > arr[r])
			j--;
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++; 
			j--;
		}
	}

	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;

	return i;

}
int quickSelect(int arr[],int l,int r,int k) {
	if (l >= r)
		return ;

	int pivot = partition(arr, l, r);
	if (pivot == k)
		return arr[pivot];
	else if (pivot > k)
		quickSelect(arr, l, pivot - 1, k);
	else if (pivot < k)
		quickSelect(arr, pivot +1, r, k);
}
int main() {
	int arr[100] = { 0 }, n, k, data;
	scanf("%d %d",&n,&k);
	for (int i = 0; i < n; i++)
		scanf("%d",&arr[i]);

	data=quickSelect(arr,0,n-1,k);
	printf("%d", data);
}