#include "CommonHeader.h"

#ifdef UVA_183_BIT_MAPS
READ_INPUT(UVA_183_BIT_MAPS)

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
#define MAXN 201
#define INF 0x3f3f3f3fL
typedef long long ll;
#define DSIZE ((200*200*3)/2) + 5

int W, H;

char Bgrid[MAXN][MAXN];
char DArr[DSIZE];
char type;
int DIndex = 0;
int DReadIdx = 0;
int Dlen = 0; 
int StrLen(char *str)
{
	int len = 0;

	while(*str++) ++len;

	return len;
}

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		Bgrid[i][j] = 0;

	FOR(i, 0, DSIZE)
		DArr[i] = 0;

	DIndex = 0;
	DReadIdx = 0;
}

char ScanBImage(int x1, int y1, int x2, int y2)
{
	char prevChar = -1;

	FOR(i, y1, y2+1)
		FOR(j, x1, x2+1)
	{
		if(prevChar == -1)
		{
			prevChar = Bgrid[i][j];
			continue;
		}

		if(prevChar != Bgrid[i][j])
			return -1;
	}

	return prevChar;
}

void B2D(int x1, int y1, int x2, int y2)
{
	int w = x2 - x1 + 1;
	int h = y2 - y1 + 1;

	if(w == 0 || h == 0)
		return;

	char c = ScanBImage(x1, y1, x2, y2);

	if(c == -1)
	{
		DArr[DIndex++] = 'D';

		B2D(x1,				y1,				x2 - (w/2), y2 - (h / 2));		//Left Top
		B2D(x2 - (w/2) + 1, y1,				x2,			y2 - (h / 2));		//Right Top
		B2D(x1,				y2 - (h / 2)+1,	x2 - (w/2),	y2);				//Left Bottom
		B2D(x2 - (w/2) + 1,	y2 - (h / 2)+1,	x2,			y2);				//Right Bottom
	}
	else
	{
		DArr[DIndex++] = c;
		return;
	}
}


void D2B(int x1, int y1, int x2, int y2)
{
	int w = x2 - x1 + 1;
	int h = y2 - y1 + 1;

	if(Dlen == DReadIdx)
		return;

	if(w == 0 || h == 0)
		return;

	char c = DArr[DReadIdx++];

	if(c == '0' || c == '1')
	{
		FOR(i, 0, h)
			FOR(j, 0, w)
			Bgrid[y1 + i][x1 + j] = c;
		return;
	}
	else if(c == 'D')
	{
		D2B(x1,				y1,				x2 - (w/2), y2 - (h / 2));		//Left Top
		D2B(x2 - (w/2) + 1, y1,				x2,			y2 - (h / 2));		//Right Top
		D2B(x1,				y2 - (h / 2)+1,	x2 - (w/2),	y2);				//Left Bottom
		D2B(x2 - (w/2) + 1,	y2 - (h / 2)+1,	x2,			y2);				//Right Bottom
	}
}

int main()
{
	while(scanf("%c ", &type))
	{
		reset();
		if(type == '#')
			break;

		if(type != '#' && type != 'B' && type != 'D' )
		{
			//_CrtDbgBreak();
			continue;
		}
		scanf("%d %d ", &H, &W);

		if(type == 'B')
		{
			char buf[DSIZE] = { 0 };
			int idx = 0;

			while(idx != W * H)
			{
				scanf("%c", &buf[idx]);
				if(buf[idx] == '\n' || buf[idx] == '\r')
					continue;
				idx++;
			}

			idx = 0;

			FOR(i, 0, H)
				FOR(j, 0, W)
				Bgrid[i][j] = buf[idx++];
			
			B2D(0, 0, W - 1, H - 1);

			printf("D%4d%4d\n", H, W);

			idx = 0;
			int len = StrLen(DArr);
			
			FOR(i, 0, len)
			{
				printf("%c", DArr[i]);

				if(idx == 49)
					printf("\n"), idx = -1;

				++idx;
			}
			
			if(len % 50)
				printf("\n");
		}
		else
		{
			scanf("%s ", &DArr);
			Dlen = StrLen(DArr);
			D2B(0, 0, W - 1, H - 1);

			printf("B%4d%4d\n", H, W);
			int idx = 0;

			FOR(i, 0, H)
				FOR(j, 0, W)
			{
				printf("%c", Bgrid[i][j]);
				if(idx == 49)
					printf("\n"), idx = -1;

				++idx;
			}

			if(idx % 50)
				printf("\n");
		}
	}

	return 0;
}

#endif
