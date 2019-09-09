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
void display_level(node *, int);
void level_order(node *);
int height(node *);
node *rotate_right(node *);
node *rotate_left(node *);
node * RR(node *);
node * LL(node *);
node * RL(node *);
node * LR(node *);
int balance_factor(node *);
node * successor(node *);



int main()
{
	node * root = NULL;
	int x, n, choice, i;

	do 
	{
		printf("\n*********AVL Operations***********\n");
		printf("1. Create\n2. Insert \n3. Delete \n4. Display Preorder\n5. Display Inorder\n6. Display Level Order\n7. Exit \n");
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
						printf("\nLevel Order : \n");
						level_order(root);
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
					printf("\nDisplay level order :: \n");
					level_order(root);
					break;

			case 7:
					break;

			default:
					printf("\nInvalid option.\n" );
					break;

		}
	}
	while(choice != 7);
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
		if (balance_factor(root) == 2)   // imbalance does not propagate upwards. Only once needed
			// if added in the left subtree of root
			if(data < root -> left -> data)		
				root = LL(root);
			else
				root = LR(root);
	}
	else 
	{
		root -> right = insert(root -> right, data);
		if (balance_factor(root) == -2)
			if(data > root -> right -> data)
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


node *delete(node * root, int data)
{
	if (root == NULL)
	{
		printf("Value not found !!\n");
		return NULL;
	}
	if (data < root -> data)
	{
		root  -> left = delete(root -> left, data);
	}
	else if(data > root -> data)
	{
		root -> right = delete(root -> right, data);
	}
	else 	// Value found
	{
		// If target node is leaf node
		if (root -> left == NULL && root -> right == NULL)
		{
			node * p = root;
			free(p);
			return NULL;
		}
		// If target node has single child
		else if(root -> left == NULL || root -> right == NULL)  
		{
			node * p;
			if (root -> left != NULL)  // if left child exists
				p = root -> left;
			else
				p = root -> right;
			free (root);
			return p;
		}
		// If target node has both children
		else
		{
			node * p = successor(root);
			root -> data = p -> data; 	// Overwrite data with inorder successor data
			root -> right = delete(root->right, p->data);
		}
	}

	// Rotate after deletion
	if (balance_factor(root) == -2)   // if deleted from left subtree
	{
		if(balance_factor(root -> right) <= 0)  // if right subtree is right heavy or balanced
			root = RR(root);
		else   		// if right subtree is left heavy
			root = RL(root);
	}
	else if (balance_factor(root) == 2) 
	{
		// if deleted from right subtree
		if(balance_factor(root -> left) >= 0)	//if left subtree is left heavy or balanced
			root = LL(root);
		else   		//if left subtree is right heavy
			root = LR(root);
	}

	root -> ht = height(root);
	return root;
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

// Level Order traversal
void level_order(node *root)
{
	if(root == NULL)
		return;
	
	for(int h=0; h <= root->ht; h++)
	{
		display_level(root, h);
		printf("\n");
	}
}

node* successor(node * root)
{
	if(root == NULL)
		return NULL;
	else if(root -> right == NULL)
		return NULL;

	node * p = root -> right;
	while(p->left != NULL)
		p = p -> left;

	return p;
}

void display_level(node *root, int curr_ht)
{

	if (root == NULL)
		return;

	if (curr_ht == 0)
	{
		printf("%d\t", root -> data);
	}
	else if (curr_ht > 0)
	{
		display_level(root -> left, curr_ht-1);
		display_level(root -> right, curr_ht-1);
	}
}