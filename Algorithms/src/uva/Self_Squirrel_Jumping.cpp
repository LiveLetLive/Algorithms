#include "CommonHeader.h"

#ifdef SELF_SQUIRREL_JUMPING
READ_INPUT(SELF_SQUIRREL_JUMPING)

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
#define MAXN 100003
#define INF 0x3f3f3f3fL
typedef long long ll;


class Node
{
public:
	Node(int k, int v) { key = k, val = v; left = NULL, right = NULL; } 
	int key;
	int val;
	Node* left;
	Node* right;
};


class BST
{
public:
	BST() { root = NULL; }
	Node *root;

	void Insert(int key, int val);
	Node* Insert(Node* x, int key, int val);

	void Delete(int key);
	Node* Delete(Node* x, int key);
	Node* deleteMin(Node* x);

	Node* Find(int key);
	Node* Find(Node *x, int key);

	Node* GetMin();
	Node* GetMin(Node* x);

	Node* GetMax();
	Node* GetMax(Node* x);

	Node *ceil(int val);
	Node *ceil(Node *x, int val);

	Node *floor(int val);
	Node *floor(Node* x, int val);
};

void BST::Delete(int key)
{
	root = Delete(root, key);
}

Node* BST::deleteMin(Node* x)
{
	if(x->left == NULL) 
	{
		Node*tmp = x->right;
		delete x;
		return tmp;
	}

	x->left = deleteMin(x->left);
	return x;
}

Node* BST::Delete(Node* x, int key)
{
	if(x == NULL) return NULL;

	if(key < x->key) x->left = Delete(x->left, key);
	else if(key > x->key) x->right = Delete(x->right, key);
	else 
	{
		if(x->right == NULL && x->left != NULL)
		{
			Node* tmp = x->left;
			delete x;
			return tmp;
		}
		else if(x->right != NULL && x->left == NULL)
		{
			Node* tmp = x->right;
			delete x;
			return tmp;
		}
		else if(x->right == NULL && x->left == NULL)
			return NULL;
		else
		{
			Node *t = x;

			//Make a copy of min on x->right
			Node *tmp = new Node(*GetMin(t->right));

			//Delete this min on the right & get the alst pointer, this will be new x's right
			Node *right = deleteMin(t->right);

			x = tmp;
			x->right = right;
			x->left = t->left;
			delete t;
		}
	}

	return x;
}

Node *BST::ceil(int val)
{
	return ceil(root, val);
}

Node *BST::ceil(Node *x, int val)
{
	if(x == NULL) return NULL;

	if(val == x->key) return x;

	Node *t = NULL;
	if(val > x->key) return ceil(x->right, val);
	if(val < x->key) 
		t = ceil(x->left, val);

	if(t == NULL) return x;
	else return t;
}

Node *BST::floor(int val)
{
	return floor(root, val);
}

Node *BST::floor(Node* x, int val)
{
	if(x == NULL) return NULL;

	if(val == x->key) return x;

	Node *t = NULL;
	if(val < x->key) return floor(x->left, val);
	if(val > x->key) 
		t = floor(x->right, val);

	if(t == NULL) return x;
	else return t;
}

Node* BST::GetMin()
{
	return GetMin(root);
}

Node* BST::GetMin(Node* x)
{
	if(x->left == NULL) return x;

	Node* t = NULL;
	if(x->left) t = GetMin(x->left);

	return t;
}

Node* BST::GetMax()
{
	return GetMax(root);
}

Node* BST::GetMax(Node* x)
{
	if(x->right == NULL) return x;

	Node* t = NULL;
	if(x->right) t = GetMax(x->right);

	return t;
}


Node* BST::Find(int key)
{
	return Find(root, key);
}

Node* BST::Find(Node *x, int key)
{
	if(x == NULL) return NULL;

	if(key < x->key) return Find(x->left, key);
	else if(key > x->key) return Find(x->right, key);
	else return x; 
}

void BST::Insert(int key, int val)
{
	if(root == NULL) root = new Node(key, val);
	else root = Insert(root, key, val);
}

Node* BST::Insert(Node* x, int key, int val)
{
	if(x == NULL) return new Node(key, val);

	if(key < x->key) x->left = Insert(x->left, key, val);
	else if(key > x->key) x->right = Insert(x->right, key, val);
	else x->val = val; 

	return x;
}

int q[MAXN];
int head, N;

void reset()
{
	FOR(i, 0, N+1)
		q[i] = 0;
}

int main()
{
	freopen("output.txt","w",stdout);
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d %d ", &N, &head);
		reset();

		BST b;
		int cnt = 0;
		int queueIndex = -1;

		printf("#%d ", t+1);

		FOR(i, 0, N)
		{
			int cmd;
			scanf("%d ", &cmd);

			if(cmd == 0)
			{
				int idx;
				scanf("%d ", &idx);

				if(queueIndex == -1)
					queueIndex = 1;

				b.Insert(idx, ++cnt);
				q[cnt] = idx;
			}
			else if(cmd == 1)
			{
				Node* tmp = b.ceil(head);
				if(tmp == NULL)
					tmp = b.floor(head);

				printf("%d ", tmp->key);
				head = tmp->key;
				queueIndex = tmp->val;
				q[tmp->val] = 0;
				b.Delete(tmp->key);
			}
			else if(cmd == 2)
			{
				Node* tmp = b.floor(head);
				if(tmp == NULL)
					tmp = b.ceil(head);
				printf("%d ", tmp->key);
				head = tmp->key;
				queueIndex = tmp->val;
				q[tmp->val] = 0;
				b.Delete(tmp->key);

			}
			else if(cmd == 3)
			{
				int idx = queueIndex;

				bool found = false;

				while(idx >= 1)
				{
					if(q[idx])
					{
						found = true;
						printf("%d ", q[idx]);

						head = q[idx];
						queueIndex = idx;
						b.Delete(q[idx]);
						q[idx] = 0;
						break;
					}
					idx--;
				}

				if(found == false)
				{
					idx = queueIndex;
					while(idx >= 1 && idx <= N+1)
					{
						if(q[idx])
						{
							found = true;
							printf("%d ", q[idx]);
							head = q[idx];
							queueIndex = idx;
							b.Delete(q[idx]);
							q[idx] = 0;
							break;
						}
						idx++;
					}
				}
			}
			else if(cmd == 4)
			{
				Node* tmp = b.GetMax();
				printf("%d ", tmp->key);
				head = tmp->key;
				queueIndex = tmp->val;
				q[tmp->val] = NULL;
				b.Delete(tmp->key);
			}
		}

		printf("\n");

	}
	return 0;
}

#endif
