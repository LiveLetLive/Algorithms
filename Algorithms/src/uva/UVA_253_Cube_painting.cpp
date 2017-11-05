#include "CommonHeader.h"

#ifdef UVA_253_CUBE_PAINTING
READ_INPUT(UVA_253_CUBE_PAINTING)

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
#define INF 0x3f3f3f3fL
typedef long long ll;

#define hash(c1, c2) (256*min(c1,c2) + max(c2,c1))

char s[20];
int i, cont[100000];

int opFace[3] = 
{
	5,
	4,
	3
};

int adFace[6][4] = 
{
	{ 1, 2, 3, 4} ,
	{ 2, 5, 3, 0} ,
	{ 1, 0, 5, 4} ,
	{ 1, 0, 5, 4} ,
	{ 0, 2, 3, 5} ,
	{ 1, 2, 3, 4} ,
};


int main()
{
	while (fgets(s, 1024, stdin)) 
	{
		int found = 1;
		memset(cont, 0, sizeof cont);
		FOR(i, 0, 3)
		{
			char f1 = s[i];
			char fo = s[opFace[i]];
			int h = hash(f1, fo);
			cont[h]++;
		}

		FOR(i, 0, 6)
		{
			char f1 = s[i];
			FOR(j, 0, 4)
			{
				char fo = s[adFace[i][j]];
				int h = hash(f1, fo);
				cont[h]++;
			}
		}


		FOR(i, 0, 3)
		{
			char f1 = s[6+i];
			char fo = s[6+opFace[i]];
			int h = hash(f1, fo);

			if (cont[h])
				cont[h]--;
			else
			{
				found = 0;
				break;
			}
		}

		if(found)
		{
			FOR(i, 0, 6)
			{
				char f1 = s[i];
				FOR(j, 0, 4)
				{
					char fo = s[adFace[i][j]];
					int h = hash(f1, fo);
					if (cont[h])
						cont[h]--;
					else
					{
						found = 0;
						break;
					}
				}

				if(found == 0)
					break;
			}
		}


		if(found)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	return 0;
}

#endif
