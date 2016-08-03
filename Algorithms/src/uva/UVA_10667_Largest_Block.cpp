#include "CommonHeader.h"

#ifdef UVA_10667_LARGEST_BLOCK
READ_INPUT(UVA_10667_LARGEST_BLOCK)

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
#define MAXN 102
#define INF 0xfffffffffLL

int N, M, T;
char gr[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gr[i][j] = 1;
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
		int B = 0;
		reset();

		scanf("%d ", &N);
		scanf("%d ", &B);


		FOR(x, 0, B)
		{
			int i0, i1, j0, j1;

			scanf("%d %d %d %d ", &i0, &j0, &i1, &j1);
			i0--, j0--, i1--, j1--;

			FOR(i, i0, i1+1)
				FOR(j, j0, j1+1)
				gr[i][j] = 0;
		}

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
	}
	return 0;  
} 
#endif