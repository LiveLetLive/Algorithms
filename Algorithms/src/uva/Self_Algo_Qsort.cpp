#include "CommonHeader.h"

#ifdef SELF_ALGO_QSORT
READ_INPUT(SELF_ALGO_QSORT)

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

class Node
{
public:
	int val;
	int idx;
	bool operator <(Node &that)
	{
		return this->val < that.val;
	}
	bool operator >(Node &that)
	{
		return this->val > that.val;
	}
};


Node s[10];
int m[] = { 3,7, 2, 0, 5, 8, 9};
int save[] = { 0,0, 0, 0, 0, 0, 0};

//int s[50005];

#define CountOf(a) sizeof(a)/sizeof(a[0])

void PrintArr()
{
	FOR(i, 0, CountOf(s))
	{
		printf("%d ", s[i]);
	}

	printf("\n");
}

void mySwap(int i, int j)
{
}

int part(int lo, int hi)
{
	int i = lo;
	int j = hi+1;

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

		swap(s[i], s[j]);
	}

	swap(s[lo], s[j]);
	return j;
}

void Qsort(int lo, int hi)
{
	if(hi <= lo) return;
	int p = part(lo, hi);
	Qsort(lo, p-1);
	Qsort(p+1, hi);
}

static int fFixS = 0;
void Save(int sec, int len)
{
	fFixS++;

	FOR(i, sec, sec+len)
		save[i] = m[s[i].idx];
}

void Load(int sec, int len)
{

}

int main()
{
	FOR(i, 0, 7)
		s[i].idx = i, s[i].val = m[i];

	Qsort(0, 6);

	FOR(i, 0, 7)
	{
		int idx = i;
		while(i < 6 && s[i+1].idx == s[i].idx + 1)
			i++;

		//Save
		Save(idx, i - idx + 1);
	}

	return 0;
}

#endif
