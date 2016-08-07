#include "CommonHeader.h"

#ifdef UVA_11137_INGENUOUS_CUBRENCY
READ_INPUT(UVA_11137_INGENUOUS_CUBRENCY)

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
#define MAXN 10005
#define MAXC 22
#define INF 100000000
typedef long long ll;
int N;

int c[MAXC];

int main()
{
	ll dp[10001] = {};
	dp[0] = 1;

	FOR(i, 1, MAXC)
		c[i] = i*i*i;

	FOR(i, 1, MAXC)
		FOR(j, c[i], 10001)
	{
		if(j >= c[i])
			dp[j] += dp[j - c[i]];
	}

	while(scanf("%d", &N) != EOF)
	{
		ll ans = dp[N];
		printf("%lld\n", ans);
	}

	return 0;
}


#endif