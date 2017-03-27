#include "CommonHeader.h"

#ifdef SELF_DATA_REARRANGE
READ_INPUT(SELF_DATA_REARRANGE)

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
#define MAXN 100003
#define INF 0x3f3f3f3fL
typedef long long ll;

int data[MAXN];
int N;
int g_CollectedZeroIndex = 0;
int g_CollectedZeroCnt = 0;

void reset()
{
	FOR(i, 0, N)
		data[i] = 0;
	g_CollectedZeroIndex = 0;
}

void MyMove(int from, int to, int size)
{
	FOR(i, 0, size)
		data[to+i] = data[from+i], data[from+i] = 0;
}

void PrintHeader()
{
	FOR(i, 0, N)
		printf("%2d ", i);
	printf("\n");
}
void PrintRam()
{
	printf("\n");

	FOR(i, 0, N)
		printf("%2d ", data[i]);
	printf("\n");
}

void CollectZero()
{
	int s = 0, e = N-1;

	while(1)
	{
		if(s > e)
			break;

		while(data[s++] != 0);
		while(data[e--] == 0);

		if(s > e)
			break;
		s--;
		e++;

		int sizeZero = 0;
		int sizeVal = 0;

		while(data[s+sizeZero] == 0) 
			sizeZero++;
		while(data[e-sizeVal] != 0)
			sizeVal++;

		int size = (sizeZero < sizeVal) ? sizeZero : sizeVal;

		MyMove(e - (size - 1), s, size);
		s += size;
		e -= size;
		PrintRam();
	}

	int start = (s < e) ? s : e;
	while(data[start++] != 0);
	g_CollectedZeroIndex = start-1;
	g_CollectedZeroCnt = (N - g_CollectedZeroIndex) > 64 ? 64 : (N - g_CollectedZeroIndex);
}

void CollectAllData()
{
	int s = 0, e = g_CollectedZeroIndex;

	FOR(f, 1, 10)
	{
		while(1)
		{
			if(s > e)
				break;

			while(data[s++] == f);
			s--;

			int startNQ = s;

			while(s < e)
				if(!(data[s++] != f))
					break;

			s--;

			int endNQ = s - 1;

			int sizeDiff = endNQ - startNQ + 1;
			int sizeVal = 0;

			while(data[s+sizeVal] == f)
				sizeVal++;

			int size = (sizeVal < sizeDiff) ? sizeVal : sizeDiff;
			size = (size < g_CollectedZeroCnt) ? size : g_CollectedZeroCnt;

			if(size == 0)
			{
				s = startNQ;
				break;
			}

			{
				MyMove(startNQ, g_CollectedZeroIndex, size);
				PrintRam();
				MyMove(s, startNQ, size);
				PrintRam();
				MyMove(g_CollectedZeroIndex, s, size);
				PrintRam();
				s = startNQ + size;
			}
		}
	}
}


void reArrange()
{
	CollectZero();
	CollectAllData();
}


int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		FOR(i, 0, N)
			scanf("%d ", &data[i]);

		PrintHeader();
		PrintRam();

		reArrange();
	}
	return 0;
}

#endif
