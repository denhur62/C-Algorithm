#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	char elem;
	struct Node * prev;
	struct Node * next;
}Node;
typedef struct List {
	struct Node * header;
	struct Node * footer;
}List;
Node * getNode(char data) {
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}
void initList(List * list) {//초기화
	list->header = NULL;
	list->footer = NULL;
	list->header = getNode(NULL);
	list->footer = getNode(NULL);
	list->header->next = list->footer;
	list->footer->prev = list->header;
}
Node * get_entry(List * list, int position) {//position 앞 노드 불러오기
	Node * cur = list->header;
	int cnt = 1;
	while (cur != list->footer) {
		if (cnt == position)
			break;
		cnt++;
		cur = cur->next;
	}
	return cur;

}
void add(List * list, int position, char item) {//add
	Node * cur = get_entry(list, position);
	Node * newNode = getNode(item);
	newNode->next = cur->next;
	cur->next->prev = newNode;
	cur->next = newNode;
	newNode->prev = cur;
}
void print(List * list) {//print
	Node * cur = list->header->next;
	while (cur != list->footer) {
		printf("%c", cur->elem);
		cur = cur->next;
	}
	printf("\n");
}
void delete(List * list, int position) {//delete
	Node * cur = get_entry(list, position);
	Node * del = cur->next;
	cur->next = del->next;
	del->next->prev = cur;
	free(del);
}
int countNode(List * list) {
	Node * cur = list->header->next;
	int cnt = 0;
	while (cur != list->footer) {
		cnt++;
		cur = cur->next;
	}
	return cnt;
}
void freeNode(List * list) {
	Node * cur = list->header;
	Node * tmp;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}
int main() {
	List list;
	int n, i;
	int position;
	char order, item, data;
	initList(&list);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		getchar();
		scanf("%c", &order);
		if (order == 'A') {
			scanf("%d %c", &position, &item);
			if (countNode(&list) + 1 >= position)
				add(&list, position, item);
			else
				printf("invalid position\n");
		}
		else if (order == 'P') {
			print(&list);
		}
		else if (order == 'D') {
			scanf("%d", &position);
			if (countNode(&list) == 0)
				printf("invalid position\n");
			else if (countNode(&list) < position)
				printf("invalid position\n");
			else
				delete(&list, position);
		}
		else if (order == 'G') {
			scanf("%d", &position);
			if (countNode(&list) == 0)
				printf("invalid position\n");
			else if (countNode(&list) < position)
				printf("invalid position\n");
			else
				printf("%c\n", get_entry(&list, position + 1)->elem);
		}
	}
	freeNode(&list);
}