#include<stdio.h>
#include<stdlib.h>

typedef struct edgeNode {
	int origin;
	int destination;
	struct edgeNode* next;
}edgeNode;

typedef struct vertexNode {
	edgeNode* inEdges;
	edgeNode* outEdges;
	int inDegree;
	char name;
}vertexNode;

typedef struct Graph {
	vertexNode* Vertices;
	edgeNode* Edges;
}Graph;

Graph* G;
char* vertexName; //정점 이름 배열
int n, m; //정점, 간선
int* Queue; //진입차수 0인 정점 삽입할 큐
int* topOrder;
int front;
int rear;

edgeNode* getNode()
{
	edgeNode* newNode = (edgeNode*)malloc(sizeof(edgeNode));
	newNode->origin = 0;
	newNode->destination = 0;
	newNode->next = NULL;
	return newNode;
}
void initializeGraph()
{
	G = (Graph*)malloc(sizeof(Graph));
	G->Vertices = NULL;
	G->Edges = NULL;
}

//정점의 배열 인덱스 반환
int index(char vertexName)
{
	for (int i = 0; i <= n - 1; i++)
	{
		if (G->Vertices[i].name == vertexName)
			return i;
	}
}
//정점 삽입
void insertVertex(char vertexName, int index)
{
	G->Vertices[index].name = vertexName;
	G->Vertices[index].inEdges = getNode();
	G->Vertices[index].outEdges = getNode();
	G->Vertices[index].inDegree = 0;
	return;
}
//정점의 부착리스트에 간선 연결
void addFirst(edgeNode* header, int i)
{
	edgeNode* newNode = (edgeNode*)malloc(sizeof(edgeNode));
	newNode->origin = G->Edges[i].origin;
	newNode->destination = G->Edges[i].destination;

	newNode->next = header->next;
	header->next = newNode;
	return;
}
//방향간선 삽입
void insertDirectedEdge(char uName, char wName, int i)
{
	int u = index(uName);//u는 uName정점의 배열 인덱스
	int w = index(wName);//w는 wName정점의 배열 인덱스
	G->Edges[i].origin = u;
	G->Edges[i].destination = w;
	G->Edges[i].next = NULL;

	addFirst(G->Vertices[u].outEdges, i);
	addFirst(G->Vertices[w].inEdges, i);

	G->Vertices[w].inDegree++;
	return;
}
//그래프 구축
void buildGraph()
{
	initializeGraph();

	//정점 입력 및 삽입
	scanf("%d", &n);
	vertexName = (char*)malloc((n + 1) * sizeof(char));
	G->Vertices = (vertexNode*)malloc(n * sizeof(vertexNode));
	for (int i = 0; i < n; i++)
	{
		getchar();
		scanf("%c", &vertexName[i]);
	}
	for (int i = 0; i < n; i++)
	{
		insertVertex(vertexName[i], i);
	}

	//방향간선 입력 및 삽입
	scanf("%d", &m);
	G->Edges = (edgeNode*)malloc(m * sizeof(edgeNode));
	char uName, wName;
	for (int i = 0; i <= m - 1; i++)
	{
		getchar();
		scanf("%c %c", &uName, &wName);
		insertDirectedEdge(uName, wName, i);
	}
}


//큐 초기화
void freshQueue()
{
	for (int i = 0; i < n; i++)
	{
		Queue[i] = -1;
	}
}
void enqueue(int v)
{
	Queue[++rear] = v;
}

char dequeue()
{
	return Queue[++front];
}

int isEmpty()
{
	if (front == rear)return 1;
	else return 0;
}

void topologicalSort()
{
	int* in = (int*)malloc(n * sizeof(int)); //정점 i의 진입차수 저장
	freshQueue();

	for (int i = 0; i <= n - 1; i++)
	{
		in[i] = G->Vertices[i].inDegree;
		if (in[i] == 0)
		{
			enqueue(i);
		}
	}
	int t = 1;
	while (isEmpty() != 1)
	{
		int u = dequeue();
		topOrder[t] = u;
		t++;

		int cnt = 0;
		edgeNode* runner = G->Vertices[u].outEdges;
		while (runner->next != NULL) {
			int w = runner->next->destination;
			in[w] -= 1;
			if (in[w] == 0)
			{
				enqueue(w);
			}
			runner = runner->next;
		}
	}
	if (t <= n)
	{
		topOrder[0] = 0;
	}
	else
	{
		topOrder[0] = 1;
	}
	return;
}


int main()
{
	buildGraph();

	char* arr = (char*)malloc(n * sizeof(char));
	Queue = (int*)malloc(n * sizeof(int));
	topOrder = (int*)malloc((n + 1) * sizeof(int));
	topologicalSort();

	if (topOrder[0] == 0)
		printf("0");
	else
	{
		for (int i = 1; i <= n; i++)
		{
			printf("%c ", (G->Vertices[topOrder[i]].name));
		}
	}
}