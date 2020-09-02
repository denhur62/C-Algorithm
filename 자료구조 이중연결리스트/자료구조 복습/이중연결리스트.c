#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	struct Node *next;
	struct Node *prev;
	char data;
}Node;
typedef struct List {
	struct Node *head;
	struct Node *tail;
}List;
//처음에 리스트 생성
List* listFirst() {
	List *list = (List*)malloc(sizeof(List));
	list->head = (Node*)malloc(sizeof(Node));
	list->tail = (Node*)malloc(sizeof(Node));
	list->head->next = list->tail;
	list->tail->prev = list->head;
	return list;
}
//연결해 나가는 과정
void listAdd(List *list, int index, char data) {
	Node *node = (Node*)malloc(sizeof(Node));
	Node *runner;
	runner = list->head;
	node->next = NULL;
	node->prev = NULL;
	node->data = data;
	if (list->head->next == list->tail) {
		if (index != 1) {
			printf("invalid position\n");
			free(node);
			return;
		}
		list->head->next = node;
		list->tail->prev = node;
		node->next = list->tail;
		node->prev = list->head;
	}
	else {
		if (index == 1) {
			node->next = runner->next;
			runner->next->prev = node;
			runner->next = node;
			node->prev = runner;
		}
		else {

			while (index > 1) {
				runner = runner->next;
				index--;
				if (runner== list->tail) {
					printf("invalid position\n");
					return;
				}
			}
				node->next = runner->next;
				runner->next->prev = node;
				runner->next = node;
				node->prev = runner;
			
		}
	}
}
// 리스트 삭제해 나가는 과정
void listRemove(List *list, int index) {
	Node *remove = NULL;
	Node *runner = list->head;

	if (index == 1) {
		if (list->head->next == list->tail) {
			printf("invalid position\n");
		}
		else {
			remove = runner->next;
			runner->next = remove->next;
			remove->next->prev = runner;
			free(remove);
		}
	}
	else {

		while (index > 1) {
			runner = runner->next;
			index--;
			if (runner->next ==list->tail) {
				printf("invalid position\n");
				return;
			}
			
		}
			remove = runner->next;
			runner->next = remove->next;
			remove->next->prev = runner;
			free(remove);
		

	}
}
//출력
void listCircle(List *list) {
	Node* horse = list->head;

	while (horse->next != list->tail) {
		horse = horse->next;
		printf("%c", horse->data);
	}
	printf("\n");
}
//해당하는 값 얻기
void listGet(List *list, int index) {
	Node *runner = list->head;
	if (index == 1 ) {
		if (runner->next != list->tail)
			printf("%c\n", runner->next->data);
		else
			printf("invalid position\n");

	}
	else {

		while (index > 0) {
			index--;
			runner = runner->next;
			if (runner == list->tail)
			{
				printf("invalid position\n");
				return;
			}
		}
		printf("%c\n", runner->data);
	}
}
void freeNode(List * list) {
	Node * cur = list->head;
	Node * tmp;
	while (cur !=list->tail) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}
int main() {
	List *list = NULL;
	int a;
	list = listFirst();
	scanf("%d", &a);
	getchar();
	while (a--) {
		char order, ch;
		int position;

		scanf("%c", &order);
		getchar();


		switch (order) {
		case 'A':
			scanf("%d %c", &position, &ch);
			getchar();

			listAdd(list, position, ch);
			break;

		case 'D':
			scanf("%d", &position);
			getchar();

			listRemove(list, position);
			break;

		case 'G':
			scanf("%d", &position);
			getchar();

			listGet(list, position);
			break;

		case 'P':

			listCircle(list);
			break;
		}
	}
	freeNode(list);
}