#include "CommonHeader.h"

#ifdef UVA_11849_CD
READ_INPUT(UVA_11849_CD)

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
#define MAXN 1000003
#define INF 0x3f3f3f3fL
typedef long long ll;

void reset()
{
}

typedef int Key;
typedef int Value;

class Node
{
public:
	Key key;
	Value val;
	Node *left;
	Node *right;
	int count;

	Node(Key k, Value v)
	{
		key = k, val = v;
		left = right = NULL;
	}
};

class BST
{
	Node *root;
public:

	BST() { root = NULL; }
	~BST() { Delete(root); }

	void Put(Key& k, Value& v)
	{
		root = Put(root, k, v);
	}

	Node* Put(Node *x, Key& k, Value& v)
	{
		if(x == NULL) return new Node(k, v);
		
		if(k < x->key) 
			x->left = Put(x->left, k, v);
		else if(k > x->key) 
			x->right = Put(x->right, k, v);
		else 
			x->val = v;
		
		x->count = 1 + Size(x->left) + Size(x->right);

		return x;
	}
	
	Value* Get(Key& k)
	{
		Node *x = root;

		while(x != NULL)
		{
			if(k < x->key) x = x->left;
			else if(k > x->key) x = x->right;
			else return &x->val;
		}
		
		return NULL;
	}

	void DeleteAll()
	{
		Delete(root);
	}

	void Delete(Node *x)
	{
		if(x == NULL) return;

		if(x->left == NULL && x->right == NULL)
		{
			delete x;
			return;
		}

		Delete(x->left);
		Delete(x->right);
	}

	int Size()
	{
		return Size(root);
	}

	int Size(Node *x)
	{
		if(x == NULL) return 0;
		return x->count;
	}

	Key* Floor(Key& k)
	{
		Node *x = Floor(root, k);
		if(x == NULL) return NULL;
		return &x->key;
	}

	Node* Floor(Node* x, Key& k)
	{
		if(x == NULL) return NULL;
		
		if(x->key == k) return x;
		if(x->key < k) return Floor(x->left, k);

		//Tricky, only in right case deal with real floor logic
		Node *t = Floor(x->right, k);
		if(t != NULL) return t;
		else return x;
	}

};

int N, M;

int arr[MAXN];

int comp(const void *p1, const void *p2)
{
	int *i1 = (int*)p1;
	int *i2 = (int*)p2;

	return (*i1 - *i2);
}

bool findItem(int k)
{
	int hi = N-1;
	int lo = 0;

	while(hi >= lo)
	{
		int mid = lo + (hi - lo)/2;
		
		if(arr[mid] == k)		return 1;
		else if(arr[mid] > k)	hi = mid-1;
		else					lo = mid+1;
	}

	return false;
}

int main()
{
	int T;
	while(scanf("%d %d", &N, &M), N, M)
	{
		int counter = 0;
		FOR(i, 0, N)
			scanf("%d ", &arr[i]);

		FOR(i, 0, M)
		{
			int k = 0;
			scanf("%d ", &k);

			if(findItem(k))
				counter++;
		}

		printf("%d\n", counter);
	}
	return 0;
}

#endif
