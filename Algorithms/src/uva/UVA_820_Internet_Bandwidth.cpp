#include "CommonHeader.h"


#ifdef UVA_820_INTERNET_BANDWIDTH
READ_INPUT(UVA_820_INTERNET_BANDWIDTH)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;

typedef unsigned long long ll;

#define FOR(i, init, count) for(int i = init; i < count; i++)
const int MAX = 110;
const int INF = 1000000;

int n, s, t, c, f, mf;

ll g[MAX][MAX];
int p[MAX];
int tc = 0;
int dist[MAX];

void reset()
{
	f = 0;
	mf = 0;
	FOR(i, 0, MAX)
	{
		FOR(j, 0, MAX)
			g[i][j] = 0;
		p[i] = -1;
	}
}


void augment(int v, int& minEdge)
{
	if(p[v] == -1) return;

	int parent = p[v];

	if(minEdge > g[parent][v])
		minEdge = g[parent][v];

	augment(parent, minEdge);

	g[parent][v] -= minEdge;
	g[v][parent] += minEdge;

	f = minEdge;
	return;
}

void PrintGraph()
{
#ifdef DEBUG
	printf("\n");
	FOR(i, 0, n+1)
	{
		FOR(j, 0, n+1)
		{
			printf("%02d ", g[i][j]);
		}
		printf("\n");
	}
	printf("\n");
#endif
}

bool bfs(int s)
{
	FOR(i, 0, MAX)
		dist[i] = INF;

	queue<int> q;
	dist[s] = 0;
	q.push(s);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		if(u == t)
			return true;
		FOR(v, 1, n+1)
		{
			if(v == u) continue;

			if(dist[v] == INF && g[u][v] > 0)
			{
				dist[v] = dist[u]+1;
				p[v] = u;
				q.push(v);
			}
		}
	}

	return false;
}

int maxflow()
{
	while(bfs(s))
	{
		int x = INF;
		augment(t, x);
		PrintGraph();
		if(f == 0)
			break;
		mf += f;
	}

	return mf;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		tc++;
		if(n == 0)
			break;

		reset();

		scanf("%d", &s);
		scanf("%d", &t);
		scanf("%d", &c);

		FOR(i, 0, c)
		{
			int x, y;
			scanf("%d", &x);
			scanf("%d", &y);
			ll tmp;
			scanf("%lld", &tmp);
			
			g[x][y] += tmp;
			g[y][x] = g[x][y];
		}
		PrintGraph();

		printf("Network %d\n", tc);
		printf("The bandwidth is %d.\n\n", maxflow());
	}
	return 0;
}


#endif