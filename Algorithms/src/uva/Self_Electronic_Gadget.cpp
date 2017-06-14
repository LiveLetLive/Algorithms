#include "CommonHeader.h"

#ifdef SELF_ELECTRONIC_GADGET
READ_INPUT(SELF_ELECTRONIC_GADGET)

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
#define MAXN 10003
#define INF 0x3f3f3f3fL
typedef long long ll;

// 1 denotes , not usable
int refTable[MAXN];
int activeTable[MAXN];

void GenTable()
{
	FOR(i, 0, MAXN)
	{
		int visited[10] = { 0 };
		int repeat = 0;

		int num = i;
		int count = 4;

		while(count--)
		{
			if(visited[num % 10])
			{
				repeat = 1;
				break;
			}
			visited[num % 10] = 1;
			num /= 10;
		}

		if(repeat == 1)
			refTable[i] = 1;
	}
}


//idx is index from right (right most == 0)
void UpdateRefTable(int idx, int Foundnum)
{
	FOR(i, 0, MAXN)
	{
		int visited[10] = { 0 };
		int repeat = 0;

		int num = i;
		int count = 4;
		visited[Foundnum] = 1;

		while(count--)
		{
			if(Foundnum == (num % 10) && count == idx)
				continue;

			if(visited[num % 10])
			{
				refTable[i] = 1;
			}
			num /= 10;
		}
	}
}

int GiveFirstZero()
{
	FOR(i, 0, MAXN)
		if(refTable[i] == 0)
			return i;
}

int main()
{
	GenTable();
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		FOR(i, 0, MAXN)
			activeTable[i] = refTable[i];

		int fguess = GiveFirstZero();

		printf("%d", fguess);
		

	}
	return 0;
}

#endif
