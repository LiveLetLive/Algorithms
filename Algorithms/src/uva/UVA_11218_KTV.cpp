#include "CommonHeader.h"

#ifdef UVA_11218_KTV
READ_INPUT(UVA_11218_KTV)

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
#define MAXN 85
#define INF 0x3f3f3f3fL
typedef long long ll;

int comb[MAXN];
int score[MAXN];
int dp[MAXN][1 << 9];
int N;

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, 1<<9)
		dp[i][j] = -INF;

	FOR(i, 0, MAXN)
		comb[i] = 0, score[i] = 0;
}

int solve(int bitmask, int idx)
{
	if(bitmask == ((1<<9)-1))
		return 0;

	if(idx >= N)
		return -INF;

	if(dp[idx][bitmask] != -INF) 
		return dp[idx][bitmask];

	int ans = -1;
	//Take (no overlap, unique sets)
	if((bitmask & comb[idx]) == 0)
	{
		int tmp = solve(bitmask | comb[idx], idx+1);
		if(tmp >= 0)
			ans = tmp + score[idx];
	}
	//Dont take
	ans = max(ans, solve(bitmask, idx+1));

	return dp[idx][bitmask] = ans;
}

int main()
{
	int t = 0;
	while(scanf("%d ", &N), N)
	{
		reset();
		FOR(i, 0, N)
		{
			int p1, p2, p3, s;
			scanf("%d %d %d %d ", &p1, &p2, &p3, &s);
			p1--, p2--, p3--;
			comb[i] = ((1<<p1) | (1<<p2) |(1<<p3));
			score[i] = s;
		}

		int ans = solve(0, 0);
		if(ans < 0) ans = -1;
		printf("Case %d: %d\n",++t, ans);
	}
	return 0;
}

#endif
