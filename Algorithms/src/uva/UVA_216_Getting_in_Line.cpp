#include "CommonHeader.h"

#ifdef UVA_216_GETTING_IN_LINE
READ_INPUT(UVA_216_GETTING_IN_LINE)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <math.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 12
#define INF 500000

int N;
int cx[MAXN];
int cy[MAXN];

class State
{
public:
	double d;
	int pos;
	int mask;
};

State dp[MAXN][1<<MAXN];
double dist[MAXN][MAXN];

void reset()
{
	FOR(i, 0, (MAXN))
		FOR(j, 0, (1 << MAXN))
		dp[i][j].d = INF, dp[i][j].pos = 0, dp[i][j].mask = 0;
}

double calc(int bitmask, int currPos)
{
	if(bitmask == ((1 << (N)) - 1) )
		return 0;

	if(dp[currPos][bitmask].d != INF)
		return dp[currPos][bitmask].d;


	double ans = INF;
	int index = 0;
	int bmask = 0;

	FOR(i, 0, N)
		if(!(bitmask & (1 << i)))
		{
			if(ans > calc( bitmask | (1 << i), i) + dist[i][currPos])
			{
				ans = calc( bitmask | (1 << i), i) + dist[i][currPos];
				index = i;
				bmask = bitmask | (1 << i);
			}
		}

		dp[currPos][bitmask].d = ans;
		dp[currPos][bitmask].mask = bmask;
		dp[currPos][bitmask].pos = index;

		return dp[currPos][bitmask].d;
}

void PrintSol(int idx)
{
	int ppos = dp[idx][0].pos;
	int pmask = dp[idx][0].mask;
	FOR(i, 0, N-1)
	{
		int npos = dp[ppos][pmask].pos;
		int nmask = dp[ppos][pmask].mask;

		printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", 
			cx[ppos],
			cy[ppos],
			cx[npos],
			cy[npos],
			dist[npos][ppos] + 16
			);

		ppos = npos;
		pmask = nmask;
	}
}

int main()
{
	int t = 0;

	while(scanf("%d", &N), N)
	{
		reset();

		FOR(i, 0, N)
			scanf("%d %d ", &cx[i], &cy[i]);

		FOR(i, 0, N)
			FOR(j, 0, N)
			dist[i][j] = dist[j][i] = sqrt(  (cx[i] - cx[j]) * (cx[i] - cx[j]) 
			+ (cy[i] - cy[j]) * (cy[i] - cy[j]) );

		printf("**********************************************************\n");
		printf("Network #%d\n" , ++t);

		double ans = INF;
		int minI = 0;
		FOR(i, 0, N)
		{
			double tmp = calc(0, i);
			if(ans > tmp)
			{
				ans = tmp;
				minI = i;
			}
		}

		PrintSol(minI);

		printf("Number of feet of cable required is %.2lf.\n", ans + (16 * (N-1)));
	}
	return 0; 
}
#endif