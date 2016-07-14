#include "CommonHeader.h"

#ifdef UVA_10360_RAT_ATTACK
READ_INPUT(UVA_10360_RAT_ATTACK)

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
#define MAXN 1030
int d, r;

int cell[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		cell[i][j] = 0;
}


int main()
{
	int T;
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &d);
		scanf("%d ", &r);

		int maxX = 0;
		int maxY = 0;

		FOR(i, 0, r)
		{
			int x, y, size;

			scanf("%d %d %d ", &x, &y, &size);


			FOR(i, x - d, x + d +1)
				FOR(j, y - d, y + d +1)
			{
				if(i < 0 || j < 0 || i > 1024 || j > 1024)
					continue;

				cell[i][j] += size;
			}

			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}

		int maxKill = 0;
		int maxKillX = 0;
		int maxKillY = 0;

		FOR(i, 0, maxX + 1)
			FOR(j, 0, maxY + 1)
		{
			if(maxKill < cell[i][j])
			{
				maxKill = cell[i][j];
				maxKillX = i;
				maxKillY = j;
			}
		}

		printf("%d %d %d\n", maxKillX, maxKillY, maxKill);
	}

	return 0;
}


#endif