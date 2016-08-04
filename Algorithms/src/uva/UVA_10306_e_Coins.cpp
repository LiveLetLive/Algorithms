#include "CommonHeader.h"

#ifdef UVA_10306_E_COINS
READ_INPUT(UVA_10306_E_COINS)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 305
#define MAXG 105
#define MAXC 105
#define INF 100000000

int N;
int M;
int S;
int dp[MAXN][MAXN];
int c1[MAXN];
int c2[MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dp[i][j] = INF, c1[i] = 0, c2[i] = 0;
}


int main()
{
	int T = 0;
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d %d ", &M, &S);

		FOR(i, 0, M)
			scanf("%d %d ", &c1[i], &c2[i]);

		dp[0][0] = 0;

		FOR(i, 0, M)
			FOR(j, c1[i], S+1)
			FOR(k, c2[i], S+1)
			dp[j][k] = min(dp[j][k], 1 + dp[j - c1[i]][k - c2[i]]);

		int ans = INF;

		FOR(j, 0, S+1)
			FOR(k, 0, S+1)
			if(j*j+k*k == S*S && dp[j][k]!= INF)
				ans = min(ans, dp[j][k]);

		if(ans == INF)
			printf("not possible\n");
		else
			printf("%d\n", ans);
	}

	return 0;
}


#endif