#include "CommonHeader.h"

#ifdef SELF_IMARAT_GIRI_PREDICTION
READ_INPUT(SELF_IMARAT_GIRI_PREDICTION)

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

class Queue
{
public:
	Queue() 
	{
		q = (int*)calloc(MAXN, sizeof(int));
		inq = (int*)calloc(MAXN, sizeof(int));
		head = 0;
		tail = 0;
	}
	~Queue() 
	{
		free(q);
		free(inq);
	}
	int *q;
	int *inq;
	int head, tail;

	bool isEmpty()
	{
		return head == tail;
	}

	int pop()
	{
		int tmp = q[tail];
		inq[tmp] = 0;
		++tail;
		return tmp;
	}

	void push(int tmp)
	{
		if(inq[tmp] == 0)
			q[head] = tmp, inq[tmp] = 1, ++head;
	}
};

class Point
{
public:
	int x,y,d;
	bool operator > (Point& that)
	{
		if((this->x + this->y) == (that.x + that.y))
			return ((this->x) > (that.x));

		return ((this->x + this->y) > (that.x + that.y));
	}
};

Point pArr[MAXN];

int N, W, K;


void reset()
{
	//FOR(i, 0, N)
	//	pArr[i].d = -1; 
}




int part(int l, int h)
{
	int i = l;
	int j = h+1;

	while(1)
	{
		while(pArr[l] > pArr[++i])
			if(i >= h)
				break;

		while(pArr[--j] > pArr[l])
			if(j <= l)
				break;

		if(i >= j)
			break;

		swap(pArr[i], pArr[j]);
	}

	swap(pArr[l], pArr[j]);
	return j;
}

void Qsort(int l, int h)
{
	if(l >= h) return;
	int p = part(l, h);
	Qsort(l, p-1);
	Qsort(p+1, h);
}

#define Abs(x) (x<0)?(-x):x

int main()
{
	int T;
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d %d %d ", &N, &W, &K);

		FOR(i, 0, N)
		{
			scanf("%d %d %d ", &pArr[i].x, &pArr[i].y, &pArr[i].d);
			pArr[i].d -= K;

			pArr[i].d = (pArr[i].d < 0) ? 0 : pArr[i].d;
		}

		Qsort(0, N-1);

		Queue q;
		int cnt = 0;

		FOR(i, 0, N)
		{
			//Found 1 which just collapsed
			if(pArr[i].d == 0)
			{
				q.push(i);
				pArr[i].d = -1;
				++cnt;
			}
		}

		if(cnt > 0)
		{
			while(q.isEmpty() == false)
			{
				int u = q.pop();

				FOR(i, u+1, N)
				{
					if(pArr[i].d == -1)
						continue;

					int dx = pArr[i].x - pArr[u].x;
					int dy = pArr[i].y - pArr[u].y;

					dx = Abs(dx); 
					dy = Abs(dy);

					if(dx > 10 && dy > 10)
						break;

					int dxy = dx + dy;  
					int d = 10 / dxy;

					if(d)
					{
						pArr[i].d -= d;
						pArr[i].d = (pArr[i].d < 0) ? 0 : pArr[i].d;

						if(pArr[i].d == 0)
						{
							q.push(i);
							pArr[i].d = -1;
						}
					}
				}


				for(int i = u - 1; u; --i)
				{
					if(pArr[i].d == -1)
						continue;

					int dx = pArr[i].x - pArr[u].x;
					int dy = pArr[i].y - pArr[u].y;

					dx = Abs(dx); 
					dy = Abs(dy);

					if(dx > 10 && dy > 10)
						break;

					int dxy = dx + dy;  
					int d = 10 / dxy;

					if(d)
					{
						pArr[i].d -= d;
						pArr[i].d = (pArr[i].d < 0) ? 0 : pArr[i].d;

						if(pArr[i].d == 0)
						{
							q.push(i);
							pArr[i].d = -1;
						}
					}
				}
			}
		}

		cnt = 0;

		FOR(i, 0, N)
			if(pArr[i].d > 0) cnt++;

		printf("#%d %d\n", t+1, cnt );

	}
	return 0;
}

#endif
