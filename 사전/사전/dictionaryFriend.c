#include<stdio.h>
#include<stdlib.h>
int findElement(int l,int r,int index, char *arr) {
	int mid = (l + r) / 2;
	if (l == r)
		return l;
	if (arr[index] == 'N') {
		findElement(l, mid, index + 1, arr);
	}
	else {
		findElement(mid+1,r, index + 1, arr);
	}
}
int main() {
	int a, b, c, answer;
	char *arr;
	scanf("%d %d %d",&a,&b,&c);
	arr = (char*)malloc(sizeof(char)*(c+1));
	scanf("%s",arr);
	answer=findElement(a, b,0, arr);
	printf("%d",answer);
	free(arr);
}