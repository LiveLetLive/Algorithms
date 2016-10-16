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
#define BLANK_POS ((ROW*ROW)-1)
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
		if(a[i] != BLANK_POS)
			sum += (abs(a[i]/ROW - i/ROW) + abs(a[i]%ROW - i%ROW));
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
		state <<= 4, state += a[i];

	if(visit_map.count(state) && visit_map[state] <= g)
		return false;

	visit_map[state] = g;

	int j;
	for(j = 0; j < MAXN; j++)
	{
		if(a[j] == BLANK_POS)
			break;
	}

	int pi = j/ROW;
	int pj = j%ROW;

	FOR(x, 0, 4)
	{
		int ni = pi + dr[x];
		int nj = pj + dc[x];

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

	return -1;
}

char op_str[] = "ulrd";

void PrintOutput(int pos)
{
	if (pos == 0)
		return;
	PrintOutput(pos - 1);
	printf("%c", op_str[pred_map[pos]]); 
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();

		char arr[MAXN] = { 0 };
		int blank = -1;
		FOR(i, 0, MAXN)
		{
			scanf("%c ", &arr[i]);
			if(arr[i] == 'x')
				a[i] = BLANK_POS, blank = i;
			else
				a[i] = arr[i] - '0' - 1;	// '0' based
		}

		int sum = 0;

		FOR(i, 0, MAXN)
			FOR(j, 0, i)
			if(a[i] != BLANK_POS && a[j] != BLANK_POS && a[i] < a[j])
				sum++;

		sum += blank / ROW;

		if(1)
		{
			int ans = IDA_Star();
			if(ans == -1)
				printf("unsolvable\n");
			else
				PrintOutput(ans);
			
			if(t < T-1)
				printf("\n\n");
		}
		else
			printf("unsolvable\n");
	}
	return 0;
}

#endif
