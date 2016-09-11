#include "CommonHeader.h"

#ifdef UVA_1201_TAXI_CAB_SCHEME
READ_INPUT(UVA_1201_TAXI_CAB_SCHEME)

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
#define MAXN 501
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

class Trip
{
public:
	Trip(){};
	int a,c,b,d;
	int start;
	int len;
};

Trip tr[MAXN];

int match[MAXN*2];
int vis[MAXN*2];
int N;

int g[MAXN*2][MAXN*2];
int cnt[MAXN*2];

void reset()
{
	FOR(i, 0, 2*N+1)
	{
		FOR(j, 0, 2*N+1)
			g[i][j] = 0;
		cnt[i] = 0;
	}
}

void PrepareGraph()
{
	FOR(i, 0, N)
		FOR(j, 0, N)
	{
		if(j == i) continue;

		int timeToReachNext = abs(tr[i].c - tr[j].a) + abs(tr[i].d - tr[j].b) ;

		if(tr[i].start + tr[i].len + timeToReachNext < tr[j].start)
		{
			g[i][cnt[i]++] = j+N;
		}
	}
}


int Aug(int l) 
{ 
	if (vis[l]) 
		return 0; // return 0 otherwise
	vis[l] = 1;

	FOR(j, 0, cnt[l])
	{
		int r = g[l][j];
		if (match[r] == -1 || Aug(match[r])) 
		{
			match[r] = l; 
			return 1; // found 1 matching
		}
	}
	return 0; // no matching
}

int FindMCBM()
{
	int MCBM = 0;

	FOR(i, 0, 2*N)
		match[i] = -1; // V is the number of vertices in bipartite graph

	FOR(l, 0, N)
	{ 
		FOR(i, 0, N*2)
			vis[i] = 0;

		MCBM += Aug(l);
	}

	return MCBM;
}
int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		int h, m;

		scanf("%d ", &N);
		reset();

		FOR(i, 0, N)
		{
			int a,b,c,d;
			scanf("%d:%d", &h, &m);
			tr[i].start = h*60+m;

			scanf("%d %d %d %d ", &a, &b, &c, &d);

			tr[i].len = abs(a-c) + abs(b-d);
			tr[i].a = a;
			tr[i].b = b;
			tr[i].c = c;
			tr[i].d = d;
		}

		PrepareGraph();
		int mcbm = FindMCBM();
		printf("%d\n", N - mcbm);
	}
	return 0;
}

#endif
