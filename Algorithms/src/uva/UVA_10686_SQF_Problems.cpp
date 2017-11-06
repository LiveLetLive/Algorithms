#include "CommonHeader.h"

#ifdef UVA_10686_SQF_PROBLEMS
READ_INPUT(UVA_10686_SQF_PROBLEMS)

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
int N;


class Cat
{
public:
	void init()
	{
		wordCnt = 0;
		name[0] = 0;
		minL = INF;
		maxL = -1;
	}

	Cat() {
		init();
	}
	char name[31];
	char words[20][31];
	int wHash[20];
	int wordCnt;
	int mCnt;
	int maxL;
	int minL;
};

Cat c[20];

void reset()
{
	FOR(i, 0, 20)
		c[i].init();
}

int hashF(char *s)
{
	int hash = 5381;

	while(*s)
	{
		hash = hash * 33 + *s;
		++s;
	}

	return hash;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &N);

		FOR(i, 0, N)
		{
			scanf("%s ", &c[i].name);
			scanf("%d ", &c[i].wordCnt);
			scanf("%d ", &c[i].mCnt);

			FOR(j, 0, c[i].wordCnt)
			{
				scanf("%s ", &c[i].words[j]);
				c[i].wHash[j] = hashF(c[i].words[j]);
				int l = strlen(c[i].words[j]);

				c[i].minL = (c[i].minL > l) ? l : c[i].minL;
				c[i].maxL = (c[i].maxL < l) ? l : c[i].maxL;
			}
		}

		while(1)
		{
			char str[101] = { 0, };
			cin.getline(str, 110);

			if(str[0] == 0)
				break;

			char str1[101] = { 0, };
			char* ptr = str;

			while(1)
			{
				int l = sscanf(ptr, "%s ", &str1);
				
				ptr += strlen(str1);

				if(l <= 0)
					break;

				int sLen = strlen(str1);

				FOR(i, 0, N)
				{
					if(sLen < c[i].minL || sLen > c[i].maxL)
						continue;

					FOR(j, 0, c[i].wordCnt)
					{

					}
				}
			}
		}

	}
	return 0;
}

#endif
