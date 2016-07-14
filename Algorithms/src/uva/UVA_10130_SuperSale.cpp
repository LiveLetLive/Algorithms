#include "CommonHeader.h"

#ifdef UVA_10130_SUPERSALE
READ_INPUT(UVA_10130_SUPERSALE)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1005
#define MAXG 105
#define MAXC 105
#define INF 100000000

int N;

int price[MAXN];
int wt[MAXN];
int G;
int capacity[MAXG];

int maxval[MAXN][MAXC];

void reset()
{
	FOR(i, 0, MAXN)
		price[i] = 0, wt[i] = 0;
	FOR(i, 0, MAXG)
		capacity[i] = 0;
}

int calc(int id, int remW)
{
	if(id >= N) return 0;
	if(remW < 0) return 0;

	if(maxval[id][remW] != -1)
		return maxval[id][remW];

	if(wt[id] > remW)
		maxval[id][remW] = calc(id+1, remW);
	else
	{
		int x = (calc(id+1, remW));
		int y = (price[id] + calc(id+1, remW - wt[id]));
		int val = max(x , y);

		maxval[id][remW] = max(maxval[id][remW], val);
	}

	return maxval[id][remW];
}

int FindMax()
{
	int val = 0;
	FOR(i, 0, G)
	{
		FOR(j, 0, N+1)
			FOR(k, 0, capacity[i]+1)
			maxval[j][k] = -1;
		val += calc(0, capacity[i]);
	}

	return val;
}

int main()
{
	int T = 0;
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &N);

		FOR(i, 0, N)
			scanf("%d %d ", &price[i], &wt[i]);

		scanf("%d ", &G);

		FOR(i, 0, G)
			scanf("%d ", &capacity[i]);

		printf("%d\n", FindMax());
	}

	return 0;
}


#endif