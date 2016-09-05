#include "CommonHeader.h"

#ifdef UVA_4143_FREE_PARENTHESES
READ_INPUT(UVA_4143_FREE_PARENTHESES)

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 33
#define MAXV 3300
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int dp[MAXN][MAXN][MAXV+MAXV];
int used[MAXV+MAXV];
int N;
int a[MAXN];
int sign[MAXN];

void reset()
{
	FOR(i, 0, N+1)
		FOR(j, 0, N+1)
		FOR(k, 0, MAXV+MAXV)
		dp[i][j][k] = -1, used[k] = 0;
}

int solve(int idx, int openCnt, int val)
{
	if(dp[idx][openCnt][val+MAXV] != -1)
	return dp[idx][openCnt][val+MAXV];
	
	// If we are at end, no matter how many brackets are open, we close them by force and say that this is 1 of answer
	if(idx >= N)
	{
		used[val+MAXV] = 1;
		return 1;
	}

	int nVal = 0;


	// even open brackets just mean that sign is restored.
	//1 - ( 2 + 3 - (4 - 5)) = 1 - (2 + 3 - 4 + 5) = 1 - 2 - 3 + 4 - 5

	if(sign[idx]) //+
		nVal = val + (a[idx] * ((openCnt%2==0) ? 1 : -1));
	else
		nVal = val - (a[idx] * ((openCnt%2==0) ? 1 : -1));

	if(sign[idx] == 0)
	{
		//Open 1 new bracket
		solve(idx+1, openCnt+1, nVal);
	}
	else if(openCnt)
	{
		//close a bracket
		solve(idx+1, openCnt-1, nVal);
	}

	//No bracket operation, just move
	solve(idx+1, openCnt, nVal);

	// We reached this state measn, that we have a sol
	return dp[idx][openCnt][val+MAXV] = 1;
}

int main()
{
	while(1)
	{
		char str[1500] = {0 };

		cin.getline(str, 1500);
		int val;
		if(str[0] == 0) break;

		int nValIndex = 0;
		int nSignIndex = 0;
		stringstream stream(str);


		while(stream >> val)
		{
			a[nValIndex++] = val;
			char ch;
			stream >> ch;
			sign[++nSignIndex] = ((ch == '-') ? 0 : 1);
		}

		N = nValIndex;
		reset();
		solve(1, 0, a[0]);

		int cnt = 0;
		FOR(i, 0, MAXV+MAXV)
			if(used[i] != 0)
				cnt++;

		printf("%d\n", cnt);

	}
	return 0;
}

#endif
