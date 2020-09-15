#include<stdio.h>
#include<stdlib.h>
#define MAX 30000

typedef struct Node {
	int vertexNum;
	int distance;
}Node;
typedef struct Edge {
	struct Node *next;
	int EndvertexNum;
	int weight;
}Edge;
typedef struct Vertex {
	struct Edge *includeEdge;
	int vertexNum;
	int d;
}Vertex;
typedef struct Graph {
	struct Vertex **vertex;
}Graph;

int n, m, s;
Graph *G;
Node *queue;
int queueSize;
void nodeSwap(Node *a,Node *b) {
	Node temp = *a;
	*a = *b;
	*b = temp;
}
void downHeap(int index) {
	while (index <= queueSize / 2) {
		int child = index * 2;
		if (child + 1 <= queueSize && queue[child].distance > queue[child + 1].distance)
			child++;
		if (queue[child].distance < queue[index].distance) {
			nodeSwap(&queue[child], &queue[index]);
			index = child;
		}
		else
			break;
	}
}
void buildHeap() {
	for (int i = queueSize/2; i >= 1; i--)
		downHeap(i);
}
void enqueue(int vertexNum,int d) {
	Node newNode;
	newNode.distance = d;
	newNode.vertexNum = vertexNum;
	queue[++queueSize] = newNode;
}
int removeMin() {
	Node minNode = queue[1];
	queue[1] = queue[queueSize--];
	downHeap(1);
	return minNode.vertexNum;
}
int isEmpty() {
	return queueSize == 0;
}
int isInQueue(int vertexNum) {
	for (int i = 1; i <= queueSize; i++) {
		if (queue[i].vertexNum == vertexNum)
			return 1;
	}
	return 0;
}
void replaceKey(int vertexNum,int weight) {
	for (int i = 1; i <= queueSize; i++) {
		if (queue[i].vertexNum == vertexNum)
			queue[i].distance = weight;
	}
	buildHeap();
}
Edge *createEdge(int EndvertexNum, int weight) {
	Edge *newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->next = NULL;
	newEdge->EndvertexNum = EndvertexNum;
	newEdge->weight = weight;
	return newEdge;
}
Vertex *createVertex(int vertexNum) {
	Vertex *newVertex = (Vertex*)malloc(sizeof(Vertex));
	newVertex->vertexNum = vertexNum;
	newVertex->includeEdge = createEdge(0, 0);
	return newVertex;
}
void addFirst(Edge *list, int endVertexNum,int weight) {
	Edge *newEdge = createEdge(endVertexNum, weight);
	newEdge->next = list->next;
	list->next = newEdge;
}
void insertEdge(int v, int u, int weight) {
	addFirst(G->vertex[v]->includeEdge, u, weight);
	addFirst(G->vertex[u]->includeEdge, v, weight);
}
void createGraph() {
	G = (Graph*)malloc(sizeof(Graph));
	G->vertex = (Vertex**)malloc((n + 1) * sizeof(Vertex*));
	for (int i = 1; i <= n; ++i)
		G->vertex[i] = createVertex(i);

	int u, v, weight;
	for (int i = 0; i<m; ++i) {
		scanf("%d%d%d", &u, &v, &weight);
		insertEdge(u, v, weight);
	}
	
	queue = (Node*)malloc((n + 1) * sizeof(Node));
}
int getWeight(int v,int u) {
	Edge *Runner = G->vertex[v]->includeEdge->next;
	while (Runner != NULL) {
		if (Runner->EndvertexNum == u)
			return Runner->weight;
		Runner = Runner->next;
	}
}
void DijkstraShortestPaths() {
	for (int i = 1; i <= n; i++)
		G->vertex[i]->d = MAX;

	G->vertex[s]->d = 0;
	for (int i = 1; i <= n; ++i)
		enqueue(i, G->vertex[i]->d);

	buildHeap();

	while (!isEmpty()) {
		int u = removeMin();
		Edge *Runner = G->vertex[u]->includeEdge->next;
		while (Runner != NULL) {
			int z = Runner->EndvertexNum;

			if (isInQueue(z)) {
				if (G->vertex[u]->d + getWeight(u, z) < G->vertex[z]->d) {
					G->vertex[z]->d = G->vertex[u]->d + getWeight(u, z);
					replaceKey(z, G->vertex[z]->d);
				}
			}
			Runner = Runner->next;
		}
	}
}

void freeGraph() {

	for (int i = 1; i <= n; ++i) {

		Vertex *vertex = G->vertex[i];

		Edge *horseBefore = vertex->includeEdge;
		Edge *horse = vertex->includeEdge->next;

		while (horse != NULL) {
			free(horseBefore);

			horseBefore = horse;
			horse = horse->next;
		}

		free(vertex);
	}

	free(G);
	free(queue);
}

int main() {

	scanf("%d%d%d", &n, &m, &s);

	createGraph();

	DijkstraShortestPaths();

	for (int i = 1; i <= n; ++i)
		if (i != s && G->vertex[i]->d != MAX)
			printf("%d %d\n", G->vertex[i]->vertexNum, G->vertex[i]->d);

	freeGraph();
}