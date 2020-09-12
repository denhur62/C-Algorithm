#include<stdio.h>
#include<stdlib.h>
int **graph;
int *visited;
int *queue;
int rear, front;
int isEmpty() {
	if (front == rear)
		return 1;
	else
		return 0;
}
void enqueue(int i) {
	queue[++rear] = i;
}
int dequeue() {
	return queue[++front];
}
void BFS(int start,int n) {
	enqueue(start);
	visited[start] = 1;
	while (!isEmpty()) {
		int nodeStart = dequeue();
		printf("%d\n", nodeStart);
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0 && graph[nodeStart][i] == 1) {
				visited[i] = 1;
				enqueue(i);
			}

		}
	}
}
void insertGraph(int a,int b) {
	graph[a][b] = 1;
	graph[b][a] = 1;
}
void setting(int n) {
	rear = 0, front = 0;
	graph = (int**)malloc(sizeof(int*)*(n+1));
	visited = (int*)malloc(sizeof(int)*(n + 1));
	queue = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1; i <= n; i++) {
		graph[i] = (int*)malloc(sizeof(int)*(n + 1));
		visited[i] = 0;
		for (int j = 1; j <= n; j++) {
			graph[i][j] = 0;
		}
	}

}
void freeGraph(int n) {

	for (int i = 1; i <= n; ++i)
		free(graph[i]);

	free(graph);
	free(visited);
}
int main() {
	int n, m, s,a,b;
	scanf("%d %d %d",&n,&m,&s);
	setting(n);
	for (int i = 0; i < m; i++) {
		scanf("%d %d",&a,&b);
		insertGraph(a, b);
	}
	BFS(s,n);
	freeGraph(n);
}