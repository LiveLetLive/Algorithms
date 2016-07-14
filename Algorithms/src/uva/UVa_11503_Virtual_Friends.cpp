#include "CommonHeader.h"

#ifdef UVA_11503_VIRTUAL_FRIENDS
READ_INPUT(UVA_11503_VIRTUAL_FRIENDS)

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 100005

int E;
int p[MAXN];
int rnk[MAXN];
int setSize[MAXN];

class edge
{
public:
	int x;
	int y;
};

void reset()
{
	FOR(i, 0, E)
		p[i] = -1, rnk[i] = 0, setSize[i] = 1;
}

map<string, int> gmap;
map<string, int>::iterator gmap_it;

int find(int x)
{
	if(p[x] == -1) return x;
	else return p[x] = find(p[x]);
}

void Union(int x, int y)
{
	int px = find(x);
	int py = find(y);

	if(px != py)
	{
		if(rnk[px] > rnk[py])
			p[py] = px, setSize[px] += setSize[py];
		else
		{
			p[px] = py;
			setSize[py] += setSize[px];
			if(rnk[px] == rnk[py]) 
				rnk[py]++;
		}
	}
}

int Size(int x, int y)
{
	Union(x, y);
	return setSize[find(x)];
}

int main()
{
	int T;
	int ncnt = 0;
	scanf("%d", &T);
	//FILE *fp = fopen("out.txt", "w+");

	FOR(t, 0, T)
	{
		gmap.clear();
		int nodeIndex = 0;
		scanf("%d", &E);
		reset();

		FOR(i, 0, E)
		{
			int x, y;
			string str1;
			string str2;
		
			cin >> str1;
			cin >> str2;

			gmap_it = gmap.find(str1);

			if(gmap_it == gmap.end())
				p[nodeIndex] = -1, rnk[nodeIndex] = 0, setSize[nodeIndex] = 1, x = gmap[str1] = nodeIndex++;
			else
				x = gmap[str1];

			gmap_it = gmap.find(str2);

			if(gmap_it == gmap.end())
				p[nodeIndex] = -1, rnk[nodeIndex] = 0, setSize[nodeIndex] = 1, y = gmap[str2] = nodeIndex++;
			else
				y = gmap[str2];

			ncnt++;
			//fprintf(fp, "%d\n", Size(x, y));
			printf("%d\n", Size(x, y));
		}

	}

	//fclose(fp);
	return 0;
}

#endif