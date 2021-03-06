#include "CommonHeader.h"

#ifdef UVA_983_LOCALIZED_SUMMING_FOR_BLURRING
READ_INPUT(UVA_983_LOCALIZED_SUMMING_FOR_BLURRING)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

typedef long long ll;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1001
#define INF 0xfffffffffLL

int N, M, T;
int gr[MAXN][MAXN];
int ans[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gr[i][j] = 0, ans[i][j] = 0;
}

void PrintGrid()
{
	FOR(i, 0, N)
	{
		FOR(j, 0, N)
			printf("%2d ", gr[i][j]);
		printf("\n");
	}

	printf("//////\n");
}



int main()
{
	int t = 0;

	while(scanf("%d %d ", &N, &M) == 2)
	{
		if(t++ > 0 ) printf("\n");
		reset();
		for(int j = N-1; j >= 0; j--)
			FOR(i, 0, N)
			scanf("%d ", &gr[j][i]);

		//PrintGrid();

		FOR(i, 0, N) FOR(j, 0, N)
		{
			if(i > 0) gr[i][j] += gr[i-1][j];
			if(j > 0) gr[i][j] += gr[i][j-1];
			if(i > 0 && j > 0) gr[i][j] -= gr[i-1][j-1];
		}

		//PrintGrid();

		FOR(i, 0, N-M+1) FOR(j, 0, N-M+1)
		{
			int m = i + (M-1);
			int n = j + (M-1);

			ans[i][j] += gr[m][n];

			if((m-M) >= 0) ans[i][j] -= gr[m-M][n];
			if((n-M) >= 0) ans[i][j] -= gr[m][n-M];
			if((m-M) >= 0 && (n-M) >= 0) ans[i][j] += gr[m-M][n-M];
		}

		int sum = 0;
		int x = 0;
		int y = N-M+1;

		for(int i = y-1; i >= 0; i--)
			FOR(j, 0, y)
		{
			printf("%d\n", ans[i][j]);
			sum += ans[i][j];
		}
		printf("%d\n", sum);

	}
	return 0;  
} 
#endif