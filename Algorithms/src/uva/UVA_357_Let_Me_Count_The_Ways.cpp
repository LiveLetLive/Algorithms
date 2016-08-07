
#include "CommonHeader.h"

#ifdef UVA_357_LET_ME_COUNT_THE_WAYS
READ_INPUT(UVA_357_LET_ME_COUNT_THE_WAYS)

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
#define MAXN 30005
#define MAXC 5
#define INF 100000000
typedef long long ll;
int N;

int c[MAXC] = { 1, 5, 10, 25, 50} ;

int main()
{
	ll dp[MAXN] = {};
	dp[0] = 1;

	FOR(i, 0, MAXC)
		FOR(j, 0, MAXN)
		if(j >= c[i])
			dp[j] += dp[j - c[i]];

	while(scanf("%d", &N) != EOF)
	{
		ll ans = dp[N];
		if(ans == 1)
			printf("There is only 1 way to produce %d cents change.\n", N);
		else
			printf("There are %lld ways to produce %d cents change.\n", ans, N);
	}

	return 0;
}


#endif