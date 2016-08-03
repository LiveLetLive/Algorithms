#include "CommonHeader.h"

#ifdef UVA_10827_MAXIMUM_SUM_ON_A_TORUS
READ_INPUT(UVA_10827_MAXIMUM_SUM_ON_A_TORUS)

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
#define MAXN 76*4
#define INF 0xfffffffffLL

int N, M, T;
int gr[MAXN][MAXN];
int gr1[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gr[i][j] = 0, gr1[i][j] = 0;
}
void PrintGrid()
{
	FOR(i, 0, N)
	{
		FOR(j, 0, N)
			printf("%2d ", gr[i][j]);
		printf("\n");
	}

	printf("----------\n");
	FOR(i, 0, N)
	{
		FOR(j, 0, N)
			printf("%2d ", gr1[i][j]);
		printf("\n");
	}

	printf("//////\n");
}



int main()
{
	int T1 = 0;
	scanf("%d ", &T1);
	FOR(t, 0, T1)
	{
		int idx = 0;
		reset();

		scanf("%d ", &N);

		FOR(i, 0, N)
		FOR(j, 0, N)
		{
			scanf("%d ", &gr[i][j]);
			gr[i+N][j+N] = gr[i][j];
			gr[i][j+N] = gr[i][j];
			gr[i+N][j] = gr[i][j];
		}

		if(N==1)  
		{
			printf("%d\n", gr[0][0]);
			continue;
		}

		//PrintGrid();

		N*= 2;
		//PrintGrid();

		FOR(i, 0, N) FOR(j, 0, N)
		{
			if(i > 0) gr[i][j] += gr[i-1][j], gr1[i][j] += gr1[i-1][j];
			if(j > 0) gr[i][j] += gr[i][j-1], gr1[i][j] += gr1[i][j-1];
			if(i > 0 && j > 0) gr[i][j] -= gr[i-1][j-1], gr1[i][j] -= gr1[i-1][j-1];
		}

		//PrintGrid();

		int maxrect = -127*150*150;

		FOR(i, 0, N) FOR(j, 0, N)
			FOR(m, i, N) FOR(n, j, N)
			{
				if(m-i+1 > N/2 || n-j+1 > N/2) continue;
				
				int rect = gr[m][n];
				if(i>0) rect -= gr[i-1][n];
				if(j>0) rect -= gr[m][j-1];
				if(i>0 && j>0) rect += gr[i-1][j-1];

				maxrect = max(maxrect, rect);
			}

		printf("%d\n", maxrect);
	}
	return 0;  
} 
#endif