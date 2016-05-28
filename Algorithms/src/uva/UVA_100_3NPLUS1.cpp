#include "CommonHeader.h"


#ifdef UVA_100_3NPLUS1
READ_INPUT(UVA_100_3NPLUS1)

#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long NUM;

#define FOR(i, init, count) for (int i = init, i < count; i++)

int i, j;
int maxCycleLen = 0;
int g_CycleLen = 0;

int main()
{
	//freopen("Text.txt", "r", stdin);

	while(scanf("%d %d", &i, &j) != EOF )
	{
		maxCycleLen = -1;

		int i1 = i, j1 = j;
		if(i > j) swap(i, j);

		for(int s1 = i; s1 <= j; s1++)
		{
			g_CycleLen = 0;
			NUM num = s1;

			while (num != 1)
			{
				if((num & 0x1) == 1) num = 3*num+1;
				else num /=2;
				g_CycleLen++;
			}

			if(maxCycleLen < g_CycleLen)
				maxCycleLen = g_CycleLen;
		}

		cout << i1 << " " << j1 << " " << maxCycleLen+1 << endl;
	}
	return 0;
}

#endif