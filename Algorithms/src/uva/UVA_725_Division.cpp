#include "CommonHeader.h"

#ifdef UVA_725_DIVISION
READ_INPUT(UVA_725_DIVISION)

#include <iostream>
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
#define MAXN 1003
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N;

int used[10];

void reset()
{
	FOR(i, 0, 10)
		used[i] = 0;
}

inline int setUsed(int val)
{
	int cnt = 0;
	while(val)
	{
		int tmp = val % 10;
		if(used[tmp]) return 0;
		used[tmp] = 1;
		cnt++;
		val /= 10;
	}

	/*if(cnt < 5)
		return 0;*/
	return 1;
}

void solve()
{
	int found = 0;
	FOR(denomin, 1234, 100000)
	{
		reset();
		int num = denomin * N;

		if(denomin < 10000) used[0] = 1;

		if(setUsed(num) == 0)
			continue;

		if(setUsed(denomin) == 0)
			continue;

		int i;

		for(i = 0; i < 10; i++)
			if(used[i] != 1)
				break;

		if(i == 10)
			printf("%05d / %05d = %d\n", num, denomin, N), found = 1;
	}

	if(found == 0)
		printf("There are no solutions for %d.\n", N);
}

int main()
{
	int first = 0;
	while(scanf("%d ", &N), N)
	{
		if(first++ != 0)
			printf("\n");
		solve();
	}
	return 0;
}

#endif
