#include "CommonHeader.h"

#ifdef UVA_12083_GUARDIAN_OF_DECENCY
READ_INPUT(UVA_12083_GUARDIAN_OF_DECENCY)

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
#define MAXN 505
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N;

class Student
{
public:
	Student() {};
	int mf;
	int h;
	int mus;
	int hobb;
};

Student s[MAXN];

map<string, int> music;
map<string, int> hobby;
int musicCnt = 0;
int hobbyCnt = 0;
int musicType, hobbyType;

int g[MAXN][MAXN];
int cnt[MAXN];
int vis[MAXN];
int match[MAXN];

void reset()
{
	music.clear();
	hobby.clear();
	musicCnt = 0;
	hobbyCnt = 0;

	FOR(i, 0, MAXN)
		cnt[i] = 0;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		g[i][j] = 0;

}

void PrepareGraph()
{
	FOR(i, 0, N)
		FOR(j, 0, N)
		if((s[i].mf == 0 && s[j].mf == 1) 
			&& (abs(s[i].h - s[j].h) <= 40) 
			&& (s[i].mus == s[j].mus)
			&& (s[i].hobb != s[j].hobb))
			g[i][cnt[i]++] = j;
}

int Aug(int l)
{
	if(vis[l])
		return 0;

	vis[l] = 1;

	FOR(x, 0, cnt[l])
	{
		int r = g[l][x];
		if(match[r] == -1 || Aug(match[r]))
		{
			match[r] = l;
			return 1;
		}
	}

	return 0;
}

int FindMCBM()
{
	int mcbm = 0;

	memset(match, -1, sizeof(match));

	FOR(l, 0, N)
	{
		memset(vis, 0, sizeof(vis));
		mcbm += Aug(l);
	}
	return mcbm;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();

		FOR(i, 0, N)
		{
			int h;
			char ch;
			char strMusic[101] = { 0} , strHobby[101] = { 0 };
			scanf("%d %c %s %s", &h, &ch, &strMusic, &strHobby);

			if(music[strMusic] == NULL)
				music[strMusic] = ++musicCnt, musicType = music[strMusic];
			else
				musicType = music[strMusic];

			if(hobby[strHobby] == NULL)
				hobby[strHobby] = ++hobbyCnt, hobbyType = hobby[strHobby];
			else
				hobbyType = hobby[strHobby];

			s[i].h = h;
			s[i].mf = (ch == 'M') ? 0 : 1;
			s[i].hobb = hobbyType;
			s[i].mus = musicType;
		}

		PrepareGraph();
		int mcbm = FindMCBM();
		printf("%d\n", N - mcbm);
	}
	return 0;
}

#endif
