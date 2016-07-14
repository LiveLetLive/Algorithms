#include "CommonHeader.h"

#ifdef UVA_10819_TROUBLE_OF_13_DOTS
READ_INPUT(UVA_10819_TROUBLE_OF_13_DOTS)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 105
#define MAXM 10205

int m, n;
int p[MAXN];
int f[MAXN];
int dp[MAXN][MAXM];

void reset()
{
	FOR(i, 0, MAXN)
	{
		p[i] = 0, f[i] = 0;
		FOR(j, 0, MAXM)
			dp[i][j] = -1; 
	}
}


int calc(int id, int spentM)
{
	int val = -1;

	if(spentM > m && m < 1800)
		return -1000;
	if(spentM > m + 200)
		return -1000;

	if(id == n)
	{
		if(spentM > m && spentM <= 2000)
			return -1000;
		return 0;
	}

	if(dp[id][spentM] != -1)
		return dp[id][spentM];

	int x = calc(id+1, spentM);
	int y = f[id] + calc(id+1, spentM + p[id]);

	val = max(x, y);

	dp[id][spentM] = val;
	return dp[id][spentM]; 
}

int FindMax()
{
	return calc(0, 0);
}

int main()
{
	int T = 0;

	while(scanf("%d %d", &m, &n) != EOF)
	{
		reset();
		FOR(i, 0, n)
			scanf("%d %d ", &p[i], &f[i]);

		printf("%d\n", FindMax());
	}

	return 0;
}

#endif