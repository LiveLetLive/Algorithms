#include "CommonHeader.h"

#ifdef UVA_11088_END_UP_WITH_MORE_TEAMS
READ_INPUT(UVA_11088_END_UP_WITH_MORE_TEAMS)

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
#define MAXN 20
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int t[MAXN];
int dp[1<<MAXN];
int N;
int mT;
void reset()
{
	mT = -1;
	FOR(j, 0, 1<<MAXN)
		dp[j] = -1;
}

bool FindThreeBits(int idx, int bitmask, int& p1,int&  p2,int&  p3)
{
	FOR(i, idx, N)
	{
		if((bitmask & (1<<i)) == 0)
		{
			p1 = i;
			break;
		}
	}
	FOR(i, p1+1, N)
	{
		if((bitmask & (1<<i)) == 0)
		{
			p2 = i;
			break;
		}
	}
	FOR(i, p2+1, N)
	{
		if((bitmask & (1<<i)) == 0)
		{
			p3 = i;
			break;
		}
	}
	if(p1 == -1 || p2 == -1 || p3 == -1) 
		return false;

	return true;
}

int solve(int bitmask)
{
	if(bitmask == (1<<N)-1)
		return 0;

	if(dp[bitmask] != -1)
		return dp[bitmask];

	int ans = 0;

	FOR(i , 0, N)
		if((bitmask & (1<<i)) == 0)
			FOR(j , i+1, N)
			if((bitmask & (1<<j)) == 0)
				FOR(k , j+1, N)
				if((bitmask & (1<<k)) == 0)
				{
					if((t[i] + t[j] + t[k]) >= 20)
						ans = max(ans, 1+solve(bitmask | (1<<i)| (1<<j)| (1<<k)));
					else
						ans = max(ans, solve(bitmask | (1<<i)| (1<<j)| (1<<k)));
				}


				return dp[bitmask] = ans;
}

int main()
{
	int t1 = 0;
	while(scanf("%d ", &N), N)
	{
		reset();

		FOR(i, 0, N)
			scanf("%d ", &t[i]);

		int ans = solve(0);
		printf("Case %d: %d\n", ++t1, ans == -1?0:ans);
		//printf("Case %d: %d\n", ++t1, mT == -1?0:mT);
	}
	return 0;
}

#endif
