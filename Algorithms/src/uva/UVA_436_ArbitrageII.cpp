#include "CommonHeader.h"


#ifdef UVA_436_ARBITRAGEII
READ_INPUT(UVA_436_ARBITRAGEII)

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <math.h>

#define FOR(i, init, count) for(int i = init; i < count; i++)

	const int MAXN = 31;
const int MAXL = 51;

double dp[MAXN][MAXN];
char country[MAXN][MAXL];

int N;
int E;

inline double myMin(double a, double b)
{
	return (a<b)?a:b;
}

inline double myMax(double a, double b)
{
	return (a>b)?a:b;
}

int FindIndex(char *str)
{
	FOR(i, 0, MAXN)
	{
		if(strcmp(str, country[i]) == 0)
			return i;
	}

	return -1;
}

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dp[i][j] = 0;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXL)
		country[i][j] = 0;
}


int main()
{
	int t = 0;
	while(scanf("%d ", &N) == 1)
	{
		t++;
		char c1[MAXL] = {};
		char c2[MAXL] = {};

		if(N == 0)
			break;

		reset();

		FOR(i, 0, N)
			scanf("%s ", &country[i]), dp[i][i] = 1.0;

		scanf("%d ", &E);

		FOR(i, 0, E)
		{
			double tmp;
			scanf("%s %lf %s", &c1, &tmp, &c2);
			dp[FindIndex(c1)][FindIndex(c2)] = tmp;
		}

		FOR(k, 0, N)
			FOR(i, 0, N)
			FOR(j, 0, N)
		{
			double tmp = dp[i][k] * dp[k][j];
			if(tmp > dp[i][j])
				dp[i][j] = tmp;
		}

		bool found = false;
		FOR(i, 0, N)
			if(dp[i][i] > 1 + 1e-5)
				found = true;

		if(found)
			printf("Case %d: Yes\n", t);
		else
			printf("Case %d: No\n", t);
	}
}

#endif