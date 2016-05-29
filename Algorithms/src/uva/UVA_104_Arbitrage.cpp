#include "CommonHeader.h"


#ifdef UVA_104_ARBITRAGE
READ_INPUT(UVA_104_ARBITRAGE)

#include <iostream>
#include <stdio.h>
#include <limits.h>

#define FOR(i, init, count) for(int i = init; i < count; i++)

	const int MAXN = 21;

double dp[MAXN][MAXN][MAXN];
int path[MAXN][MAXN][MAXN];
int N;

inline double myMin(double a, double b)
{
	return (a<b)?a:b;
}

inline double myMax(double a, double b)
{
	return (a>b)?a:b;
}

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		FOR(s, 0, MAXN)
		dp[i][j][s] = 0, path[i][j][s] = i, path[i][j][0] = i;
}


int main()
{
	while(scanf("%d ", &N) == 1)
	{
		reset();

		FOR(i, 0, N)
			FOR(j, 0, N)
		{
			if(i == j)
				dp[i][j][0] = 1;
			else
				scanf("%lf ", &dp[i][j][0]);
		}

		FOR(s, 1, N+1)
			FOR(k, 0, N)
			FOR(i, 0, N)
			FOR(j, 0, N)
		{
			double tmp = dp[i][k][s-1] * dp[k][j][0];
			if(tmp > dp[i][j][s])
			{
				dp[i][j][s] = tmp;
				path[i][j][s] = k;
			}
		}

		bool found = false;

		FOR(s,1,N)
		{
			FOR(i, 0, N)
			{
				if(dp[i][i][s] > 1.01)
				{
					int seq[MAXN] = {};

					seq[s] = path[i][i][s];

					for(int j = s - 1 ; j >= 0; --j)
						seq[j] = path[i][seq[j+1]][j];

					FOR(j, 0, s+1)
						printf("%d ", seq[j]+1);

					printf("%d\n", seq[0]+1);
					found = true;
					break;
				}
			}
			if(found)
				break;
		}

		if(found == false)
			printf("no arbitrage sequence exists\n");

		/*int minRow = -1, minstep = INT_MAX;

		FOR(i, 0, N)
		{
		FOR(s, 1, N+1)
		{
		if(dp[i][i][s] > 1.01)
		{
		if(minstep > s)
		{
		minRow = i, minstep = s;
		break;
		}
		}
		}
		}

		if(minstep == INT_MAX)
		printf("no arbitrage sequence exists\n");
		else
		{
		int seq[MAXN] = {};
		int idx = minRow;
		int size = minstep+1;
		int seqIdx = 0;

		seq[seqIdx++] = minRow+1;

		while(size--)
		{
		seq[seqIdx++] = path[minRow][idx][size]+1;
		idx = path[minRow][idx][size];
		}
		4
		for(int i = seqIdx - 1; i >= 0; --i)
		printf("%d ", seq[i]);

		printf("\n");
		}*/
	}
}

#endif