#include "CommonHeader.h"

#ifdef UVA_10659_FITTING_TEXT_INTO_SLIDES
READ_INPUT(UVA_10659_FITTING_TEXT_INTO_SLIDES)

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 1003
#define INF 0x3f3f3f3fL
typedef long long ll;

int N, M, P;
int X, Y;

char str[100][100][100] = { 0,};
int wlen[100][100];
int wcnt[100];

void reset()
{
}

bool isFit(int s)
{
	int cX = 0, cY = 0;

	if((s * M) > Y)
		return false;

	FOR(p, 0, M)
	{
		int first = 0;
		cY += s, cX = 0;

		FOR(c, 0, wcnt[p])
		{
			int needW = ((wlen[p][c] + first) * s);

			if((cX + needW) > X)
				cY += s, cX = wlen[p][c]*s;
			else
				cX += needW;

			if(cX > X || cY > Y)
				return false;
			first = 1;
		}
	}

	return true;
}

int fsize2()
{
	int font = 0;
	for(font = 28; font >= 8; font--) 
	{
		bool ans = isFit(font);

		if(ans == false)
			continue;
		else
			return font;
	}

	return -1;
}
int fsize()
{
	int lo = 8;
	int hi = 28;
	int ans = -1;

	while (lo <= hi)
	{
		int mid = lo + (hi - lo) / 2;

		if(lo == hi)
			if(isFit(mid) == false)
				return -1;
			else
				return mid;

		if (isFit(mid) == false) 
			hi = mid - 1;
		else
			ans = max(ans, mid), lo = mid + 1;
	}

	return ans;
}

int main()
{
	scanf("%d ", &N);
	FOR(t, 0, N)
	{
		scanf("%d ", &M);

		FOR(i, 0, M)
		{
			char s[1024];
			cin.getline(s,1024);

			int len = strlen(s);

			int widx = 0;
			int idx = 0;
			FOR(j, 0, len)
			{
				if(s[j] == ' ')
				{	wlen[i][widx] = idx; ++widx; idx = 0; continue; }

				str[i][widx][idx++] = s[j];
			}

			wlen[i][widx] = idx;
			wcnt[i] = widx + 1;
		}

		scanf("%d ", &X);
		scanf("%d ", &Y);

		int ans = fsize2();

		if(ans == -1)
			printf("No solution\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}

#endif
