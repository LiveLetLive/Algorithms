#include "CommonHeader.h"


#ifdef UVA_452_PROJECT_SCHEDULING
READ_INPUT(UVA_452_PROJECT_SCHEDULING)

#include <iostream>
#include <stdio.h>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 28

int g[MAXN][MAXN];
int v[MAXN];

void reset()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0;
		v[i] = 0;
	}
}
int main()
{
	int T = 0;

	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		char ch;
		char str[30];
		int tmp;

		reset();

		scanf("%*");
		scanf("%c %d ", &ch, &tmp);

		v[ch - 'A'] = tmp;

		while(scanf("%c %d %s", &ch, &tmp, &str))
		{
			v[ch - 'A'] = tmp;
			int len = strlen(str);

			FOR(i, 0, len)
				g[str[i] - 'A'][ch - 'A'] = 1;
		}

	}

	return 0;
}
#endif