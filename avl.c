#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left, *right;
	int ht;
}node;


node *insert(node *, int);
node *delete(node *, int);
void preorder(node *);
void inorder(node *);
int height(node *);
node *rotate_right(node *);
node *rotate_left(node *);
node * RR(node *);
node * LL(node *);
node * RL(node *);
node * LR(node *);
int balance_factor(node *);



int main()
{
	node * root = NULL;
	int x, n, choice, i;

	do 
	{
		printf("AVL Operations\n");
		printf("1. Create\n2. Insert \n3. Delete \n4. Display Preorder\n5. Display Inorder\n6. Exit \n");
		printf("Enter you choice :: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
					printf("\nEnter no. of elements : ");
					scanf("%d", &n);
					printf("Enter elements :\n");
					root = NULL;
					for(i = 0; i<n; i++)
					{
						scanf("%d", &x);
						root = insert(root , x);
					}
					break;

			case 2:
					printf("\nEnter an element : " );
					scanf("%d", &x);
					root = insert(root, x);
					break;

			case 3:
					printf("\nEnter data to delete : ");
					scanf("%d", &x);
					root = delete(root, x);
					break;

			case 4:
					printf("\nDisplay in Preorder :: \n");
					preorder(root);
					break;

			case 5:
					printf("\nDisplay in Inorder :: \n");
					inorder(root);
					break;

			case 6:
					break;

			default:
					printf("\nInvalid option\n" );
					break;

		}
	}
	while(choice != 6);
	return 0;
}


// Create a new node at height of leaf and return pointer
node *create_node(int data)
{
	node *p = (node *)malloc(sizeof(node));
	p -> data = data;
	p -> left = p -> right = NULL;
	p -> ht = 0;
	return p;
}

node *insert(node *root, int data)
{
	if(root == NULL)
	{
		root = create_node(data);
	}
	else if (root -> data > data) //insert in left subtree
	{
		root -> left = insert(root -> left, data);
		// check for imbalance
		if (balance_factor(root) == 2)
			// if added in the left subtree of root
			if(data < root -> data)		
				root = LL(root);
			else
				root = LR(root);
	}
	else 
	{
		root -> right = insert(root -> right, data);
		if (balance_factor(root) == -2)
			if(data > root -> data)
				root = RR(root);
			else
				root = RL(root);
	}
	root -> ht = height(root);

	return root;
}


node *RR(node *p)
{
	p = rotate_left(p);
	return p;
}

node *LL(node *p)
{
	p = rotate_right(p);
	return p;
}

node *LR(node *p)
{
	p -> left = rotate_left(p -> left);
	p = rotate_right(p);
	return p;
}

node *RL(node *p)
{
	p -> right = rotate_right(p -> right);
	p = rotate_left(p);
	return p;
}

node * rotate_right(node *p)
{
	node *q;
	q = p -> left;
	p -> left = q -> right;
	q -> right = p;
	p -> ht = height(p);
	q -> ht = height(q);
	return q;
}

node * rotate_left(node *p)
{
	node *q;
	q = p -> right;
	p -> right = q -> left;
	q -> left = p;
	p -> ht = height(p);
	q -> ht = height(q);
	return (q);

}

// Calculate balance factor for the current node
int balance_factor(node *p)
{
	int left_ht, right_ht;
	if (p == NULL)
		return 0;
	if (p -> left == NULL)
		left_ht = 0;
	else 
		left_ht = p -> left -> ht + 1;

	if (p -> right == NULL)
		right_ht = 0;
	else
		right_ht = p -> right -> ht + 1;

	return (left_ht - right_ht);
}

// Inorder traversal
void inorder(node *root)
{
	if (root != NULL)
	{
		inorder(root -> left);
		printf("%d\t", root->data);
		inorder(root -> right);
	}
}

// Inorder traversal
void preorder(node *root)
{
	if (root != NULL)
	{
		printf("%d\t", root->data);
		preorder(root -> left);
		preorder(root -> right);
	}
}


// Calculate height of a node and return
int height(node *p)
{
	int left_ht, right_ht;
	if (p == NULL)
		return 0;
	if (p -> left == NULL)
		left_ht = 0;
	else
		left_ht = 1 + p -> left -> ht;
	if (p -> right == NULL)
		right_ht = 0;
	else
		right_ht = 1 + p -> right -> ht;

	if (left_ht > right_ht)
		return left_ht;
	else
		return right_ht;
}


node * delete(node * root, int data)
{
	//Find the element in the AVL tree and delete
}