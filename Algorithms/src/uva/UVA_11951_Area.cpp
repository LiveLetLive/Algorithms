#include "CommonHeader.h"


#ifdef UVA_11951_AREA
READ_INPUT(UVA_11951_AREA)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)

typedef long long ll;

int N, M, K, T;
ll Mat[101][101];

void PrintMat()
{
	FOR(i, 0, N)
	{
		FOR(j, 0, M)
		{
			printf("%03d ", Mat[i][j]);
		}

		printf("\n");
	}
}

inline int MyMin(int i, int j)
{
	return i<j ? i : j;
}

inline int MyMax(int i, int j)
{
	return i>j ? i : j;
}

inline int FindSub(int i , int j, int k, int l, ll &price)
{
	ll max = Mat[k][l];

	if(i > 0) max -= Mat[i-1][l];
	if(j > 0) max -= Mat[k][j-1];
	if(i > 0 && j > 0) max += Mat[i-1][j-1];

	//if(max < 0) max = 0;
	price = max;
	return max <= K;
}

int main()
{
	//freopen("Text.txt", "r", stdin);
	
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		scanf("%d", &N);
		scanf("%d", &M);
		scanf("%d", &K);

		FOR(i , 0, N)
		{
			FOR(j , 0, M)
			{
				ll tmp = 0;
				scanf("%d", &tmp);

				Mat[i][j] = tmp;

				if(i > 0) Mat[i][j] += Mat[i-1][j];
				if(j > 0) Mat[i][j] += Mat[i][j-1];
				if(i > 0 && j > 0) Mat[i][j] -= Mat[i-1][j-1];
			}
		}

		//PrintMat();

		int maxArea = -0x3f3f3f3f;
		ll minPrice = 0x3f3f3f3f3f3f3f3f;
		int purchaseOnce = 0;

		int ri, rj, rk, rl;
		FOR(i, 0, N)
		{
			FOR(j, 0, M)
			{
				FOR(k, i, N)
				{
					FOR(l, j, M)
					{
						ll Price = 0;
						bool isPurchasePossible = FindSub(i,j, k, l, Price);

						if(isPurchasePossible)
						{
							purchaseOnce = 1;
							int dy = k-i+1;
							int dx = l-j+1;

							//if(dy == 0) dy = 1;
							//if(dx == 0) dx = 1;

							int localArea = dy*dx;

							if(localArea > maxArea)
							{
								maxArea = localArea;
								minPrice = Price;
								ri =i; rj = j; rk = k; rl = l;
							}
							else if(localArea == maxArea)
							{
								minPrice = MyMin(minPrice, Price);
								ri =i; rj = j; rk = k; rl = l;
							}
						}
						else if(Price > K)
							break;
					}
				}
			}

		}

		if(purchaseOnce)
			printf("Case #%d: %d %d\n", t+1, maxArea, minPrice);
		else
			printf("Case #%d: %d %d\n", t+1, 0, 0);
		
		//printf("#%d:#%d:#%d:#%d\n", ri, rj ,rk , rl);
	}

	return 0;
}

#endif