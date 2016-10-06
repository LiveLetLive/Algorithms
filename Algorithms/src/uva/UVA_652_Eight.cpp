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
#define INF 0x3f3f3f3fL
typedef unsigned long long ull;
int a[MAXN];

map<int, int> pred_map;
map<ull, int> visit_map;

void reset()
{
	visit_map.clear();
	pred_map.clear();
}

int limit = 0;
int next_limit = 0;

int H()
{
	int sum = 0;
	FOR(i, 0, MAXN)
		if(a[i] != 0 && i != a[i])
			sum += abs(a[i] - i);
	return sum;
}

int dr[] = { -1, 0, 0, 1 };
int dc[] = {  0,-1, 1, 0 };

void make_move(int pi, int pj, int ni, int nj)
{
	int p = pi * ROW + pj;
	int n = ni * ROW + nj;

	swap(a[p], a[n]);
}

bool isDest()
{
	FOR(i, 0, MAXN)
		if(a[i] != i)
			return false;
	return true;
}

int DFS(int g, int h)
{
	if(g+h > limit)
	{
		next_limit = min(next_limit, g+h);
		return 0;
	}

	if(isDest())
		return 1;

	unsigned long long state = 0;
	FOR(i, 0, MAXN)
		state |= (a[i] << 4);

	if(visit_map.count(state) && visit_map[state] <= g)
		return false;

	int i;
	for(i = 0; i < MAXN; i++)
		if(a[i] == 15)
			break;

	int pi = i/4;
	int pj = i%4;

	FOR(x, 0, 4)
	{
		int ni = dr[x];
		int nj = dc[x];

		if(ni < 0 || nj < 0 || ni >= ROW || nj >= ROW )
			continue;

		make_move(pi, pj, ni, nj);	//Make move

		pred_map[g+1] = x;

		if(DFS(g+1, H()) == 1)
			return 1;

		make_move(ni, nj, pi, pj);	//Make restore
	}

	return 0;
}

int IDA_Star()
{
	limit = H();
	while(1)
	{
		next_limit = INF;
	
		if(DFS(0, H()) == 1)
			return 1;

		if(next_limit == INF)
			return -1;

		limit = next_limit;
	}
}

void PrintOutput()
{

}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();

		char arr[MAXN] = { 0 };

		FOR(i, 0, MAXN)
		{
			scanf("%c ", &arr[i]);
			if(arr[i] == 'x')
				a[i] = 15;
			else
				a[i] = arr[i] - '0' - 1;	// '0' based
		}

		int sum = 0;

		FOR(i, 0, MAXN)
			FOR(j, 0, i)
			if(a[i] != 15 && a[j] != 15 && a[i] < a[j])
				sum ++;

		if(sum%2 != 0)
		{
			int ans = IDA_Star();
			if(ans == -1)
				printf("unsolvable\n");
			else
				PrintOutput();
		}
		else
			printf("unsolvable\n");
	}
	return 0;
}

#endif
