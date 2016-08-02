#include "CommonHeader.h"

//#ifdef UVA_836_LARGEST_SUBMATRIX
#if 1
//READ_INPUT(UVA_836_LARGEST_SUBMATRIX)

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
#define MAXN 28
#define INF 0xfffffffffLL

int N, M, T;
char gr[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gr[i][j] = 0;
}

int solve()
{
	return 0;
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
	int T1 = 0;
	scanf("%d ", &T1);
	FOR(t, 0, T1)
	{
		int idx = 0;
		reset();

		//scanf("%*s");
		scanf("%s ", &gr[idx++]);

		int len1 = strlen(gr[0]);

		FOR(i, 1, len1)
			scanf("%s ", &gr[idx++]);

		N = idx;
		FOR(i, 0, N)
			FOR(j, 0, N)
			gr[i][j] -= '0';

		int maxSum = 0;
		int currSum = -1;
		int maxL, maxT, maxR, maxB;

		int maxrect = -1;

		FOR(l, 0, N)
		{
			int sum[MAXN] = {};
			FOR(r, l, N)
			{
				FOR(i, 0, N)
					sum[i] += gr[i][r];

				currSum = 0;
				int currT = 0;
				int ht = 0;
				int width = r-l+1;
				FOR(k, 0, N)
				{

					if(currSum != width*ht) 
						currSum = 0, ht = 0;

					currSum += sum[k];
					ht++;

					if(currSum > maxSum && currSum == width*ht)
						maxL = l, maxR = r, maxT = k - ht + 1, maxB = k, maxSum = currSum;
				}
			}
		}

		printf("%d\n", maxSum);
		if(t < (T1-1)) printf("\n");
	}
	return 0;  
} 
#endif