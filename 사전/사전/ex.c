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
char* vertexName; //���� �̸� �迭
int n, m; //����, ����
int* Queue; //�������� 0�� ���� ������ ť
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

//������ �迭 �ε��� ��ȯ
int index(char vertexName)
{
	for (int i = 0; i <= n - 1; i++)
	{
		if (G->Vertices[i].name == vertexName)
			return i;
	}
}
//���� ����
void insertVertex(char vertexName, int index)
{
	G->Vertices[index].name = vertexName;
	G->Vertices[index].inEdges = getNode();
	G->Vertices[index].outEdges = getNode();
	G->Vertices[index].inDegree = 0;
	return;
}
//������ ��������Ʈ�� ���� ����
void addFirst(edgeNode* header, int i)
{
	edgeNode* newNode = (edgeNode*)malloc(sizeof(edgeNode));
	newNode->origin = G->Edges[i].origin;
	newNode->destination = G->Edges[i].destination;

	newNode->next = header->next;
	header->next = newNode;
	return;
}
//���Ⱓ�� ����
void insertDirectedEdge(char uName, char wName, int i)
{
	int u = index(uName);//u�� uName������ �迭 �ε���
	int w = index(wName);//w�� wName������ �迭 �ε���
	G->Edges[i].origin = u;
	G->Edges[i].destination = w;
	G->Edges[i].next = NULL;

	addFirst(G->Vertices[u].outEdges, i);
	addFirst(G->Vertices[w].inEdges, i);

	G->Vertices[w].inDegree++;
	return;
}
//�׷��� ����
void buildGraph()
{
	initializeGraph();

	//���� �Է� �� ����
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

	//���Ⱓ�� �Է� �� ����
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


//ť �ʱ�ȭ
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
	int* in = (int*)malloc(n * sizeof(int)); //���� i�� �������� ����
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