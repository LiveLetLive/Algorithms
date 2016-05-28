#include "CommonHeader.h"


#ifdef UVA_11450_WEDDING_SHOPPING
READ_INPUT(UVA_11450_WEDDING_SHOPPING)

#include <iostream>
#include <cstdio>


#define FOR(i, init, count) for(int i = init; i < count; i++)
int m[103][103];
int d[103][103];
int T, N, M, C;

int price[23][23];
int dp[203][203];
int modCount[23];
int maxTotal = -1;

int PriceCalc(int ml, int gi, int mod)
{
	int maxCalc = -1000000000;

	if(ml < 0) return -1000000000;

	if(dp[ml][gi] != -1) return dp[ml][gi];

	if(gi == C) return M - ml;

	FOR(i, 0, modCount[gi])
	{
		int c = PriceCalc(ml - price[gi][i], gi+1, i);
		if(c > maxCalc)
			maxCalc = c;
	}

	dp[ml][gi] = maxCalc;

	if(maxCalc > maxTotal)
		maxTotal = maxCalc;

	return maxCalc;
}

void PrintTable()
{
	printf("Price\n");
	FOR(j, 0, C)
		printf("%3d  ", price[j]);
	printf("\nPriceEND\n");

		printf("     ");

	FOR(j, 0, C)
		printf("%3d  ", j);

	printf("\n");

	for(int i = M-1; i; --i)
	{
		printf("%3d  ",i);
		FOR(j, 0, C)
			printf("%3d  ", dp[i][j]);
		printf("\n");
	}
}
void reset()
{
	maxTotal = -1;

	FOR(i, 0, 23)
		FOR(j, 0, 23)
		price[i][j] = -1,modCount[i] = 0;
	FOR(i, 0, 203)
		FOR(j, 0, 203)
		dp[i][j] = -1;
}
int main()
{
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		int maxLen = -1;

		scanf("%d %d", &M, &C);

		reset();

		FOR(j, 0, C)
		{
			int l = 0;

			scanf("%d", &l);

			modCount[j] = l;

			FOR(k, 0, l)
				scanf("%d", &price[j][k]);
		}

		int c = PriceCalc(M,0, 0);
		PrintTable();

		if(c < 0)
			printf("no solution\n");
		else
			printf("%d\n", c);
	}

	return 0;
}

#endif