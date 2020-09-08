#include<stdio.h>

int graph[7][7];

void createGraph() {
	for (int i = 1; i <= 6; ++i) {
		for (int j = 1; j <= 6; j++) {
			graph[i][j] = 0;
		}
	}
}

void printNode(int nodeNumber) {

	// 예외 처리 : 없는 정점일 경우 종료 
	if (nodeNumber >= 7 || nodeNumber <= 0) {
		printf("-1\n");
		return;
	}

	for (int i = 1; i <= 6; ++i)
		if (graph[nodeNumber][i] != 0)
			printf(" %d %d", i, graph[nodeNumber][i]);

	printf("\n");
}

void modifyEdge(int a, int b, int w) {

	// 예외 처리 : 없는 정점일 경우 종료 
	if (a >= 7 || a <= 0 || b >= 7 || b <= 0) {
		printf("-1\n");
		return;
	}

	graph[a][b] = w;
	graph[b][a] = w;
}

void graphSetting() {

	modifyEdge(1, 2, 1);
	modifyEdge(1, 3, 1);
	modifyEdge(1, 4, 1);
	modifyEdge(1, 6, 2);

	modifyEdge(2, 3, 1);

	modifyEdge(3, 5, 4);

	modifyEdge(5, 5, 4);
	modifyEdge(5, 6, 3);
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
			printNode(nodeNumber);
			break;

			// 간선 변경 
		case 'm':
			scanf("%d%d%d", &a, &b, &w);
			getchar();

			modifyEdge(a, b, w);
			break;

			// 종료
		case 'q':
			return 0;
		}
	}
}

