#include "CommonHeader.h"

#ifdef UVA_702_THE_VINDICTIVE_COACH
READ_INPUT(UVA_702_THE_VINDICTIVE_COACH)

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
#define MAXN 23
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N, C;

ll dp[MAXN][1<<MAXN];


void reset()
{
	FOR(i, 0, N+1)
		FOR(j, 0, 1<<(N+1))
		dp[i][j] = -1;

}

ll solve(int idx, int bitmask, int sh)
{
	if(bitmask == ((1 << N) - 1))
		return 1;

	if(dp[idx][bitmask] != -1)
		return dp[idx][bitmask];

	ll ans = 0;

	// We are at captain, find all smaller than him, if not found, find smallest from that highest
	if(idx == C)
	{
		int found = false;
		FOR(i, 0, C)
			if((bitmask & (1 << i)) == 0)
				ans += solve(i, bitmask | (1 << i), 1), found = true;

		if(found == false)
			FOR(i, C+1, N)
			if((bitmask & (1 << i)) == 0) {
				ans += solve(i, bitmask | (1 << i), 2); break;
			}
	}
	else
	{
		bool found = false;
		if(sh == 0 || sh ==2)
		{
			FOR(i, 0, idx)
				if((bitmask & (1 << i)) == 0)
					ans += solve(i, bitmask | (1 << i), 1), found = true;
		}
		
		if(sh == 1 || sh ==2)
		{
			FOR(i, idx+1, N)
				if((bitmask & (1 << i)) == 0) 
					ans += solve(i, bitmask | (1 << i), 0), found = true;
		}
	}

	return dp[idx][bitmask] = ans;
}

int main()
{
	int T;

	while(scanf("%d %d ", &N, &C) != EOF)
	{
		C--;
		reset();
		printf("%lld\n", solve(C, 1<<C, 0));
	}
	return 0;
}

#endif
