#include "CommonHeader.h"

#ifdef UVA_10364_SQUARE
READ_INPUT(UVA_10364_SQUARE)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;
#define INF 0x3FFFFFFF
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 21

int N;

int s[MAXN];
int dp[1 << MAXN];
int sum;

void reset()
{
	sum = 0;
	FOR(i, 0, MAXN)
		s[i] = 0;
	FOR(i, 0, (1<<MAXN))
		dp[i] = -1;
}

bool solve(int len, int bitmask)
{
	if(len > (sum / 4))
		return false;

	if(dp[bitmask] != -1)
		return dp[bitmask];

	if(len == (sum / 4))
	{
		if(bitmask == ((1 << N) - 1))
			return true;
		len = 0;
	}

	FOR(i, 0, N)
		if(!(bitmask & (1 << i)))
			if(solve(len + s[i], bitmask | (1 << i)))
				return true;

	return dp[bitmask] = false;
}

int main()
{
	int T;
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d", &N);
		FOR(i, 0, N)
			scanf("%d", &s[i]), sum += s[i];

		if(sum % 4)
		{
			printf("no\n");
			continue;
		}

		if(solve(0, 0))
			printf("yes\n");
		else 
			printf("no\n");
	}

	return 0;
}


#endif