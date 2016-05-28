#include "CommonHeader.h"


#ifdef UVA_108_MAXIMUM_SUM
READ_INPUT(UVA_108_MAXIMUM_SUM)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)

int N;
int M[101][101];

void PrintMat()
{
	FOR(i, 0, N)
	{
		FOR(j, 0, N)
		{
			printf("%03d ", M[i][j]);
		}

		printf("\n");
	}
}


inline int MyMax(int i, int j)
{
	return i>j ? i : j;
}

inline int FindSub(int i , int j, int k, int l)
{
	int max = M[k][l];

	if(i > 0) max -= M[i-1][l];
	if(j > 0) max -= M[k][j-1];
	if(i > 0 && j > 0) max += M[i-1][j-1];

	//if(max < 0) max = 0;

	return max;
}

int main()
{
	while(scanf("%d", &N) != EOF)
	{
		FOR(i , 0, N)
		{
			FOR(j , 0, N)
			{
				int tmp = 0;
				scanf("%d", &tmp);

				M[i][j] = tmp;
				
				if(i > 0) M[i][j] += M[i-1][j];
				if(j > 0) M[i][j] += M[i][j-1];
				if(i > 0 && j > 0) M[i][j] -= M[i-1][j-1];
			}
		}

		//PrintMat();

		int maxSub = -0x3f3f3f3f;

		FOR(i, 0, N)
		{
			FOR(j, 0, N)
			{
				FOR(k, i, N)
				{
					FOR(l, j, N)
					{
						maxSub = MyMax( maxSub, FindSub(i,j, k, l));
					}
				}

			}

		}

		printf("%d\n", maxSub);
	}

	return 0;
}

#endif