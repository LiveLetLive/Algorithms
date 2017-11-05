#include "CommonHeader.h"

#ifdef CG_RECTANGLES_SCPC_2016
READ_INPUT(CG_RECTANGLES_SCPC_2016)

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
#define MAXN 5003
#define INF 0x3f3f3f3fL
typedef long long ll;
int N, M, K;

class Rect;





class Rect
{
public:
	Rect() {};
	Rect(int X1,int Y1,int X2,int Y2)
	{
		x1 = X1, y1 = Y1, x2 = X2, y2 = Y2;
	}
	int x1, y1, x2, y2;

	bool operator < (Rect & o)
	{
		if (x1 == o.x1) {
			if (y1 == o.y1) {
				if (x2 == o.x2) {
					if (y2 == o.y2) {
						return y2 > o.y2;
					}
					return y2 > o.y2;
				}
				return x2 > o.x2;
			}
			return y1 < o.y1;
		}
		return x1 < o.x1;
	}

	bool contains(Rect& o)
	{
		if((x1 <= o.x1 
			//&& o.x1 < o.x2
			&& o.x2 <= x2)
			&&(y1 <= o.y1 
			//&& o.y1 < o.y2
			&& o.y2 <= y2))
			return true;
		return false;
	}
};

Rect r[MAXN];
int dp[MAXN];

int test[MAXN];

void HeapSwap(int i, int j)
{
	int tmp = test[i];
	test[i] = test[j];
	test[j] = tmp;
}

void HeapSink(int k, int n)
{
	while(2*k <= n)
	{
		int j = 2*k;
		if(j < n && test[j+1] > test[j]) j++;

		if(test[k] > test[j])
			break;

		HeapSwap(j,k);
		k = j;
	}
}

void HeapSort()
{
	int tmp = K;
	// Heapify
	for(int i = K/2; i > 0 ; i--)
		HeapSink(i, K);

	//For all move & sink
	while(K > 1)
	{
		HeapSwap(1, K--);
		HeapSink(1, K);
	}

	K = tmp;
}



int Solve(int idx)
{
	if(dp[idx] != -1)
		return dp[idx];

	int ans = 0;
	FOR(i, idx+1, K+1)
	{
		if(r[idx].contains(r[i]))
		{
			ans = max(ans, Solve(i)+1);
		}
	}

	return dp[idx] = ans;
}

void reset()
{
	FOR(i, 0, K+1)
		dp[i] = -1;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d %d %d ", &N, &M, &K);

		K++;
		reset();

		r[1] = Rect(0, 0, N, M);

		FOR(i, 2, K+1)
		{
			int x1, y1, x2, y2;
			scanf("%d %d %d %d ", &x1, &y1, &x2, &y2);
			r[i] = Rect(x1, y1, x2, y2);
		}

		//sort(r, r + K);
		FOR(i, 1, K+1)
			test[i] = rand() % 1000;

		HeapSort();

		int ans = 0;
		ans = Solve(1);

		printf("Case #%d\n", t+1);
		printf("%d\n", (ans == 0) ? 1 : ans);
	}
	return 0;
}

#endif
