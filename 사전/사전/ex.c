#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX INT_MAX

typedef enum { false, true } bool;

typedef struct Node {
	int vertexNum;
	int distance;
} Node;

typedef struct Edge {
	struct Edge *next;
	int oppositeVertexNum;
	int weight;
} Edge;

typedef struct Vertex {
	int vertexNum;
	int d;
	Edge *incidentEdges;
	Edge *parent;
} Vertex;

typedef struct Graph {
	Vertex **vertices;
} Graph;

int n, m;
Graph *G;

int* MST;
int indexOfMST = 0;
int totalWeight = 0;

// 큐 관련 
Node *queue;
int queueSize;

void nodeSwap(Node *a, Node *b) {
	Node temp = *a;
	*a = *b;
	*b = temp;
}

void downHeap(int index) {

	while (index <= queueSize / 2) {
		int child = index * 2;
		if (child + 1 <= queueSize && queue[child].distance < queue[child + 1].distance)
			child++;

		if (queue[index].distance < queue[child].distance) {
			nodeSwap(&queue[index], &queue[child]);
			index = child;
		}
		else
			break;
	}
}

void buildHeap() {

	for (int i = queueSize / 2; i >= 1; --i)
		downHeap(i);
}

void enqueue(int vertexNum, int distance) {

	Node newNode;
	newNode.vertexNum = vertexNum;
	newNode.distance = distance;

	queue[++queueSize] = newNode;
}

int removeMin() {

	Node minNode = queue[1];
	int minVertexNum = minNode.vertexNum;

	MST[indexOfMST++] = minVertexNum;
	totalWeight += minNode.distance;

	queue[1] = queue[queueSize--];
	downHeap(1);

	return minVertexNum;
}

bool isEmpty() {
	return queueSize == 0;
}

bool isInQueue(int vertexNum) {

	for (int i = 1; i <= queueSize; ++i) {
		if (queue[i].vertexNum == vertexNum)
			return true;
	}

	return false;
}

void replaceKey(int vertexNum, int weight) {

	for (int i = 1; i <= queueSize; ++i) {
		if (queue[i].vertexNum == vertexNum)
			queue[i].distance = weight;
	}

	buildHeap();
}

// 큐 관련 끝 

Edge* createEdge(int oppositeVertexNum, int weight) {

	Edge *newEdge = (Edge*)malloc(sizeof(Edge));

	newEdge->next = NULL;
	newEdge->oppositeVertexNum = oppositeVertexNum;
	newEdge->weight = weight;

	return newEdge;
}

Vertex* createVertex(int vertexNum) {

	Vertex *newVertex = (Vertex*)malloc(sizeof(Vertex));

	newVertex->vertexNum = vertexNum;
	newVertex->parent = NULL;
	// 헤더 
	newVertex->incidentEdges = createEdge(0, 0);

	return newVertex;
}

void addFirst(Edge* list, int oppositeVertexNum, int weight) {

	Edge *newEdge = createEdge(oppositeVertexNum, weight);

	newEdge->next = list->next;
	list->next = newEdge;
}

void insertDirectedEdge(int v, int u, int weight) {

	addFirst(G->vertices[v]->incidentEdges, u, weight);
	addFirst(G->vertices[u]->incidentEdges, v, weight);
}

void createGraph() {

	// 정점의 수
	scanf("%d%d", &n, &m);

	G = (Graph*)malloc(sizeof(Graph));

	G->vertices = (Vertex**)malloc((n + 1) * sizeof(Vertex*));
	for (int i = 1; i <= n; ++i)
		G->vertices[i] = createVertex(i);

	int u, v, weight;
	for (int i = 0; i<m; ++i) {
		scanf("%d%d%d", &u, &v, &weight);
		insertDirectedEdge(u, v, weight);
	}

	MST = (int*)malloc(n * sizeof(int));

	// 큐 생성
	queue = (Node*)malloc((n + 1) * sizeof(Node));
}

int getWeight(int v, int u) {

	Edge *horse = G->vertices[v]->incidentEdges->next;

	while (horse != NULL) {

		if (horse->oppositeVertexNum == u)
			return horse->weight;

		horse = horse->next;
	}
}

void primJamik() {

	// 1
	for (int i = 1; i <= n; ++i) {
		G->vertices[i]->d = MAX;
		G->vertices[i]->parent = NULL;
	}

	// 2,3
	G->vertices[1]->d = 0;

	// 4
	for (int i = 1; i <= n; ++i)
		enqueue(i, G->vertices[i]->d);

	// 힙 구조화 
	buildHeap();

	// 5

	while (!isEmpty()) {

		int u = removeMin();

		// 헤더 건너 띄고 
		Edge *e = G->vertices[u]->incidentEdges->next;
		while (e != NULL) {

			int z = e->oppositeVertexNum;

			if (isInQueue(z) && getWeight(u, z) > G->vertices[z]->d) {

				G->vertices[z]->d = getWeight(u, z);
				G->vertices[z]->parent = e;

				replaceKey(z, getWeight(u, z));
			}

			e = e->next;
		}
	}
}

void freeGraph() {

	for (int i = 1; i <= n; ++i) {

		Vertex *vertex = G->vertices[i];

		Edge *horseBefore = vertex->incidentEdges;
		Edge *horse = vertex->incidentEdges->next;

		while (horse != NULL) {
			free(horseBefore);

			horseBefore = horse;
			horse = horse->next;
		}

		free(vertex);
	}

	free(G);
	free(MST);
	free(queue);
}

int main() {

	createGraph();

	primJamik();

	for (int i = 0; i<n; ++i)
		printf(" %d", MST[i]);
	printf("\n");

	printf("%d", totalWeight);

	freeGraph();
}