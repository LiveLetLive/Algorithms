#include "CommonHeader.h"

#ifdef UVA_11742_SOCIAL_CONSTRAINTS
READ_INPUT(UVA_11742_SOCIAL_CONSTRAINTS)

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

void reset()
{
}

int main()
{
	int T;
	int num[21];
	scanf("%d ", &T);

	FOR(i, 0, T)
	{
		scanf("%x ", &num[i]);
		FOR(j, 0, 20)
			printf("%d ", (num[i] & (1 << j))?1:0);
		printf("\n");
	}

	return 0;
}

#endif
