#include "CommonHeader.h"

#ifdef UVA_562_DIVIDING_COINS
READ_INPUT(UVA_562_DIVIDING_COINS)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <math.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 102
#define MAXV 50000
#define INF 500000

int c[MAXN];
int dp[MAXV][MAXN];
int N;

void reset()
{
	FOR(i, 0, MAXV)
		FOR(j, 0, MAXN)
		dp[i][j] = -1, c[j] = 0;

}

int calc(int d, int idx)
{
	if(dp[d][idx] != -1) return dp[d][idx] ;

	if(idx > N)
		return d;

	int d1;
	int d2;

	d1 = calc(abs(d + c[idx]), idx+1);
	d2 = calc(abs(d - c[idx]), idx+1);

	int ans = min(abs(d1), abs(d2));

	return dp[d][idx] = ans;
}

int main()
{
	int T = 0;

	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d", &N);

		FOR(i, 0, N)
			scanf("%d ", &c[i]);

		int ans = calc(0, 0);

		printf("%d\n", abs(ans));
	}
	return 0; 
}
#endif