#include "CommonHeader.h"

#ifdef UVA_10074_TAKE_THE_LAND
READ_INPUT(UVA_10074_TAKE_THE_LAND)

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
#define MAXN 105
#define INF 0xfffffffffLL

int N, M, T;
int gr[MAXN][MAXN];

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
	while(scanf("%d %d ", &N, &M), N, M)
	{
		int idx = 0;
		reset();

		FOR(i, 0, N)
		FOR(j, 0, M)
			scanf("%d ", &gr[i][j]), gr[i][j] ^= 0x1;

		int maxSum = 0;
		int currSum = -1;
		int maxL, maxT, maxR, maxB;

		int maxrect = -1;

		FOR(l, 0, M)
		{
			int sum[MAXN] = {};
			FOR(r, l, M)
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
	}
	return 0;  
} 
#endif