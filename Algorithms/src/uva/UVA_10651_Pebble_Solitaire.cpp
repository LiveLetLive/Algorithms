#include "CommonHeader.h"

#ifdef UVA_10651_PEBBLE_SOLITAIRE
READ_INPUT(UVA_10651_PEBBLE_SOLITAIRE)

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
#define MAXN 12
#define INF 0x3f3f3f3fL
typedef long long ll;

int dp[1<<MAXN];

void reset()
{
	FOR(i, 0, 1<<MAXN)
		dp[i] = INF;
}

bool CheckMove(int bitmask, int &i, int& tgt, int& disappear)
{
	//Check Left Move
	if(i > 1)
		if(bitmask & (1<<(i-1)))
			if((bitmask & (1<<(i-2))) == 0)
			{
				tgt = i-2, disappear = i-1;
				return true;
			}

			//Check Right Move
			if(i < 10)
				if(bitmask & (1<<(i+1)))
					if((bitmask & (1<<(i+2))) == 0)
					{
						tgt = i+2, disappear = i+1;
						return true;
					}

					return false;
}

int solve(int bitmask, int idx)
{
	int count = 0;
	FOR(i, 0, 12)
		if(bitmask & (1 << i))
			count++;

	if(count == 1) return 1;

	if(dp[bitmask] != INF)
		return dp[bitmask];

	int ans = INF;
	FOR(i, 0, 12)
		if(bitmask & (1 << i))
		{
			int tgt = 0;
			int disappear = 0;
			if(CheckMove(bitmask, i, tgt, disappear))
			{
				int newbitmask = (bitmask & (~((1<<i)|(1<<disappear))) | (1<<tgt));
				ans = min(ans, solve(newbitmask, i));
			}
		}

		if(ans == INF)
		{
			int count = 0;
			FOR(i, 0, 12)
				if(bitmask & (1 << i))
					count++;
			ans = count;
		}
		return dp[bitmask] = ans;
}

int main()
{
	int T;
	reset();
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		int bitmask = 0;
		char str[13];
		scanf("%s ", &str);

		FOR(i, 0, 12)
			if(str[i] == 'o')
				bitmask |= (1 << i);
		if(bitmask == 0)
			printf("0\n");
		else
			printf("%d\n", solve(bitmask, 0));
	}
	return 0;
}

#endif
