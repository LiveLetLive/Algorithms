#include "CommonHeader.h"


#ifdef UVA_10285_LONGEST_RUN_ON_SNOWBOARD
READ_INPUT(UVA_10285_LONGEST_RUN_ON_SNOWBOARD)

#include <iostream>
#include <cstdio>


#define FOR(i, init, count) for(int i = init; i < count; i++)
int m[103][103];
int d[103][103];
int T, N, R, C;


int checkLen(int x, int y)
{
	if(m[x][y] != -1) return m[x][y];
	int up = 0, down = 0, left = 0, right = 0; 

	if(x != 0 && d[x-1][y] < d[x][y] )
		left = checkLen(x-1, y) + 1;

	if(y != 0 && d[x][y-1] < d[x][y] )
		up = checkLen(x, y-1) + 1;

	if(x != R-1 && d[x+1][y] < d[x][y] )
		right = checkLen(x+1, y) + 1;

	if(y != C-1 && d[x][y+1] < d[x][y] )
		down = checkLen(x, y+1) + 1;

	m[x][y] = max(max(up, down), max(left, right));

	return m[x][y];
}

int main()
{
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		char str[1024];
		int maxLen = -1;

		scanf("%s %d %d", str, &R, &C);

		FOR(i, 0, 103)
			FOR(j, 0, 103)
			m[i][j] = -1;

		FOR(i, 0, R)
			FOR(j, 0, C)
				scanf("%d", &d[i][j]);

		FOR(i, 0, R)
			FOR(j, 0, C)
			{
				int c = -1;
				if(m[i][j] == -1)
					c = checkLen(i,j);

				if(c > maxLen)
					maxLen = c;
			}

		printf("%s: %d\n", str, maxLen+1);
	}

	return 0;
}

#endif