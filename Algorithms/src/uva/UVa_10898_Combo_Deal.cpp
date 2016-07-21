#include "CommonHeader.h"

#ifdef UVA_10898_COMBO_DEAL
READ_INPUT(UVA_10898_COMBO_DEAL)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 12
#define INF 0x3FFFFFFF

int N;
int p[6];
int pc[8];

int comboItem[8][6];
int ComboItemInt[8];
int C;
int O;
int order[6];

int dp[1<<24];

void reset()
{
	FOR(i, 0, 6)
		p[i] = 0, order[i] = 0;
	FOR(i, 0, 8)
		pc[i] = 0, ComboItemInt[i] = 0;
	FOR(i, 0, 8)
		FOR(j, 0, 6)
		comboItem[i][j] = 0;

	FOR(i, 0, (1 << (4*N)))
		dp[i] = -1;
}

bool CheckCombo(int idx, int remItem)
{
	FOR(i, 0, N)
	{
		int itemCnt = remItem & (0xF << (4*i));

		itemCnt >>= (4*i);

		if((itemCnt - comboItem[idx][i]) < 0)
			return false;
	}
	return true;
}
int solve(int remItem)
{
	if(dp[remItem] != -1)
		return dp[remItem];

	if(remItem == 0)
		return 0;

	int ans = INF;
	bool found = false;

	// Check all combos
	FOR(i, 0, C)
	{
		if(CheckCombo(i, remItem))
		{
			found = true;
			int newRemItem = remItem - ComboItemInt[i];
			ans = min(ans, solve(newRemItem) + pc[i]);
		}
	}

	//We have tried all combos, now purchase individually
	if(found == false)
	{
		ans = 0;
		FOR(i, 0, N)
		{
			int itmCnt = (remItem & (0xF << (4*i))) >> (4*i);
			ans += (p[i]*itmCnt);
		}
	}

	return dp[remItem] = ans;
}

int main()
{
	while(scanf("%d", &N) != EOF)
	{
		reset();

		FOR(i, 0, N)
			scanf("%d ", &p[i]);

		scanf("%d", &C);

		FOR(i, 0, C)
		{
			FOR(j, 0, N)
				scanf("%d ", &comboItem[i][j]), ComboItemInt[i] |= (comboItem[i][j] << (4*j)); 

			scanf("%d", &pc[i]);
		}

		scanf("%d", &O);

		FOR(i, 0, O)
		{
			int OrderItem = 0;
			FOR(x, 0, 6) order[x] = 0;
			FOR(j, 0, N) 
				scanf("%d ", &order[j]), OrderItem |= (order[j] << (4*j)); 

			int ans = solve(OrderItem);

			printf("%d\n", ans);
		}

	}
	return 0; 
}
#endif