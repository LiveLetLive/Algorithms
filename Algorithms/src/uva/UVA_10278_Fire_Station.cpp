#include "CommonHeader.h"


#ifdef UVA_10278_FIRE_STATION
READ_INPUT(UVA_10278_FIRE_STATION)

#include <iostream>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 505
#define INF 0x3f3f3f3f

int g[MAXN][MAXN];
bool in_queue[MAXN];
int dist[MAXN];
int bk_dist[MAXN];
int FS_Location[MAXN];

int F, N;

void makeCopy()
{
	FOR(i, 0, N+1)
		bk_dist[i] = dist[i];
}

void restoreCopy()
{
	FOR(i, 0, N+1)
		dist[i] = bk_dist[i];
}

void reset()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0;

		dist[i] = INF;
		bk_dist[i] = INF;
		FS_Location[i] = 0;
		in_queue[i] = 0;
	}
}

void sfpa(int s)
{
	queue<int> q;

	FOR(i, 0, N+1)
		in_queue[i] = 0;

	q.push(s);
	in_queue[s] = true;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = 0;

		FOR(v, 1, N+1)
		{
			if(u == v) continue;
			if(g[u][v] &&  dist[v] > dist[u] + g[u][v])
			{
				dist[v] = dist[u] + g[u][v];
				if(in_queue[v] == 0)
					q.push(v), in_queue[v] = 1;
			}
		}

	}
}

int main()
{
	int T = 0;

	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		reset();

		scanf("%*");

		scanf("%d %d ", &F, &N);

		FOR(i, 0, F)
		{
			int tmp;
			scanf("%d ", &tmp);
			FS_Location[tmp] = 1;
		}

		if(N == 1)
		{
			printf("%d\n", 1);
			if(t < T-1) printf("\n");
			continue;
		}	

		char str[50] = { 0};
		int x, y, d;
		while(gets(str))
		{
			if(str[0] == 0) break;
			sscanf(str, "%d %d %d ", &x, &y, &d);
			g[x][y] = g[y][x] = d;
		}

		//Find the shortest distance from the FS usign existing fire stations
		FOR(i, 1, N+1)
		{
			if(FS_Location[i] == 1)
				dist[i] = 0, sfpa(i);
		}

		makeCopy();
		int maxDist = -1;

		FOR(i, 1, N+1)
			maxDist = max(maxDist, dist[i]);

		int minD = INF, minDIndex = -1;

		// Now place a fire station at each non-existing firestation and check the max value
		FOR(i, 1, N+1)
		{
			if(FS_Location[i] != 1)
			{
				restoreCopy();
				dist[i] = 0; 
				sfpa(i);

				int maxD = -1;

				FOR(j, 1, N+1)
					maxD = max(maxD, dist[j]);

				if(minD > maxD)
					minD = maxD, minDIndex = i;
			}
		}

		printf("%d\n", minDIndex);

		if(t < T-1)
			printf("\n");
	}

	return 0;
}

#endif