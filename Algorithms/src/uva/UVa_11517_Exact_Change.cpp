
#include "CommonHeader.h"

#ifdef UVA_11517_EXACT_CHANGE
READ_INPUT(UVA_11517_EXACT_CHANGE)

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

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1000005
#define MAXG 105
#define MAXC 105
#define INF 0x3FFFFFFF
typedef long long ll;

int dp[MAXN];
int dc[MAXN];

int c[MAXC];
int C;
int V;
static int counter = 0;
int sumV;

void reset()
{
	counter = 0;
	FOR(j, 0, 30000+1)
		dp[j] = INF, dc[j] = INF;
}


void solve()
{
	dp[0] = 0;
	dc[0] = 0;

	FOR(c1, 0, C)
		for (int i = 30001 - c[c1] - 1; i >= 0; i--)
			if(dp[i] != INF)
				dp[i + c[c1]] = min(dp[i + c[c1]], dp[i]+1);

	FOR(x, V, sumV+1)
		if(dp[x] != INF)
		{
			printf("%d %d\n", x, dp[x]);
			return;
		}
}

int main()
{
	int T;
	scanf("%d", &T);
	FOR(t, 0, T)
	{
		scanf("%d", &V);
		scanf("%d", &C);

		sumV = 0;
		FOR(c1, 0, C)
			scanf("%d", &c[c1]), sumV += c[c1];
		reset();

		solve();
	}

	return 0;
}

#endif