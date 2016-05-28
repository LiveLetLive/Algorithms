#include "CommonHeader.h"


#ifdef UVA_11456_TRAINSORTING
READ_INPUT(UVA_11456_TRAINSORTING)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAX 100001
typedef int ll;

int N, M, K, T;
ll Mat[MAX];
ll Len[MAX];

ll dpInc[MAX];
ll dpDec[MAX];
int count = 0;

inline int MyMin(int i, int j)
{
	return i<j ? i : j;
}

inline int MyMax(int i, int j)
{
	return i>j ? i : j;
}

void PrintMat()
{
	FOR(i, 0, count)
		printf("%3d ", Mat[i]);
	printf("\n");	
	FOR(i, 0, count)
		printf("%3d ", Len[i]);
	printf("\n");

	FOR(i, 0, count)
		printf("%3d ", dpInc[i]);
	printf("\n");
	FOR(i, 0, count)
		printf("%3d ", dpDec[i]);
	printf("\n");

	printf("\n");
	printf("\n");
	printf("\n");
}

int main()
{

	int idx = 0;
	int maxIncIndex = -1;
	int maxIncVal = -1;

	scanf("%d ", &T);


	FOR(t, 0, T)
	{
		int maxInc = 0, maxDec = 0;

		scanf("%d ", &N);

		FOR(i, 0, N)
			scanf("%d ", &Mat[i]);
		FOR(j, 0, N)
			scanf("%d ", &Len[j]);

		count = N;

		FOR(i , 0, count)
			dpInc[i] = Len[i], dpDec[i] = Len[i];

		FOR(i , 0, count)
		{
			FOR(j , 0, i)
			{
				if(Mat[i] > Mat[j])
				{
					dpInc[i] = MyMax(dpInc[i],  dpInc[j]+Len[i]);
				}
				if(Mat[i] < Mat[j])
				{
					dpDec[i] = MyMax(dpDec[i],  dpDec[j]+Len[i]);
					if(maxDec < dpDec[i])
						maxDec = dpDec[i];
				}
			}
			maxInc = MyMax(maxInc, dpInc[i]);
			maxDec = MyMax(maxDec, dpDec[i]);
		}

		//PrintMat();

		if(maxDec > maxInc)
			printf("Case %d. Decreasing (%d). Increasing (%d).\n", t+1, maxDec, maxInc);
		else
			printf("Case %d. Increasing (%d). Decreasing (%d).\n", t+1, maxInc, maxDec);

	}
	return 0;
}

#endif