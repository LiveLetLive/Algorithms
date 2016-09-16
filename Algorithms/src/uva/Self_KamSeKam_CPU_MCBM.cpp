#include "CommonHeader.h"

#ifdef SELF_KAMSEKAM_CPU_MCBM
READ_INPUT(SELF_KAMSEKAM_CPU_MCBM)

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
#define MAXN 1003
#define MAXT 5010
#define MAXDP 0xFFFFF
#define MAXC 5
#define INF 0x3f3f3f3fL
typedef long long ll;

int N, T;
int tm[MAXN], len[MAXN]; 
int cnt[MAXN*2];
int g[MAXN*2][MAXN*2];
int vis[MAXN*2];
int match[MAXN*2];

void reset()
{
	FOR(i, 0, N*2)
		FOR(j, 0, N*2)
		g[i][j] = 0, cnt[i] = 0;
}

void PrepareGraph()
{
		FOR(i, 0, N)
			FOR(j, 0, N)
		{
			if(i == j) continue;
			if((tm[i] + len[i] - tm[j] + len[j] ) <= 10)
				g[i][cnt[i]++] = j+N;
		}
}

int Aug(int l) 
{
	if (vis[l]) 
		return 0;

	vis[l] = 1;

	FOR(j, 0, cnt[l])
	{
		int r = g[l][j];

		if (match[r] == -1 || Aug(match[r])) 
		{
			match[r] = l; 
			return 1;
		}
	}


	return 0;
}

int FindMCBM()
{
	int mcbm = 0;
	FOR(i, 0, N*2)
		match[i] = -1;

	FOR(l, 0, N)
	{
		FOR(i, 0, N)
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
		scanf("%d", &N);

		reset();

		FOR(i, 0, N)
			scanf("%d %d ", &tm[i], &len[i]);



		PrepareGraph();
		int cpus =  N - FindMCBM();
		cpus = cpus > 5 ? -1 : cpus; 

		printf("%d\n", cpus);
	}
	return 0;
}

#endif

