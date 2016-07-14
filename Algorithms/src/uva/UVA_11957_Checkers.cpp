#include "CommonHeader.h"


#ifdef UVA_11957_CHECKERS
READ_INPUT(UVA_11957_CHECKERS)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 101
#define INF 10000000

char g[MAXN][MAXN];
int dp[MAXN][MAXN];
int wi, wj;
int T, N;
void reset()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			dp[i][j] = -1;
	}
}

int dc[] = { -1,  1 };
int dr[] = { -1, -1 };

int dc1[] = { -2,  2 };
int dr1[] = { -2, -2 };

int move(int i, int j)
{
	if(i < 0 || j < 0) return -1;
	if(i >= N || j >= N) return -1;
	if(g[i][j] == 'B') return -1;
	if(i == 0) return 1;
	if(dp[i][j] != -1) return dp[i][j];
	int paths = 0;

	FOR(s, 0, 2)
	{
		int res = move(i + dr[s], j + dc[s]);
		if(res == -1)
			res = move(i + dr1[s], j + dc1[s]);
		if(res == -1)
			res = 0;

		paths += res;
		paths %= 1000007;
	}

	return dp[i][j] = paths;
}

int main()
{
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();
		char str[MAXN] = { 0, };
		scanf("%d ", &N);

		FOR(i, 0, N)
		{
			scanf("%s ", &str);
			FOR(j, 0, N)
			{
				g[i][j] = str[j];
				if(str[j] == 'W')
					wi = i, wj = j;
			}
		}

		int ans = move(wi, wj);
		printf("Case %d: %d\n", t+1, ans);
	}

	return 0;
}

#endif