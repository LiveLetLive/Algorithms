#include "CommonHeader.h"

#ifdef UVA_12125_MARCH_OF_THE_PENGUINS
READ_INPUT(UVA_12125_MARCH_OF_THE_PENGUINS)

#include <iostream>
#include <cstdio>
#include <queue>
#include <math.h>

using namespace std;


#define MAXN (101*2+5)
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define INF 0x3f3f3f3f

int g[MAXN][MAXN];

int adj_List[MAXN][MAXN];
int adjCnt[MAXN];

int bk_g[MAXN][MAXN];
int p[MAXN];
int dist[MAXN];
int x[MAXN];
int y[MAXN];
int penCnt[MAXN];
int flyCnt[MAXN];
int mf, f;
int nodeCnt;
int T;
int N;
double D;
int total_penguin = 0;

void makeCopy()
{
	FOR(i, 0, nodeCnt)
	{
		FOR(j, 0, nodeCnt)
			bk_g[i][j] = g[i][j];
	}
}

void restoreCopy()
{
	mf = 0;
	FOR(i, 0, nodeCnt)
	{
		p[i] = -1;
		FOR(j, 0, nodeCnt)
			g[i][j] = bk_g[i][j];
	}
}

void PrintGraph()
{
#ifdef DEBUG
	printf("//////////////////\n");
	FOR(i, 0, nodeCnt)
	{
		FOR(j, 0, nodeCnt)
			printf("%02d ", g[i][j] >= 20 ? -1 : g[i][j]);
		printf("\n");
	}
	printf("//////////////////\n");
#endif
}
void reset()
{
	total_penguin = 0;
	mf = 0;
	f = 0;
	FOR(i, 0, nodeCnt)
	{
		adjCnt[i] = 0;
		p[i] = -1;
		FOR(j, 0, nodeCnt)
			bk_g[i][j] = g[i][j] = 0, adj_List[i][j] = 0;
	}
}

bool bfs(int src, int sink)
{
	queue<int> q;

	FOR(i, 0, nodeCnt)
		dist[i] = INF;

	q.push(src);
	dist[src] = 0;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		if(u == sink)
			return true;

		FOR(j, 0, adjCnt[u])
		{
			int v = adj_List[u][j];

			if(u == v) continue;
			if(dist[v] == INF && g[u][v])
			{
				p[v] = u;
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}

	return false;
}

void augment(int v, int& minEdge)
{
	int pv = p[v];
	if(pv == -1) return;

	if(g[pv][v] < minEdge )
		minEdge = g[pv][v]; 

	augment(pv, minEdge);

	g[pv][v] -= minEdge;
	g[v][pv] += minEdge;
}

int maxFlow(int src, int sink)
{
	while(bfs(src, sink))
	{
		PrintGraph();

		int f = INF;
		augment(sink, f);

		if(f == 0)
			break;

		mf += f;
	}
	PrintGraph();

	return mf;
}


int main()
{
	scanf("%d ", &T);

	FOR(t1, 0, T)
	{
		scanf("%d %lf", &N, &D);
		nodeCnt = 2*N + 1;
		reset();

		int s = 2 * N;
		int t;

		FOR(i, 0, N)
		{
			scanf("%d %d %d %d ", &x[i], &y[i], &penCnt[i], &flyCnt[i]);

			int idx = adjCnt[i]++;
			adj_List[i][idx] = N+i;
			
			idx = adjCnt[s]++;
			adj_List[s][idx] = i;

			g[i][N+i] = flyCnt[i];
			g[s][i] = penCnt[i];
			total_penguin += penCnt[i];
		}

		FOR(i, 0, N)
		{
			FOR(j, 0, N)
			{
				if(i == j) continue;

				int dx = x[i] - x[j];
				int dy = y[i] - y[j];

				double d1 = dx*dx + dy*dy; 
				if(d1 <= (D*D))
				{
					int idx = adjCnt[N+i]++;
					adj_List[N+i][idx] = j;

					idx = adjCnt[N+j]++;
					adj_List[N+j][idx] = i;


					g[N+i][j] = INF;
					g[N+j][i] = INF;
				}
			}
		}
		makeCopy();
		bool foundIce = false;

		int nAnswer[MAXN] = {0,};
		int nAnswerIndex = 0;
		FOR(i, 0, N)
		{
			t = i;
			restoreCopy();
			int ans = maxFlow(s, t);
			if(ans == total_penguin)
				foundIce = true, nAnswer[nAnswerIndex++] = i;
		}

		if(nAnswerIndex == 0)
        	puts("-1");
        else
		{
        	printf("%d", nAnswer[0]);
			for(int i = 1; i < nAnswerIndex; i++)
        		printf(" %d", nAnswer[i]);
        	puts("");
        }
	}


	return 0;
}



#endif