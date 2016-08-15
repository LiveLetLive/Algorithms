#include "CommonHeader.h"

#ifdef UVA_1211_ATOMIC_CAR_RACE
READ_INPUT(UVA_1211_ATOMIC_CAR_RACE)

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
#define MAXN 101
#define MAXL 10001
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
typedef double TIM;

TIM T[MAXL];
TIM b;
int N;
int r;
TIM v,e,f;
int chk[MAXN];

void reset()
{
	FOR(i, 0, MAXL)
		T[i] = 0;
	FOR(i, 0, MAXN)
		chk[i] = 0;
}

void CalcTime()
{
	FOR(i, 0, chk[N-1]+1)
	{
		if(i >= r)
			T[i] = 1.0 / (v - (e*(i-r)));
		else
			T[i] = 1.0 / (v - (f*(r-i)));
	}
}

TIM solve()
{
	return 0.0;
}

int main()
{
	while(scanf("%d ", &N), N)
	{
		FOR(i, 0, N)
			scanf("%d ", &chk[i]);
		scanf("%lf", &b);
		scanf("%d %lf %lf %lf", &r, &v, &e, &f);

		CalcTime();

		TIM ans = solve();
		printf("%lf\n", ans);
	}
	return 0;
}

#endif
