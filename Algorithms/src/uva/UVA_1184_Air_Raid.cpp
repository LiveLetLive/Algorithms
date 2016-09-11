#include "CommonHeader.h"

#ifdef UVA_1184_AIR_RAID
READ_INPUT(UVA_1184_AIR_RAID)

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
#define MAXN 121
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int g[MAXN*2][MAXN*2];
int cnt[MAXN*2];
int vis[MAXN*2];
int match[MAXN*2];
int V, E;

void reset()
{
	FOR(i, 0, V*2)
	{
		FOR(j, 0, V*2)
			g[i][j] = 0;
		cnt[i] = 0;
	}
}


int Aug(int u)
{
	if(vis[u])
		return 0;

	vis[u] = 1;

	FOR(x, 0, cnt[u])
	{
		int v = g[u][x];
		if(match[v] == -1 || Aug(match[v]))
		{
			match[v] = u;
			return 1;
		}
	}

	return 0;
}

int FindMBCM()
{
	int mcbm = 0;

	FOR(i, 0, 2*V)
		match[i] = -1;


	FOR(l, 0, V)
	{
		FOR(i, 0, V)
			vis[i] = 0;

		mcbm += Aug(l);
	}

	return mcbm;
}


int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &V);
		scanf("%d ", &E);

		reset();
		FOR(i, 0, E)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			x--, y--;
			g[x][cnt[x]++] = y+V;
		}

		int mbcm = FindMBCM();
		printf("%d\n", (V) - mbcm);
	}
	return 0;
}

#endif
