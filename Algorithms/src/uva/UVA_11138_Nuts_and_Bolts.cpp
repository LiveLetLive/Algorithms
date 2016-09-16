#include "CommonHeader.h"

#ifdef UVA_11138_NUTS_AND_BOLTS
READ_INPUT(UVA_11138_NUTS_AND_BOLTS)

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
#define MAXN 505
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N, B;

int g[MAXN][MAXN];
int cnt[MAXN];
int match[MAXN];
int vis[MAXN];

void reset()
{
	FOR(i, 0, B)
	{
		FOR(j, 0, N)
			g[i][j] = 0;
		cnt[i] = 0;
	}
}

int Aug(int l)
{
	if(vis[l])
		return 0;

	vis[l] = 1;

	FOR(x, 0, cnt[l])
	{
		int r = g[l][x];
		if(match[r] == -1 || Aug(match[r]))
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

	memset(match, -1, sizeof(match));

	FOR(l, 0, B)
	{
		memset(vis, 0, sizeof(vis));
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
		scanf("%d %d ", &B, &N);
		reset();
		FOR(b, 0, B)
			FOR(n, 0, N)
		{
			int tmp;
			scanf("%d ", &tmp);

			if(tmp)
				g[b][cnt[b]++] = n;
		}
		printf("Case %d: ",t+1);
		printf("a maximum of %d nuts and bolts ", FindMCBM());
		printf("can be fitted together\n");
	}
	return 0;
}

#endif
