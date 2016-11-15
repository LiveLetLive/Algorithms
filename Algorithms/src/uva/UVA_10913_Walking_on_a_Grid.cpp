#include "CommonHeader.h"

#ifdef UVA_10913_WALKING_ON_A_GRID
READ_INPUT(UVA_10913_WALKING_ON_A_GRID)

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
#define MAXN 77
#define INF 0x3f3f3f3fL
typedef int ll;
#define MAXNEG 8

int N, K;
int g[MAXN][MAXN];
ll dp[MAXN][MAXN][MAXNEG][3];
int vis[MAXN][MAXN][MAXNEG][3];

int foundOnce = false;

void reset()
{
	foundOnce = false;
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
	{
		FOR(k, 0, MAXNEG)
			FOR(d, 0, 3)
			dp[i][j][k][d] = -INF, vis[i][j][k][d] = 0;
		g[i][j] = 0;
	}
}

int dr[] = { 1, 0, 0 };
int dc[] = { 0, -1, 1 };

ll solve(int i, int j, int remK, int prevDir)
{
	int &ans = dp[i][j][remK][prevDir];

	if(vis[i][j][remK][prevDir])
		return dp[i][j][remK][prevDir];

	if(remK > K) return ans = -INF;
	
	if(i == N-1 && j == N-1)
	{
		foundOnce = true;
		return ans = g[N-1][N-1];;
	}

	ans = -INF;

	FOR(x, 0, 3)
	{
		int ni = i + dr[x];
		int nj = j + dc[x];

		if(ni < 0 || nj < 0 || ni >= N || nj >= N)
			continue;

		if((prevDir + x) == 3)
			continue;

		int tmp = (g[ni][nj] < 0);
		int sum = solve(ni, nj, remK + tmp, x);

		if(sum != -INF)
			ans = max(ans, sum + g[i][j]);
	}

	vis[i][j][remK][prevDir] = 1;

	return dp[i][j][remK][prevDir] = ans;
}

int main()
{
	int T = 0;
	while(scanf("%d %d ", &N, &K))
	{
		if(N == 0 && K == 0)
			break;

		reset();

		FOR(i, 0, N)
			FOR(j, 0, N)
			scanf("%d ", &g[i][j]);

		ll ans = solve(0, 0, (g[0][0] < 0), 0);

		if(foundOnce)
			printf("Case %d: %d\n", ++T, ans);
		else
			printf("Case %d: impossible\n", ++T);
	}
	return 0;
}

#endif
