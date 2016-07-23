#include "CommonHeader.h"

#ifdef UVA_10616_DIVISIBLE_GROUP_SUMS
READ_INPUT(UVA_10616_DIVISIBLE_GROUP_SUMS)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

typedef long long ll;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 205
#define MAXM 13
#define MAXD 21
#define INF 0xfffffffffLL

int N, Q, M, D;
int num[MAXN];
int dp[MAXN][MAXM][MAXD];
void reset()
{
	FOR(i, 0, MAXN)
	{
		num[i] = 0;
		FOR(j, 0, MAXM)
		FOR(k, 0, MAXD)
			dp[i][j][k] = -1;
	}
}

int solve(int i, int remM, int rem)
{
	if(remM <= 0)
		if (rem == 0) 
			return 1;
		else 
			return 0;

		if(i >= N)
			return 0;

		if(dp[i][remM][rem] != -1)
			return dp[i][remM][rem];

		int tmp = (rem + num[i]) % D;
		if(tmp < 0) tmp += D;
		
		int ans = solve(i+1, remM - 1, tmp );
		ans += solve(i+1, remM, rem);

		return dp[i][remM][rem] = ans;
}

int main()
{
	int t = 0;
	while(scanf("%d %d ", &N, &Q), N, Q)
	{
		t++;
		reset();
		FOR(i, 0, N)
			scanf("%d ", &num[i]);

		printf("SET %d:\n", t);

		FOR(i, 0, Q)
		{
			FOR(p, 0, MAXN)
				FOR(j, 0, MAXM)
				FOR(k, 0, MAXD)
					dp[p][j][k] = -1;
			scanf("%d %d ", &D, &M);
			printf("QUERY %d: %d\n", i+1, solve(0, M, 0)); 
		}
	}
	return 0;  
} 
#endif