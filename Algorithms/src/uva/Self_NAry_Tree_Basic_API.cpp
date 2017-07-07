#include "CommonHeader.h"

#ifdef SELF_NARY_TREE_BASIC_API
READ_INPUT(SELF_NARY_TREE_BASIC_API)

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 1003
#define INF 0x3f3f3f3fL
typedef long long ll;

class Node;

class Node
{
public:
	Node()
	{
		data = -1, fChild = NULL, next = NULL, depth = 0, parent = NULL;
	}
	Node(Node* p, int d, int dep)
	{
		data = d, fChild = NULL, next = NULL, depth = dep, parent = p;
	}
	int data;
	Node *parent;
	Node* fChild;
	Node* next;
	int depth;
};

Node * root = NULL;
typedef bool (*NodeTraverseFunc) (Node *node, int data);

typedef enum
{
	IN_ORDER, 
	LEVEL_ORDER
}TraverseType;

//initialize;, Nary tree, create root node with dot. 
extern void Nary_Tree_init();

//return the root node of the Nary tree, NULL if no node is present 
extern Node* Nary_Tree_Get_Root();

extern int Nary_Tree_insert (int parentID, int dataChild);

extern int Nary_Tree_insert_before (int parentID, int sibling, int data);

extern int Nary_Tree_depth (int key);

extern void Nary_Tree_children_foreach(int key, NodeTraverseFunc func, int data); 

extern int Nary_Tree_is_leaf(int key);

extern void Nary_Tree_destroy (int key);

extern void Nary_Tree_traverse(Node *root, TraverseType order, NodeTraverseFunc func, int data);




bool print(Node *node, int data)
{
	if(node != NULL)
		printf("%d ", node->data);
	return false;
}

int N;

int main()
{
	int no0f0perations, Test_Cases; 
	scanf("%d", &Test_Cases);
	int N, key, val, retInt;
	int par, sib;

	for (int i = 0; i < Test_Cases; i++) 
	{
		printf("#%d\n", i + 1);

		Nary_Tree_init();

		scanf("%d", &no0f0perations); 
		while (no0f0perations--)
		{
			scanf("%d ", &N);
			switch (N) 
			{
			case 1:
				scanf("%d %d", &par, &val);
				retInt = Nary_Tree_insert(par, val); 
				printf("%d\n", retInt);
				break;
			case 2:
				scanf("%d %d %d ", &par, &sib, &val);
				retInt = Nary_Tree_insert_before(par, sib, val); 
					printf("%d\n", retInt);
				break;

			case 3:
				scanf("%d ", &key);
					retInt = Nary_Tree_depth(key);
				printf("%d\n", retInt);
				break;
			case 4:
				scanf("%d", &key);
				if (Nary_Tree_is_leaf(key) == 0)
				{
					Nary_Tree_children_foreach(key, print, -1);
					printf("\n");
				}
					break; 
			case 5:
				scanf("%d", &key);
					printf("%d\n", Nary_Tree_is_leaf(key));
				break; 
			case 6:
				scanf("%d", &key);
					Nary_Tree_destroy(key);
				break; 
			case 7:

				int order;
				scanf("%d", &order);

					if(Nary_Tree_Get_Root() == NULL)
					{
						printf("NULL\n");
					}
					else
					{
						Nary_Tree_traverse(Nary_Tree_Get_Root(), (TraverseType)order, print, -1 ); 
						printf("\n");
					}
				break;
			}
			return 0;
		}
	}
}

void Nary_Tree_init()
{
	if(root == NULL)
		root = new Node(NULL, 0, 1);
	else
	{
		Nary_Tree_destroy(1);
		root = new Node(NULL, 0, 1);
	}
}

Node* Nary_Tree_Get_Root()
{
	return root;
}

Node* FindNode(Node* root, int key)
{
	if(root == NULL)
		return NULL;

	if(root->data == key)
		return root;

	Node *n = FindNode(root->fChild, key);
	if(n) return n;
	n = FindNode(root->next, key);
	if(n) return n;

	return NULL;
}

int Nary_Tree_insert (int parentID, int dataChild)
{
	Node* n = FindNode(root, parentID);

	if(n == NULL)
		return -1;
	else
	{
		Node *c = new Node(n, dataChild, n->depth + 1); 
		Node *tmp = n->fChild;
		n->fChild = c;
		c->next = tmp;
		return dataChild;
	}
}

int Nary_Tree_insert_before (int parentID, int sibling, int data)
{
}

int Nary_Tree_depth (int key)
{
	Node* n = FindNode(root, key);

	if(n == NULL)
		return -1;
	else
		return n->depth;
}

void Nary_Tree_children_foreach(int key, NodeTraverseFunc func, int data)
{
	Node* n = FindNode(root, key);

	if(n == NULL)
		return;

	Node *n = root->fChild;

	while(n)
	{
		func(n, data);
		n = n->next;
	}

	return;
}

int Nary_Tree_is_leaf(int key)
{
	Node* n = FindNode(root, key);

	if(n == NULL)
		return -1;
	else
		return n->fChild == NULL;
}

bool DeleteNode(Node *node, int data)
{
	delete node;
	node = NULL;
	return true;
}


void Nary_Tree_destroy (int key)
{
	Node* n = FindNode(root, key);

	if(n == NULL)
		return;

	Nary_Tree_traverse(n, TraverseType::IN_ORDER, DeleteNode, -1);

	delete n;
}

void Nary_Tree_traverse(Node *root, TraverseType order, NodeTraverseFunc func, int data)
{

}


#endif
