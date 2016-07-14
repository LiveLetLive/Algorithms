#include "CommonHeader.h"

#ifdef UVA_10010_WHERE_WALDORF
READ_INPUT(UVA_10010_WHERE_WALDORF)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 51
#define INF 0x3f3f3f3f

inline bool comp(char a, char b)
{
	return tolower(a) == tolower(b);
}
char a[MAXN][MAXN];
char pat[MAXN];
int patlen;

int n, m, Q, T;
int ansI, ansJ;
void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		a[i][j] = 0, pat[i] = 0;
}

int dr[] = { 0,	 0, -1, -1, -1,  1,  1,  1  };
int dc[] = { -1, 1, -1,  0, +1, -1,  0, +1,  };


bool isSafe(int i, int j)
{
	if(i < 0 || j < 0) return false;
	if(i >= m) return false;
	if(j >= n) return false;

	return true;
}

bool sUtil(int i, int j, int patIndex, int dir)
{
	if(isSafe(i, j) == false) return false;

	if(comp(a[i][j], pat[patIndex]) == false) return false;

	if(patIndex+1 == patlen) return true;

	if(dir == -1)
	{
		FOR(v, 0, 8)
		{
			int ans = sUtil(i + dr[v], j + dc[v], patIndex+1, v);

			if(ans)
				return true;
		}
	}
	else
	{
		return sUtil(i + dr[dir], j + dc[dir], patIndex+1, dir);
	}

	return false;
}

void searchIndex()
{
	FOR(i, 0, m)
		FOR(j, 0, n)
		if(comp(a[i][j], pat[0]))
		{
			bool ans = sUtil(i, j, 0, -1);
			if(ans)
			{
				ansI = i+1, ansJ = j+1;
				return;
			}
		}
}

int main()
{
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &m);
		scanf("%d ", &n);

		FOR(i, 0, m)
			scanf("%s ", &a[i]);

		scanf("%d ", &Q);

		FOR(i, 0, Q)
		{
			scanf("%s ", &pat);
			patlen = strlen(pat);

			searchIndex();
			printf("%d %d\n", ansI, ansJ);
		}

		if(t < T-1)
			printf("\n");
	}

	return 0;
}

#endif