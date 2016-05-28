#include "CommonHeader.h"


#ifdef UVA_481_WHATGOESUP
READ_INPUT(UVA_481_WHATGOESUP)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAX 100001
typedef int ll;

int N, M, K, T;
ll Mat[MAX];
ll dp[MAX];
ll prev[MAX];
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
		printf("%3d ", dp[i]);
	printf("\n");

	FOR(i, 0, count)
		printf("%3d ", prev[i]);
	printf("\n");
	printf("\n");
	printf("\n");
}

int PrintStack(int idx)
{
	if(prev[idx] == -1)
	{
		printf("%d\n", Mat[idx]);
		return -1;
	}

	PrintStack(prev[idx]);
	printf("%d\n", Mat[idx]); 
	return idx;
}

int main()
{

	int idx = 0;
	int maxIndex = -1;
	int maxVal = -1;

	while(scanf("%d ", &Mat[idx++]) != EOF);

	count = idx;

	FOR(i , 0, count)
		dp[i] = 1, prev[i] = -1;

	FOR(i , 1, count)
	{
		FOR(j , 0, i)
		{
			if(Mat[i] > Mat[j])
				if(dp[i] < dp[j]+1)
				{
					dp[i] = dp[j]+1, prev[i] = j;
					if(maxVal < dp[i])
						maxIndex = i,maxVal = dp[i]; 
				}
		}
	}

	//PrintMat();

	/*{
		int ans[MAX];
		int k = 0;
		int index = maxIndex;
		while(prev[index] != -1)
			ans[k++] = Mat[index], index = prev[index];

		ans[k++] = Mat[index];

		printf("%d\n-\n", k);

		for(int i = k-1; i >= 0; i--)
			printf("%d\n", ans[i]);
	}
*/
	/*{
		int ans[MAX];
		int k = maxVal;
		int index = maxIndex;

		printf("%d\n-\n", k);

		PrintStack(index);
	}*/

	int index = maxIndex;
	while(prev[index] != -1)
	{
		printf("%d\n", Mat[index]); 
		index = prev[index];
	}


	// LIS nLOGk algo required to pass on UVA. Leaving for now. :-)
	return 0;
}

#endif