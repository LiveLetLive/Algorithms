#include "CommonHeader.h"

#ifdef UVA_11338_MINEFIELD
READ_INPUT(UVA_11338_MINEFIELD)

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
#define MAXN 10003
#define MAXN1 1000

#define INF 0x3f3f3f3f3f3f3f3fL
typedef double ll;

class MCell
{
public:
	ll x;
	ll y;
};

class Node
{
public:
	int neighbor;
	ll d;
};

int w, h;
int N;
MCell gCells[MAXN];
Node g[MAXN][MAXN1];
int cnt[MAXN];
int in_queue[MAXN];
ll dist[MAXN];
ll td;

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN1)
		g[i][j].neighbor  = 0, g[i][j].d = 0, cnt[i] = 0;
}

inline ll cdistance(int i, int j)
{
	ll x1 = gCells[i].x;
	ll x2 = gCells[j].x;
	ll y1 = gCells[i].y;
	ll y2 = gCells[j].y;

	ll ans = sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))); 

	if(ans < 0)
		ans = -ans;

	return ans;
}

bool spfa()
{
	queue<int> q;

	FOR(i, 0, N)
		dist[i] = INF, in_queue[i] = 0;

	q.push(0);
	dist[0] = 0;

	while(q.empty() == false)
	{
		int u = q.front();
		q.pop();
		in_queue[u] = false;

		if(u == N-1)
			return true;

		FOR(i, 0, cnt[u])
		{
			int v = g[u][i].neighbor;
			ll d = g[u][i].d;

			if(dist[v] > dist[u] + d && dist[u] + d <= (td))
			{
				dist[v] = dist[u] + d;
				if(in_queue[v] == false)
					q.push(v), in_queue[v] = true;
			}
		}
	}

	return false;
}

int main()
{
	char str[50] = { 0 };
	while(fgets(str, 50, stdin))
	{
		if(str[0] == '*')
			break;
		reset();

		sscanf(str, "%d %d ", &w, &h);
		scanf("%d ", &N);

		gCells[0].x = 0;
		gCells[0].y = 0;
		gCells[N+1].x = w;
		gCells[N+1].y = h;

		FOR(i, 1, N+1)
			scanf("%lf %lf ", &gCells[i].x, &gCells[i].y);
		 
		N += 2;

		//Make graph for safe points.
		FOR(i, 0, N)
			FOR(j, i+1, N)
		{
			if(i == j) continue;

			ll dist = cdistance(i, j);
			if(dist <= 1.5)
			{
				g[i][cnt[i]].neighbor = j;
				g[j][cnt[j]].neighbor = i;
				g[i][cnt[i]++].d = dist;
				g[j][cnt[j]++].d = dist;
			}
		}

		scanf("%lf ", &td);
		int ans = spfa();

		if(ans == 1)
			printf("I am lucky!\n");
		else
			printf("Boom!\n");
	}
	return 0;
}

#endif
