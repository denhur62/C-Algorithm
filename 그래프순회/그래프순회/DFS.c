#include<stdio.h>
#include<stdlib.h>
typedef struct Edge {
	struct Edge *next;
	int nodeNumber;
}Edge;
typedef struct Node {
	int nodeNumber;
	int visited;
	Edge *list;
}Node;
Node **graph;
Edge *createEdge(int nodeNumber) {
	Edge *newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->next = NULL;
	newEdge->nodeNumber = nodeNumber;
}
void createGraph(int n ) {
	graph = (Node**)malloc(sizeof(Node*)*(n+1));
	for (int i = 1; i <= n; i++) {
		graph[i] = (Node*)malloc(sizeof(Node));
		graph[i]->nodeNumber = i;
		graph[i]->list = createEdge(0);
		graph[i]->visited = 0;
	}
}
void insertEdge(int a, int b) {
	Edge *runner = graph[a]->list;
	Edge *before = runner;
	Edge *newEdge = createEdge(b);
	while (runner != NULL) {
		if (runner->nodeNumber > b)
			break;
		before = runner;
		runner = runner->next;
	}
	before->next = newEdge;
	newEdge->next = runner;

}
void DFS(int start) {

	graph[start]->visited = 1;
	printf("%d\n", graph[start]->nodeNumber);
	Edge *runner = graph[start]->list->next;
	int visited;
	while (runner != NULL) {
		visited= runner->nodeNumber;
		if (graph[visited]->visited == 0)
			DFS(visited);
		runner = runner->next;
	}
}
void freeGraph(int n) {
	Edge *before = NULL;
	for (int i = 1; i <= n; ++i) {

		Edge *runner = graph[i]->list;
		Edge *next = runner->next;
		while (next != NULL) {
			free(runner);
			runner = next;
			next = next->next;
		}
		free(graph[i]);
	}
	free(graph);
}
int main() {
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	createGraph(n);

	int edgeNum1, edgeNum2;

	for (int i = 0; i<m; ++i) {
		scanf("%d%d", &edgeNum1, &edgeNum2);
		insertEdge(edgeNum1, edgeNum2);
		insertEdge(edgeNum2, edgeNum1);
	}

	DFS(s);

	freeGraph(n);
}