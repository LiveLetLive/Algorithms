#include "CommonHeader.h"

#ifdef UVA_750_8_QUEENS_CHESS_PROBLEM
READ_INPUT(UVA_750_8_QUEENS_CHESS_PROBLEM)

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
#define MAXN 8
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int solIndex = 0;
int placedR[MAXN];
int sol[100][MAXN];
int sr, sc;

void reset()
{
	solIndex = 0;

	FOR(i, 0, 100)
		FOR(j, 0, MAXN)
		sol[i][j] = -1, placedR[j] = -1;
}

int isPossible(int r, int c)
{
	FOR(i, 0, 8)
		if(placedR[i] != -1)
		{
			int pc = i;
			int pr = placedR[i];

			if(pc == c) return 0;
			if(pr == r) return 0;
			if(abs(pc - c) == abs(pr - r)) return 0;
		}

		return 1;
}


int place(int c, int cnt)
{
	if(cnt == 8 && placedR[sc] == sr)
	{
		FOR(i, 0, 8)
			sol[solIndex][i] = placedR[i];
		solIndex++;

		printf("%2d      %d", solIndex, placedR[0]+1);

		FOR(j, 1, 8)
			printf(" %d", placedR[j] + 1);
		printf("\n");

		return 1;
	}

	FOR(r, 0, 8)
	{
		if(isPossible(r, c))
		{
			if(c == sc && r != sr) 
				continue;
			placedR[c] = r;
			place(c+1, cnt + 1);
			placedR[c] = -1;
		}
	}
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T) 
	{
		scanf("%d %d ", &sr, &sc);
		reset();

		sr--, sc--;
		printf("SOLN       COLUMN\n");
		printf(" #      1 2 3 4 5 6 7 8\n\n");

		place(0, 0);

		if (t< T-1) 
			printf("\n");
	}
	return 0;
}

#endif
