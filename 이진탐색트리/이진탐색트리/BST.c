#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
typedef struct node
{
	struct node *LChild;
	struct node *Parent;
	int key;
	struct node *RChild;
}node;
node *getnode() {
	node *newnode = (node*)malloc(sizeof(node));
	newnode->LChild = NULL;
	newnode->RChild = NULL;
	return newnode;
}
bool isExternal(node *w) {
	if (w->LChild == NULL && w->RChild == NULL)
		return true;
	else
		return false;
}
bool isInternal(node *w) {
	if (w->LChild != NULL || w->RChild != NULL)
		return true;
	else
		false;
}
node *sibling(node *w) {
	if (w->Parent == NULL)
		return NULL;
	if (w->Parent->LChild = w)
		return w->Parent->RChild;
	else
		return w->Parent->LChild;

}
node *inOrderSucc(node *w) {
	w = w->RChild;
	if (isExternal(w))
		return NULL;
	while (w->LChild != NULL)
		w = w->LChild;
	return w;
}
node *treeSearch(node *w, int k) {
	if (isExternal(w))
		return w;
	if (w->key == k)
		return w;
	if (w->key < k)
		treeSearch(w->RChild, k);
	else
		treeSearch(w->LChild, k);

}
void reduceExternal(node *z) {

	node *g;
	node *w = z->Parent;
	node *zs = sibling(z);
	if (w->Parent == NULL)
		zs->RChild = NULL;
	else
	{
		g = w->Parent;
		zs->Parent = g;
		if (w == g->LChild)
			g->LChild = zs;
		else if (w == g->RChild)
			g->RChild = zs;
	}
	free(z);
	free(w);

}
void removeElement(node *tree, int key) 
{
	node *w, *z, *y;
	int e;

	w = treeSearch(tree, key);
	if (isExternal(w))
		return;
	e = w->key;
	z = w->LChild;
	if (!isExternal(z))
		z = w->RChild;
	if (isExternal(z))
		reduceExternal(z);
	else
	{
		z = inOrderSucc(w);
		y = z->Parent;
		w->key = y->key;
		reduceExternal(z);
	}
}

void externalNode(node *e) {
	node *left = getnode();
	node *right = getnode();
	left->Parent = e;
	right->Parent = e;
	left->LChild = NULL, left->RChild = NULL;
	right->RChild = NULL, right->RChild = NULL;
	e->LChild = left;
	e->RChild = right;
}
void insertItem(node *w,int k) {

	node *e = treeSearch(w, k);
	if (!isExternal(e))
		return;
	else {
		e->key = k;
		externalNode(e);
	}
}
int findElement(node *w, int k) {

	node *e = treeSearch(w, k);
	if (isExternal(e))
		return ;
	else
		return e->key;
}
void printpreorder(node *w) {

	if (!isExternal(w)) {
		printf(" %d",w->key);
		printpreorder(w->LChild);
		printpreorder(w->RChild);
	}
}
void freeNode(node *w) {

	if ((w->LChild)!=NULL)
		freeNode(w->LChild);
	if ((w->RChild)!=NULL)
		freeNode(w->RChild);
	free(w);
}
int main()
{
	int key, x;
	char alp, res = NULL;
	node *root;

	root = getnode();

	scanf("%c", &alp);

	while (alp != 'q')
	{
		if (alp == 'i')
		{
			scanf(" %d", &key);
			insertItem(root, key);
		}
		else if (alp == 'd')
		{
			scanf(" %d", &key);

			if (key == findElement(root, key)) {
				removeElement(root, key);
				printf("%d\n", key);
			}
			else
				printf("X\n");
		}
		else if (alp == 's')
		{
			scanf(" %d", &key);
			x = findElement(root, key);
			if (x == key)
				printf("%d\n", key);
			else
				printf("X\n");
		}
		else if (alp == 'p')
		{
			printpreorder(root);
			printf("\n");
		}
		scanf(" %c", &alp);
	}
	freeNode(root);
}