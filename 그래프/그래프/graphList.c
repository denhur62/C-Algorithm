#include<stdio.h>
#include<stdlib.h>
typedef struct Edge {
	struct Edge *next;
	int connectedNodeNumber;
	int weight;
} Edge;

typedef struct Node {
	int nodeNumber;
	Edge *incidenceLists;
} Node;
Node *graph[7];
Edge * createEdge(int NodeNumber,int weight) {
	Edge *newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->next = NULL;
	newEdge->weight = weight;
	newEdge->connectedNodeNumber = NodeNumber;
	return newEdge;
}
void createGraph() {
	for (int i = 1; i < 7; i++) {
		graph[i] = (Node*)malloc(sizeof(Node));
		graph[i]->incidenceLists = createEdge(0,0);
		graph[i]->nodeNumber = i;
	}
}
void insertEdge(int a, int b, int w) {
	Edge *newEdge = createEdge(b, w);
	Edge *Runner = graph[a]->incidenceLists;
	Edge *before = NULL;
	while (Runner != NULL) {
		if (Runner->connectedNodeNumber == b)
			Runner->weight = w;
		else if (Runner->connectedNodeNumber > b)
			break;
		before = Runner;
		Runner = Runner->next;
	}
	newEdge->next = Runner;
	before->next = newEdge;

}
void removeEdge(int a, int b) {
	Edge *Runner = graph[a]->incidenceLists;
	Edge *before = Runner;
	while (Runner != NULL) {
		if (Runner->connectedNodeNumber == b)
			break;
		else if (Runner->connectedNodeNumber > b)
			return;
		before = Runner;
		Runner = Runner->next;
	}
	if (Runner == NULL)
		return;
	before->next = Runner->next;
	free(Runner);
}
void printNode(int nodeNumber) {
	Edge *Runner = graph[nodeNumber]->incidenceLists->next;
	while (Runner != NULL) {
		printf(" %d %d", Runner->connectedNodeNumber, Runner->weight);
		Runner = Runner->next;
	}
	printf("\n");

}
void graphSetting() {
	insertEdge(1, 2, 1);	insertEdge(2, 1, 1);
	insertEdge(1, 3, 1);	insertEdge(3, 1, 1);
	insertEdge(1, 4, 1);	insertEdge(4, 1, 1);
	insertEdge(1, 6, 2);	insertEdge(6, 1, 2);

	insertEdge(2, 3, 1);	insertEdge(3, 2, 1);

	insertEdge(3, 5, 4);	insertEdge(5, 3, 4);

	insertEdge(5, 5, 4);
	insertEdge(5, 6, 3);	insertEdge(6, 5, 3);
}
int exceptionCheck(int a, int b) {
	// 예외 처리 : 없는 정점일 경우 
	if (a >= 7 || a <= 0 || b >= 7 || b <= 0) {
		printf("-1\n");
		return -1;
	}
	return 1;
}
void freeGraph() {
	Edge *before = NULL;
	for (int i = 1; i < 7; i++) {
		Edge *Runner = graph[i]->incidenceLists;
		while (Runner != NULL) {
			before = Runner;
			Runner = Runner->next;
			free(before);
		}

		free(graph[i]);
	}
}
int main() {

	// 초기 설정
	createGraph();
	graphSetting();

	char order;
	int nodeNumber, a, b, w;

	while (1) {

		scanf("%c", &order);
		getchar();

		switch (order) {

			// 노드 인쇄 
		case 'a':
			scanf("%d", &nodeNumber);
			getchar();

			// 존재하는 정점인지 확인 
			if (exceptionCheck(nodeNumber, nodeNumber) == -1)
				break;

			printNode(nodeNumber);
			break;

			// 간선 변경 
		case 'm':
			scanf("%d%d%d", &a, &b, &w);
			getchar();

			// 존재하는 정점인지 확인 
			if (exceptionCheck(a, b) == -1)
				break;

			if (w == 0) {
				removeEdge(a, b);
				removeEdge(b, a);
			}
			else {
				insertEdge(a, b, w);
				insertEdge(b, a, w);
			}

			break;

			// 종료
		case 'q':
			// 메모리 반환 후 종료 
			freeGraph();
			return 0;
		}
	}
}