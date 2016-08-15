#include "CommonHeader.h"

#ifdef UVA_10645_MENU
READ_INPUT(UVA_10645_MENU)

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
#define MAXK 23
#define MAXN 52
#define MAXM 102

#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int K, N, M;

int c[MAXN];
int b[MAXN];
int dp[MAXK][MAXN][MAXM];
int Prev[MAXK][MAXN][MAXM];

void PrintDPTable()
{
	FOR(i, 1, K+1)
	{
		FOR(k, 1, M+1)
		{
			FOR(j, 1, N+1)
			{
				printf("%2d ", dp[i][j][k]);
			}
			printf("\n");
		}
		printf("-----------\n");
	}
}

void reset()
{
	FOR(i, 0, MAXK)
		FOR(j, 0, MAXN)
		FOR(k, 0, MAXM)
		dp[i][j][k] = 0, Prev[i][j][k] = 0;
}

void PrintPath(int i, int j, int k)
{
	if(i == 0) return;
	PrintPath(i-1, Prev[i][j][k], k - Prev[i][j][k]);
	printf("%d ", Prev[i][j][k]);
}

int main()
{
	int T;
	while(scanf("%d %d %d ", &K, &N, &M), K, N, M)
	{
		reset();
		FOR(i, 1, N+1)
			scanf("%d %d ", &c[i], &b[i]), b[i] *= 2;

		FOR(i, 1, K+1)
			FOR(j, 1, N+1)
			FOR(k, 1, M+1)
		{
			if(c[j] <= k)
			{
				int sameD = dp[i-1][j][k-c[j]] + (b[j] / 2);
				int newD = dp[i-1][j-1][k-c[j]] + b[j];

				if(sameD > newD)
					dp[i][j][k] += sameD, Prev[i][j][k] = j;
				else
					dp[i][j][k] += newD, Prev[i][j][k] = j-1;
			}
		}

		PrintDPTable();

		int ans = 0;
		int idx = 0;
		FOR(j, 1, N+1)
		{
			if(dp[K][j][M] != 0)
				ans = max(ans, dp[K][j][M]), idx = j;
		}

		if(ans == 0)
			printf("0.0\n");
		else
		{
			printf("%d.%1d\n", ans / 2, (ans % 2)*5);
			PrintPath(K, idx, M);
			printf("\n");
		}
	}
	return 0;
}

#endif
