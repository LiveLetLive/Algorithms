#include "CommonHeader.h"

#ifdef UVA_836_LARGEST_SUBMATRIX
READ_INPUT(UVA_836_LARGEST_SUBMATRIX)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

typedef long long ll;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 28
#define INF 0xfffffffffLL

int N, M, T;
char gr[MAXN][MAXN];
int dp[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gr[i][j] = 0, dp[i][j] = 0;
}

int solve()
{
	return 0;
}

void PrintGrid()
{
	FOR(i, 0, N+1)
		printf("%s\n", gr[i]);
}

int main()
{
	int T1 = 0;
	scanf("%d ", &T1);
	FOR(t, 0, T1)
	{
		int idx = 0;
		reset();
		while(scanf("%s ", &gr[idx]))
			if(gr[idx++][0] == 0)
				break;

		N = idx - 1;
		FOR(i, 1, N+1)
			FOR(j, 1, N+1)
			dp[i][j] = gr[i-1][j-1] - '0';

		PrintGrid();
		solve();
		printf("%d\n", 0); 
	}
	return 0;  
} 
#endif