#include "CommonHeader.h"


#ifdef UVA_1056_DEGREE_OF_SEPERATION
READ_INPUT(UVA_1056_DEGREE_OF_SEPERATION)

#include <iostream>
#include <cstdio>
#include <map>
#include <string>


using namespace std;


#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 51
typedef int ll;

int data[MAXN][MAXN];

int P, R;

void reset()
{
	FOR(i, 0, MAXN)
	{	
		FOR(j, 0, MAXN)
			data[i][j] = 0xFFFF;
		data[i][i] = 0;
	}
}

int main()
{
	int t = 1;
	while(1)
	{
		map<string,int> nMap;
		map<string,int>::iterator nMapIterator;
		reset();
		int Mindex = 0;
		char str1[50], str2[50];
		scanf("%d ", &P);
		scanf("%d ", &R);

		if(P == 0 && R == 0)
			break;

		FOR(i, 0, R)
		{
			scanf("%s %s ", &str1, &str2);
			nMapIterator = nMap.find(str1);
			if(nMapIterator == nMap.end())
				nMap[str1] = Mindex++;

			int x = nMap[str1];

			nMapIterator = nMap.find(str2);
			if(nMapIterator == nMap.end())
				nMap[str2] = Mindex++;

			int y = nMap[str2];

			data[x][y] = 1;
			data[y][x] = 1;
		}

		FOR(k, 0, P)
			FOR(i, 0, P)
			FOR(j, 0, P)
		{
			data[i][j] = min(data[i][j], data[i][k] + data[k][j]);
		}

		int max = -1;

		FOR(i, 0, P)
			FOR(j, 0, P)
		{
			if(max < data[i][j])
				max = data[i][j];
		}

		if(max < 0xffff)
			printf("Network %d: %d\n\n", t++, max);
		else
			printf("Network %d: DISCONNECTED\n\n", t++);

	}

}

#endif