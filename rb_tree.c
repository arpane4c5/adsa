// RB Tree Implementation: Create, insert, delete,

#include<stdio.h>
#include<stdlib.h>

enum nodeColor{
	RED,
	BLACK
};

struct rbNode{
	int data;
	int color;
	struct rbNode *link[2];
	
};


struct rbNode * root = NULL;

struct rbNode * createNode(int data)
{
	struct rbNode * newnode;
	newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
	newnode -> data = data;
	newnode -> color = RED;
	newnode -> link[0] = newnode -> link[1] = NULL;
	return newnode;
}

void preorder(struct rbNode *T)
{
	if (T!=NULL)
	{
		printf("%d (color is %d)\n", T->data, T->color);
		preorder(T->link[0]);
		preorder(T->link[1]);
	}
}

void insertion(int data)
{
	struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
	int dir[98], ht=0, index;
	ptr = root;
	if (!root)
	{
		root = createNode(data);
		return;
	}

	stack[ht] = root;
	dir[ht++] = 0;
}

void main()
{
	node *root = NULL;

	printf("RB - Tree Operations : \n");
	printf("1. Create \n2. Insert node.\n3. Delete node\n4. Search node.");

}