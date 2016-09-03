#include "CommonHeader.h"

#ifdef UVA_12324_PHILIP_J_FRY_PROBLEM
READ_INPUT(UVA_12324_PHILIP_J_FRY_PROBLEM)

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
#define MAXN 110
#define INF 0x3f3f3f3fL
typedef long long ll;

int ball[MAXN];
int trip[MAXN];
int dp[MAXN][MAXN];
//vector<vector<int> > dp(MAXN, vector<int>(MAXN));
int N;

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dp[i][j] = -1;
}

int solve(int tr, int bRem)
{
	if(tr >= N)
		return 0;

	if(bRem > N)
		bRem = N;

	if(dp[tr][bRem] != -1)
		return dp[tr][bRem];

	int a = INF;
	int b = INF;
	if(bRem > 0)
		a = min(a, (trip[tr]/2) + solve(tr+1, bRem-1+ball[tr]));

	b = min(b, (trip[tr]) + solve(tr+1, bRem+ball[tr]));

	return dp[tr][bRem] = min(a,b);
}

int main()
{
	int T;
	while(scanf("%d ", &N), N)
	{
		reset();
		FOR(i, 0, N)
			scanf("%d %d", &trip[i], &ball[i]);

		printf("%d\n", solve(0,0));
	}
	return 0;
}

#endif
