#include "CommonHeader.h"

#ifdef UVA_10626_BUYING_COKE
READ_INPUT(UVA_10626_BUYING_COKE)

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
#define MAXC 151
#define MAXC5 101
#define MAXC10 51
#define INF 0x3f3f3f3fL
typedef long long ll;

int C, Val, C5, C10;

int dp[MAXC][MAXC5][MAXC10];

void reset()
{
	FOR(i, 0, MAXC)
		FOR(j, 0, MAXC5)
		FOR(k, 0, MAXC10)
		dp[i][j][k] = INF;
}

int solve(int c, int c5, int c10)
{
	if(c == C)
		return 0;

	int c1 = Val - (c * 8) - (5 * c5) - (10 * c10);

	if(dp[c][c5][c10] != INF)
		return dp[c][c5][c10];

	int ans = INF;
	if(c10)
		ans = min (ans, 1 + solve(c + 1, c5, c10 - 1));
	if(c10 && c1 > 2)
		ans = min (ans, 4 + solve(c + 1, c5 + 1, c10 - 1));
	if(c5 > 1)
		ans = min (ans, 2 + solve(c + 1, c5 - 2, c10));
	if(c5 >= 1 && c1 > 2)
		ans = min (ans, 4 + solve(c + 1, c5 - 1, c10));
	if(c1 > 7)
		ans = min (ans, 8 + solve(c + 1, c5, c10));

	return dp[c][c5][c10] = ans;
} 

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		int tmp;
		reset();
		scanf("%d %d %d %d ", &C, &tmp, &C5, &C10);
		Val = tmp + C5*5 + C10*10;

		printf("%d\n", solve(0, C5, C10));
	}
	return 0;
}

#endif
