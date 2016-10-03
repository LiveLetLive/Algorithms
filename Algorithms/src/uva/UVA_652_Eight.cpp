#include "CommonHeader.h"

#ifdef UVA_652_EIGHT
READ_INPUT(UVA_652_EIGHT)

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
#define ROW 3
#define MAXN ROW*ROW
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int a[MAXN];

void reset()
{
}

int H()
{
	int sum = 0;
	FOR(i, 0, MAXN)
		if(a[i] != 0 && i != a[i])
			sum += abs(a[i] - i);
	return sum;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		FOR(i, 0, MAXN)
		{
			scanf("%d ", &a[i]);
			if(a[i] == 'x')
				a[i] = 0;
		}

		int ans = IDA_Star();
	}
	return 0;
}

#endif
