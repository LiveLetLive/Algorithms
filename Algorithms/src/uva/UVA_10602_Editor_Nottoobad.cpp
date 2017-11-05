#include "CommonHeader.h"

#ifdef UVA_10602_EDITOR_NOTTOOBAD
READ_INPUT(UVA_10602_EDITOR_NOTTOOBAD)

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
#define MAXN 103
#define INF 0x3f3f3f3fL
typedef long long ll;

int N;
char words[MAXN][MAXN];
unsigned char mat[MAXN][MAXN];
unsigned char len[MAXN];

void reset()
{
}

unsigned char StrCmp(char *s1, char *s2)
{
	unsigned char l = 0;

	while(s1 && s2 && *s1 && *s2 && *s1 == *s2)
		++l, ++s1, ++s2;
	return l;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		FOR(i, 0, N)
			scanf("%s ", &words[i]);

		FOR(i, 0, N)
		{
			len[i] = strlen(words[i]);

			FOR(j, 0, N)
			{
				if(i == j) continue;
				mat[i][j] = StrCmp(words[i], words[j]);
			}
		}


		{
			unsigned char select[MAXN] = { 0, };
			unsigned char visit[MAXN] = { 0, };
			int idx = 0;
			int ans = len[0];
			FOR(i, 0, N)
			{
				int mx = -1;
				select[i] = idx;
				visit[idx] = 1;
				
				bool found = false;
				int next = idx;

				FOR(j, 0, N)
				{
					if(idx == j) continue;
					if(visit[j]) continue;

					found = true;

					if(mx < mat[idx][j])
						mx = mat[idx][j], next = j;
				}

				if(found)
					idx = next, ans += ((len[idx] - mx));
			}

			printf("%d\n", ans);
			FOR(i, 0, N)
				printf("%s\n", words[select[i]]);
		}
	}
	return 0;
}

#endif
