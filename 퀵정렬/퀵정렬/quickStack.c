#include<stdio.h>
#include<stdlib.h>
int arr[100];
int top;
int stack[100];
int pop() {
	if (top == 0)
		return 0;
	else
		return stack[--top];
}
void push(int data) {
	stack[top++] = data;
}
int isStackEmpty() {
	if (top == 0)
		return 1;
	else
		return 0;
}
void quicksort(int arr[], int l,int r) {
	int q, toright, toleft,temp;
	push(r);
	push(l);
	while (!isStackEmpty()) {
		l = pop();
		r = pop();
		q = (l + r) / 2;
		toright = l;
		toleft = r - 1;
		temp = arr[q];
		arr[q] = arr[r];
		arr[r] = temp;
		if (l < r) {

			while (toright <= toleft) {
				while (toright <= toleft && arr[toright] <= arr[r])
					toright++;
				while (toright <= toleft && arr[toleft] >= arr[r])
					toleft--;
				if (toright < toleft) {
					temp = arr[toright];
					arr[toright] = arr[toleft];
					arr[toleft] = temp;
					
				}
			}

			temp = arr[toright];
			arr[toright] = arr[r];
			arr[r] = temp;
			push(r);
			push(toright + 1);
			push(toright - 1);
			push(l);

			for (int z = 1; z <= 11; z++) {
				printf("%d ", arr[z]);

			}
			printf("\n");

		}
	}

		
}
int main() {
	int N;
	scanf("%d",&N);
	for (int i = 1; i <=N; i++)
		scanf("%d",&arr[i]);

	top = 0;
	quicksort(arr,1,N);
	for (int i = 1; i <= N; i++)
		printf("%d ", arr[i]);
}