#include "CommonHeader.h"

#ifdef UVA_10721_BAR_CODES
READ_INPUT(UVA_10721_BAR_CODES)

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
#define MAXN 51
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N, K, M;

int osIdxCnt;
ll dp[2][MAXN][MAXN][MAXN]; //[i][j][k]

void reset()
{
	FOR(m, 0, 2)
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		FOR(k, 0, MAXN)
		dp[m][i][j][k] = -1;
}

ll solve(int rg, int idx, int remK, int remM)
{
	if( idx == N && remK == 0 && remM != 0)
		return 1;

	if(idx > N) return 0;
	if(remM <= 0) return 0;
	if(remK < 0) return 0;


	if(dp[rg][idx][remK][remM] != -1)
		return dp[rg][idx][remK][remM];

	ll ans = 0;

	if(rg == 1) // Red
	{
		ans += solve(1, idx+1, remK, remM - 1);
		ans += solve(0, idx+1, remK - 1, M);
	}
	else
	{
		ans += solve(0, idx+1, remK, remM - 1);
		ans += solve(1, idx+1, remK - 1, M);
	}
	return dp[rg][idx][remK][remM] = ans; 
}

int main()
{
	while(scanf("%d %d %d ", &N, &K, &M) != EOF)
	{
		reset();
		ll ans = solve(1, 1, K-1, M);
		printf("%lld\n", ans);
	}
	return 0;
}


#endif