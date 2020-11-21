#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define EDGE_HEADER INT_MIN
#define MAX_STACK_SIZE 100
typedef enum { false, true } bool;

typedef struct Edge {
	struct Edge *next;
	int connectedNodeNumber;
} Edge;

typedef struct Node {
	int nodeNumber;
	Edge *incidenceLists;
	int routineNumber;
} Node;

// 정점의 개수, 간선의 개수, 정점 시작 번호 
int n, m, s,count=0,row=0,col=0;
bool *visited;
Node **graph;
int answer[10000][10000] = { 0 };
int stack[MAX_STACK_SIZE];
int top = -1;
Edge* createEdge(int nodeNumber) {
	Edge *newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->next = NULL;
	newEdge->connectedNodeNumber = nodeNumber;

	return newEdge;
}

void createGraph() {

	graph = (Node*)malloc((n + 1) * sizeof(Node*));
	visited = (bool*)malloc((n + 1) * sizeof(bool));

	for (int i = 1; i <= n; ++i) {
		graph[i] = (Node*)malloc(sizeof(Node));
		graph[i]->incidenceLists = createEdge(EDGE_HEADER);
		graph[i]->nodeNumber = i;
		graph[i]->routineNumber = 0;
		visited[i] = false;
	}
}

void insertEdge(int a, int b) {

	Edge *horse = graph[a]->incidenceLists;

	// 지금 horse 다음에 추가하기
	// 시작이 빈칸 헤더
	while (horse->next != NULL) {
		if (horse->next->connectedNodeNumber > b)
			break;

		horse = horse->next;
	}

	Edge *newEdge = createEdge(b);
	Edge *nextEdge = horse->next;

	horse->next = newEdge;
	newEdge->next = nextEdge;

	//// b 에도 추가 
	//horse = graph[b]->incidenceLists;

	//while (horse->next != NULL) {
	//	if (horse->next->connectedNodeNumber > a)
	//		break;

	//	horse = horse->next;
	//}

	//newEdge = createEdge(a);
	//nextEdge = horse->next;

	//horse->next = newEdge;
	//newEdge->next = nextEdge;
}
void push(int value) {
	if (top >= MAX_STACK_SIZE - 1)
		printf("스택이 가득 찼습니다.");
	else
		stack[++top] = value;
}

int pop() {
	if (top<0)
		printf("스택이 비었습니다.");
	else
		return stack[top--];
}

int DFS(int nodeNumber) {

	Node *node = graph[nodeNumber];
	node->routineNumber = ++count;
	push(nodeNumber);

	Edge *edgeLists = node->incidenceLists->next;
	int parent = node->routineNumber;

	while (edgeLists != NULL) {
		int currentNodeNumber = edgeLists->connectedNodeNumber;
		
		if (graph[edgeLists->connectedNodeNumber]->routineNumber == 0) {
			int b = DFS(edgeLists->connectedNodeNumber);
			if (parent > b)
				parent = b;
		}
		else if (!visited[edgeLists->connectedNodeNumber]) {
			if (parent > graph[edgeLists->connectedNodeNumber]->routineNumber)
				parent = graph[edgeLists->connectedNodeNumber]->routineNumber;
		}
		edgeLists = edgeLists->next;
	}

	if (parent == node->routineNumber) {

		while (1) {
			int t = stack[top];
			pop();
			answer[row][col++] = t;
			visited[t] = true;
			if (t == nodeNumber)
				break;
		}
		answer[row][col++] = -1;
		row++;
		col = 0;
	}
	return parent;
}


int main() {

	scanf("%d%d", &n, &m);
	createGraph();

	int edgeNum1, edgeNum2;

	for (int i = 0; i<m; ++i) {
		scanf("%d%d", &edgeNum1, &edgeNum2);
		insertEdge(edgeNum1, edgeNum2);
	}
	for (int i = 1; i <= n;i++) {
		DFS(i);
	}
	printf("%d\n",row);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ", answer[i][j]);
		}
		printf("\n");
	}

	
}
//7 9
//1 4
//4 5
//5 1
//1 6
//6 7
//2 7
//7 3
//3 7
//7 2