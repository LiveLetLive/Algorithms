#include "CommonHeader.h"

#ifdef UVA_11378_BEY_BATTLE
READ_INPUT(UVA_11378_BEY_BATTLE)

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

template <typename T> class Queue
{
public:
	Queue() { front = -1, tail = -1; }
	void clear() { front = -1, tail = -1; }
	T data[MAXN];
	int front, tail;

	void push(T& val)
	{
		front++;
		front %= MAXN;
		data[front] = val;
	}
	T& pop()
	{
		int t = tail++;
		tail %= MAXN;
		return data[t];
	}

};

void reset()
{
}

class Point
{
public:
	Point() {}
	Point(int xx, int yy) { x = xx, y = yy; }
	int x, y;
	bool operator < (Point& that)
	{
		if(this->x < that.x) return true;
		else if(this->x == that.x) return this->y < that.y;
		else return false;
	}
	bool operator > (Point& that)
	{
		if(this->x > that.x) return true;
		else if(this->x == that.x) return this->y > that.y;
		else return false;
	}
};


class Node
{
public:
	Node() {}
	Node(int kk, Point& vv) { k = kk, v = vv; left = NULL, right = NULL;}
	int k;
	Point v;
	Node *left;
	Node *right;
};

class BST
{
public:
	BST( ) { root = NULL; }
	Node *root;

	void Insert(Point& p);
	void sort(Queue<Point>& q);
	void sort(Node *x, Queue<Point>& q);
	Node *Insert(Node *x, Point& p);
};

void BST::sort(Queue<Point>& q)
{
	sort(root, q);
}
void BST::sort(Node *x, Queue<Point>& q)
{
	if(x == NULL) return;

	if(x->left) sort(x->left, q);
	q.push(x->v);
	if(x->right) sort(x->right, q);
}

void BST::Insert(Point& p)
{
	if(root == NULL)
	{
		root = new Node(p.x, p);
		return;
	}
	root = Insert(root, p);
}

Node *BST::Insert(Node *x, Point& p)
{
	if(x == NULL) return new Node(p.x, p);

	if(p < x->v) x->left = Insert(x->left, p);
	else if(p > x->v) x->right = Insert(x->right, p);

	return x;
}

Queue<Point> sq;
int N;

int FindClosest()
{
	int MaxDist = INF;

	int tail = 0;

	FOR(i, 1, N)
	{
		//New Point added, remove the farther ones
		FOR(j, tail, i)
		{
			int dist = abs(sq.data[i].x - sq.data[j].x);
			if(dist > MaxDist)
				tail++;
		}

		//Update Max Distance
		FOR(j, tail, i)
		{
			int dist = max(abs(sq.data[i].x - sq.data[j].x),  abs(sq.data[i].y - sq.data[j].y));
			MaxDist = min(MaxDist, dist);
		}
	}

	return MaxDist;
}


int main()
{
	int cnt = 1;
	while(scanf("%d ", &N) != EOF)
	{
		BST b;
		cnt++;
		FOR(i, 0, N)
		{
			Point p;
			scanf("%d %d ", &p.x, &p.y);
			b.Insert(p);
		}
		sq.clear();
		b.sort(sq);

		printf("%d\n", FindClosest());
	}
	return 0;
}

#endif
