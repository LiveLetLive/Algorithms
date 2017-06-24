#include "CommonHeader.h"
#include <stdio.h> 
#include <stdlib.h>

#ifdef SELF_SORTING_DATA
READ_INPUT(SELF_SORTING_DATA)

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


#define MAX_SIZE 500000 
#define MAX_COUNT 6000000
#define MOVE_OVERHEAD 1024
static int arr[MAX_SIZE];
long long original = 0, checksum = 0;
static int ptr = 0;
static int totalAccessCount = 0;
static int arrSize;
static int saveData[MAX_SIZE];
static int moveOverhead;
static bool moved;

extern void init(); 
extern void run(int);


int move(int position)
{
	if (position < 0 || position >= arrSize) 
		return -1;

	if (moveOverhead > MOVE_OVERHEAD) 
		return -1;

	moveOverhead++; 
	moved = true;

	ptr = position; 
	return arr[ptr];
}


void save(int sector, int length)
{
	if (totalAccessCount >= MAX_COUNT) 
		return;

	totalAccessCount++;

	if (!moved || sector < 0 || length <= 0 || ptr + length > arrSize || sector + length > MAX_SIZE)
		return;

	for (int i = ptr; i < ptr + length; i++)
	{
		if (saveData[sector] != 0) 
			return;
		saveData[sector++] = arr[i];
	}

	moveOverhead = 0; 
	moved = false;
}


void load(int sector, int length)
{
	if (totalAccessCount >= MAX_COUNT) 
		return;

	totalAccessCount++;

	if (!moved || sector < 0 || length <= 0 || ptr + length > arrSize || sector + length > MAX_SIZE) 
		return; 
	
	for (int i = ptr; i < ptr + length; i++)
	{
		if (!saveData[sector]) 
			return;

		arr[i] = saveData[sector];
		saveData[sector] = 0; 
		sector++;
	}
	moveOverhead = 0; 
	moved = false;
}

int check()
{
	int check = arr[0];
	checksum += check;
	for (int i = 1; i < arrSize; i++)
	{
		if (check > arr[i])
			return 0;
		check = arr[i];
		checksum += check;
	}

	if (original != checksum) 
		return 0;

	return 1;
}

void clear()
{
	ptr  = 0;
	moveOverhead = 0;
	checksum = original = 0; 
	totalAccessCount = 0;

	for (int i = 0; i < arrSize; i++) arr[i] = 0;
}


int tc ;
int main()
{
	setbuf(stdout, NULL);

	int T; 
	scanf("%d", &T);

	for (tc = 1; tc <= T ; tc++)
	{
		scanf("%d", &arrSize);


		for (int i = 0; i < arrSize; i++)
		{
			scanf("%d", &arr[i]); 
			original += arr[i];
		}

		init();
		moved = true; 
		run(arrSize);

		int answer = check(); 
		printf("#%d %d, %d\n", tc, answer, totalAccessCount); 
		clear();
	}

}


//int main()
//{
//	int ncount = 50;
//	srand(31);
//	freopen("out.txt", "w", stdout);
//	FOR(i, 0, 6)
//	{
//		int cnt = ncount * pow(10, i);
//
//		cnt = cnt > 500000 ? 500000 : cnt;
//
//		printf("%d\n", cnt);
//
//		FOR(j, 0, cnt)
//		{
//			int x = rand();
//			printf("%d ", x ? x : 1);
//		}
//		printf("\n");
//	}
//}


void init()
{
}

int s[MAX_SIZE];
int idx[MAX_SIZE];

void MySwap(int i, int j)
{
	int tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;

	tmp = idx[i];
	idx[i] = idx[j];
	idx[j] = tmp;
}

int part(int lo, int hi)
{
	int i = lo;
	int j = hi + 1;

	while(1)
	{
		while(s[++i] < s[lo])
			if(i == hi)
				break;

		while(s[--j] > s[lo])
			if(j == lo)
				break;

		if(i >= j)
			break;

		MySwap(i, j);
	}

	MySwap(j, lo);
	return j;
}

void QSort(int lo, int hi)
{
	if(hi <= lo)
		return;
	int p = part(lo, hi);
	QSort(lo, p-1);
	QSort(p+1, hi);
}

void run(int size)
{
	FOR(i, 0, size)
	{
		if(i && (i % (MOVE_OVERHEAD)) == 0)
			move(0), save(0,1) , move(0), load(0,1);

		s[i] = move(i);
		idx[i] = i;
	}

	QSort(0, size-1);

	FOR(i, 0, size)
	{
		int idxTmp = i;

		while(((i+1) < size) && idx[i] + 1 == idx[i+1]) 
			++i;

		int len = i - idxTmp + 1;

		move(idx[idxTmp]);
		save(idxTmp, len); 
	}

	move(0);
	load(0, size);
	return;
}


#endif
