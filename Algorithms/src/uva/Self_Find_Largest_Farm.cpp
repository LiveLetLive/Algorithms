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
#define MAXL 50
#define INF 0x3f3f3f3fL
typedef long long ll;
typedef short us;
int N;
us s[MAXN];

class DP
{
public:
	short data[MAXL][MAXL][MAXL][MAXL];
};

DP *dp = NULL;

void reset()
{
	FOR(j, 0, MAXL)
		FOR(k, 0, MAXL)
		FOR(m, 0, MAXL)
		FOR(n, 0, MAXL)
		dp->data[j][k][m][n] = 0;
}

us solve(us idx, us l1, us l2, us w1, us w2, int bitmask)
{
	if(idx == N)
	{
		if(l1 && w1 && l1 == l2 && w1 == w2)
			return l1*w1;
		else 
			return -1;
	}

	if(dp->data[l1][l2][w1][w2] != 0)
		return dp->data[l1][l2][w1][w2];

	if(l1 > MAXL || l2 > MAXL || w1 > MAXL || w2 > MAXL)
		return -1;

	us ans = -1;

	ans = max(ans, solve(idx+1, l1 + s[idx],	l2,				w1,				w2, bitmask));
	ans = max(ans, solve(idx+1, l1 ,			l2 + s[idx],	w1,				w2, bitmask));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1 + s[idx],	w2, bitmask));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1,				w2 + s[idx], bitmask));
	ans = max(ans, solve(idx+1, l1 ,			l2,				w1,				w2, bitmask));

	return dp->data[l1][l2][w1][w2] = ans;
}

int main()
{
	int T;
	dp = new DP;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();

		FOR(i, 0, N)
			scanf("%d ", &s[i]);

		printf("%d\n", solve(0, 0, 0, 0, 0, 0));

	}
	delete dp;
	return 0;
}

#endif
