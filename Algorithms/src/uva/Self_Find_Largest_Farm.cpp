#include "CommonHeader.h"

#ifdef SELF_FIND_BIGGEST_RECTANGLE
READ_INPUT(SELF_FIND_BIGGEST_RECTANGLE)

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
#define MAXN 16
#define MAXL 51
#define INF 0x3f3f3f3fL
typedef long long ll;
typedef short us;
int N;
us s[MAXN];
us sum[1<<MAXN];

//#define USE_HEAP

#ifdef USE_HEAP
class DP
{
public:
	short data[MAXN][MAXL][MAXL][MAXL];
};

DP *dp = NULL;
#else
short dp[MAXN][MAXL][MAXL][MAXL];
#endif

void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, MAXL)
		FOR(k, 0, MAXL)
		FOR(m, 0, MAXL)
#ifdef USE_HEAP
		dp->data[i][j][k][m] = 0;
#else
		dp[i][j][k][m] = 0;
#endif

	FOR(i, 0, 1 << N)
		sum[i] = 0;
}

us solve(us idx, us l1, us l2, us w1, int bitmask)
{
	us w2 = sum[bitmask] - (l1 + l2 + w1);

	if(idx == N)
	{
		if(l1 && w1 && l1 == l2 && w1 == w2)
			return l1*w1;
		else 
			return -1;
	}

	if(l1 >= MAXL || l2 >= MAXL || w1 >= MAXL || w2 >= MAXL)
		return -1;

#ifdef USE_HEAP
	if(dp->data[idx][l1][l2][w1] != 0)
		return dp->data[idx][l1][l2][w1];
#else
	if(dp[idx][l1][l2][w1] != 0)
		return dp[idx][l1][l2][w1];
#endif

	us ans = -1;

	ans = max(ans, solve(idx+1, l1 + s[idx],	l2,				w1,				bitmask | (1 << idx)));
	ans = max(ans, solve(idx+1, l1 ,			l2 + s[idx],	w1,				bitmask | (1 << idx)));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1 + s[idx],	bitmask | (1 << idx)));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1,				bitmask | (1 << idx)));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1,				bitmask));

#ifdef USE_HEAP
	return dp->data[idx][l1][l2][w1] = ans;
#else
	return dp[idx][l1][l2][w1] = ans;
#endif
}

int main()
{
	int T;
#ifdef USE_HEAP
	dp = new DP;
#endif
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();

		FOR(i, 0, N)
			scanf("%d ", &s[i]);

		FOR(i, 0, 1 << N)
			FOR(j, 0, N)
			if(i & (1<<j))
				sum[i] += s[j];

		//if(t > 10) continue;

		printf("%d\n", solve(0, 0, 0, 0, 0));
	}

#ifdef USE_HEAP
	//delete dp;
#endif
	return 0;
}

#endif
