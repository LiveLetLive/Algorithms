#include "CommonHeader.h"

#ifdef UVA_12047_HIGHEST_PAID_TOLL
READ_INPUT(UVA_12047_HIGHEST_PAID_TOLL)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 10001
#define INF 1000000000L
typedef int ll;

class Node
{
public:
	int j;
	ll cost;
};

Node g[MAXN][MAXN];
Node rg[MAXN][MAXN];
ll dist[MAXN];
ll dist2[MAXN];
bool in_queue[MAXN];
int cnt[MAXN];
int rcnt[MAXN];
int T, N, M, s, t, P;

void reset()
{
	FOR(i, 0, N+1)
	{
		FOR(j, 0, N+1)
			g[i][j].cost = -1, rg[i][j].cost = -1;

		cnt[i] = 0;
		rcnt[i] = 0;
	}
}

ll bfs(int src)
{
	FOR(i, 0, N+1)
		dist[i] = INF, in_queue[i] = 0;

	ll maxToll = -1;

	queue<int> q;
	q.push(src);
	dist[src] = 0;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = false;

		FOR(ss, 0, cnt[u])
		{
			int v = g[u][ss].j;

			if(g[u][ss].cost != (ll)-1 && (dist[v] > (dist[u] + g[u][ss].cost)))
			{
				dist[v] = min(dist[v] , dist[u] + g[u][ss].cost);
				if(in_queue[v] == false)
					q.push(v), in_queue[v] = true;
			}
		}
	}

	return 0;
}

ll bfs2(int src)
{
	FOR(i, 0, N+1)
		dist2[i] = INF, in_queue[i] = 0;

	ll maxToll = -1;

	queue<int> q;
	q.push(src);
	dist2[src] = 0;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = false;

		FOR(ss, 0, rcnt[u])
		{
			int v = rg[u][ss].j;

			if(rg[u][ss].cost != (ll)-1 && (dist2[v] > (dist2[u] + rg[u][ss].cost)))
			{
				dist2[v] = min(dist2[v] , dist2[u] + rg[u][ss].cost);
				if(in_queue[v] == false)
					q.push(v), in_queue[v] = true;
			}
		}
	}

	return 0;
}


int main()
{
	scanf("%d ", &T);

	FOR(t1, 0, T)
	{
		scanf("%d %d %d %d %d ", &N, &M, &s, &t, &P);
		reset();

		FOR(j, 0, M)
		{
			int x, y;
			ll c;
			scanf("%d %d %d ", &x, &y, &c);

			int idx = cnt[x]++;
			g[x][idx].cost = c;
			g[x][idx].j = y;

			idx = rcnt[y]++;
			rg[y][idx].cost = c;
			rg[y][idx].j = x;
		}

		bfs(s);
		bfs2(t);

		int high = -1;

		FOR(u, 0, N+1)
		FOR(j, 0, cnt[u])
		{
			int v = g[u][j].j;
			int c = g[u][j].cost;

			if(
				c != -1 
				&& dist[u] != INF 
				&& dist2[v] != INF 
				&& (dist[u] + c + dist2[v]) <= P
				)
				high = max(high, c);
		}

		printf("%d\n", high);
	}
	return 0;
}

// Not working code, dont know the reason, maybe self loops should be added to the paths.
//
//#include <iostream>
//#include <cstdio>
//#include <queue>
//
//	using namespace std;
//
//#define FOR(i, init, count) for(int i = init; i < count; i++)
//#define MAXN 10001
//#define INF 1000000000L
//typedef long long ll;
//
//class Node
//{
//public:
//	int j;
//	ll cost;
//};
//
//Node g[MAXN][MAXN];
//ll dist[MAXN];
//ll maxRoad[MAXN];
//bool in_queue[MAXN];
//int cnt[MAXN];
//int T, N, M, s, t, P;
//
//void reset()
//{
//	FOR(i, 0, N+1)
//	{
//		FOR(j, 0, N+1)
//			g[i][j].cost = -1;
//
//		cnt[i] = 0;
//	}
//}
//
//ll bfs(int src)
//{
//	FOR(i, 0, N+1)
//		dist[i] = INF, maxRoad[i] = -1, in_queue[i] = false;
//
//	ll maxToll = -1;
//
//	queue<int> q;
//	q.push(src);
//	dist[src] = 0;
//	in_queue[src] = true;
//
//	while(!q.empty())
//	{
//		int u = q.front();
//		q.pop();
//		in_queue[u] = false;
//
//		if(u == t)
//		{
//			maxToll = max(maxToll, maxRoad[t]);
//		}
//		FOR(ss, 0, cnt[u])
//		{
//			int v = g[u][ss].j;
//
//			if(g[u][ss].cost != (ll)-1 && ((g[u][ss].cost + dist[u]) <= P))
//			{
//				dist[v] = dist[u] + g[u][ss].cost;
//				maxRoad[v] = max(maxRoad[v], max(maxRoad[u], g[u][ss].cost));
//				if(in_queue[v] == false)
//					q.push(v), in_queue[v] = true;
//			}
//		}
//	}
//
//	return maxToll;
//}
//
//int main()
//{
//	scanf("%d ", &T);
//
//	FOR(t1, 0, T)
//	{
//		scanf("%d %d %d %d %d ", &N, &M, &s, &t, &P);
//		reset();
//
//		FOR(j, 0, M)
//		{
//			int x, y;
//			ll c;
//			scanf("%d %d %lld ", &x, &y, &c);
//
//			int idx = cnt[x]++;
//			g[x][idx].cost = c;
//			g[x][idx].j = y;
//		}
//
//		ll high = bfs(s);
//		printf("%lld\n", high);
//	}
//	return 0;
//}

#endif