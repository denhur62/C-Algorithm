#include<stdio.h>
#include<stdlib.h>
#define MAX 30000

typedef struct Edge {
	int weight;
	int origin;
	int opposite;
} Edge;

typedef struct Graph {
	Edge *edgeList;
	int *distance;
} Graph;

int n, m, s;
Graph* G;

// 메모리 할당
void createGraph() {

	G = (Graph*)malloc(sizeof(Graph));
	G->edgeList = (Edge*)malloc(m * sizeof(Edge));
	G->distance = (int*)malloc((n + 1) * sizeof(int));

	for (int i = 0; i<m; ++i) {
		Edge *edge = &G->edgeList[i];
		scanf("%d", &edge->origin);
		scanf("%d", &edge->opposite);
		scanf("%d", &edge->weight);
	}
}

int min(int a, int b) {

	if (a < b)
		return a;
	return b;
}

void BellmanFordShortestPaths() {

	// 1
	for (int i = 1; i <= n; ++i)
		G->distance[i] = MAX;

	// 2
	G->distance[s] = 0;

	// 3 
	for (int i = 1; i <= n - 1; ++i) {
		for (int j = 0; j<m; ++j) {

			int u = G->edgeList[j].origin;
			int z = G->edgeList[j].opposite;

			if (G->distance[u] != MAX)
				G->distance[z] = min(G->distance[z], G->distance[u] + G->edgeList[j].weight);
		}
	}
}

// 메모리 반환 함수 
void freeGraph() {

	free(G->distance);
	free(G->edgeList);
	free(G);
}

int main() {

	scanf("%d%d%d", &n, &m, &s);

	createGraph();

	BellmanFordShortestPaths();

	for (int i = 1; i <= n; ++i)
		if (i != s && G->distance[i] != MAX)
			printf("%d %d\n", i, G->distance[i]);

	freeGraph();
}

