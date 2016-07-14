#include "CommonHeader.h"


#ifdef UVA_988_MANY_PATHS_ONE_DESTINATION
READ_INPUT(UVA_988_MANY_PATHS_ONE_DESTINATION)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;

int N, pathCnt;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 900
#define INF 10000000

int g[MAXN][MAXN];
int cnt[MAXN];
int dp[MAXN];

void reset()
{
	FOR(i, 0, MAXN)
	{
		//FOR(j, 0, MAXN)
		//	g[i][j] = 0;
		cnt[i] = 0;
		dp[i] = INF;
	}
}

int numPaths(int u)
{
	int paths = 0;
	if(u == -1) return 1;
	if(dp[u] != INF) return dp[u];

	FOR(v, 0, cnt[u])
	{
		paths += numPaths(g[u][v]);
	}

	return dp[u] = paths;
}

int main()
{
	while(scanf("%d ", &N) == 1)
	{
		static int first = 0;

		if(first++ != 0)
			printf("\n");

		reset();
		int count;
		FOR(i, 0, N)
		{
			int temp;
			scanf("%d ", &count);
			FOR(j, 0, count)
			{
				scanf("%d ", &temp);
				g[i][cnt[i]++] = temp;
			}
			if(count == 0)
				g[i][cnt[i]++] = -1;
		}

		int ans = numPaths(0);
		printf("%d\n", ans);
	}

	return 0;
}

#endif