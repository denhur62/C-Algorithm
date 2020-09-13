#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	struct Node *next;
	int data;
}Node;
typedef struct Vertex {
	char vertexName;
	int indegree;
	struct Node *inEdge;
	struct Node *outEdge;
}Vertex;
typedef struct Edge {
	int destination;
	int start;
}Edge;
typedef struct Graph {
	struct Edge **edge;
	struct Vertex **vertex;
}Graph;
Graph *graph;
int n, m;
int *in, *topOrder, *Q,front,rear;
int dequeue() {
	return Q[++front];
}
void enqueue(int i) {
	Q[++rear] = i;
}
int isEmpty() {
	if (front == rear)
		return 1;
	else
		return 0;
}
Node* getNode(int i) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = i;
	newNode->next = NULL;
	return newNode;
}
void addFirst(Node *node, int i) {
	Node *newNode = getNode(i);
	newNode->next = node->next;
	node->next = newNode;
}
int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (graph->vertex[i]->vertexName == vName)
			return i;
	}
}
void insertDirectedEdge(char uName,char wName,int i) {
	int u, w;
	u = index(uName);
	w = index(wName);
	graph->edge[i]->start = u;
	graph->edge[i]->destination = w;
	addFirst(graph->vertex[u]->outEdge, i);
	addFirst(graph->vertex[w]->inEdge, i);
	graph->vertex[w]->indegree++;
}
void insertVertex(char vName,int i) {
	graph->vertex[i]->vertexName = vName;
	graph->vertex[i]->outEdge = getNode(-1);
	graph->vertex[i]->inEdge = getNode(-1);
	graph->vertex[i]->indegree = 0;
}
void buildGraph() {
	char vName,uName,wName;
	graph = (Graph*)malloc(sizeof(Graph));
	scanf("%d",&n);
	graph->vertex = (Vertex**)malloc(sizeof(Vertex*)*n);
	getchar();
	for (int i = 0; i < n; i++) {
		graph->vertex[i] = (Vertex*)malloc(sizeof(Vertex)*n);
		scanf("%c",&vName);
		getchar();
		insertVertex(vName, i);
	}
	graph->edge = (Edge**)malloc(sizeof(Edge*)*m);
	scanf("%d",&m);
	getchar();
	for (int i = 0; i < m; i++) {
		graph->edge[i] = (Edge*)malloc(sizeof(Edge));

		scanf("%c %c",&uName,&wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}

}
void topologicalSort() {
	int *in = (int*)malloc(n * sizeof(int));
	topOrder = (int*)malloc((n + 1) * sizeof(int));
	Q = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		in[i] = graph->vertex[i]->indegree;
		if (in[i] == 0)
			enqueue(i);
	}
	int t = 1;
	while (!isEmpty()) {
		int u = dequeue();
		topOrder[t] = u;
		t++;
		Node *Runner = graph->vertex[u]->outEdge->next;
		while (Runner != NULL) {

			int w = graph->edge[Runner->data]->destination;
			in[w] = in[w] - 1;
			if (in[w] == 0)
				enqueue(w);
			Runner = Runner->next;
		}

	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}
void freeGraph() {

	for (int i = 0; i<n; ++i) {
		
		Node *horse = graph->vertex[i]->outEdge->next;
		Node *horseBefore = graph->vertex[i]->outEdge;

		while (horse != NULL) {
			free(horseBefore);
			horseBefore = horse;
			horse = horse->next;
		}
		horse = graph->vertex[i]->inEdge->next;
		horseBefore = graph->vertex[i]->inEdge;
		while (horse != NULL) {
			free(horseBefore);
			horseBefore = horse;
			horse = horse->next;
		}
		free(graph->vertex[i]);
	}

	//free(graph->edge);
	//free(graph->vertex);
	free(graph);
}
int main() {
	buildGraph();

	topologicalSort();

	if (topOrder[0] == 0)
		printf("0");
	else {
		for (int i = 1; i <= n; ++i)
			printf("%c ", graph->vertex[topOrder[i]]->vertexName);
	}

	freeGraph();

}