#include "CommonHeader.h"

#ifdef UVA_12467_SECRET_WORD
READ_INPUT(UVA_12467_SECRET_WORD)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1000005

char str[MAXN*2];
char p[MAXN*2];
int b[MAXN*2];
int slen = 0;

void reset()
{
	FOR(i, 0, (slen*2))
		str[i] = 0, b[i] = 0;
}

void kmpPreProcess()
{
	int i = 0; 
	int j = -1;
	b[0] = -1;

	while(i < slen)
	{
		while(j >= 0 && p[i] != p[j])
			j = b[j];

		j++, i++;
		b[i] = j;
	}

}

int kmp()
{
	kmpPreProcess();

	int i = 0;
	int j = 0;
	int maxVal = -1;
	while(i < slen)
	{
		while(j >= 0 && str[i] != p[j])
			j = b[j];

		j++, i++;

		maxVal = max(maxVal, j);
	}

	return maxVal;
}


int main()
{
	int T;
	scanf("%d ", &T);
	while(T--)
	{
		scanf("%s ", &p);
		slen = strlen(p);
		reset();

		FOR(i, 0, slen)
			str[slen - i - 1] = p[i];

		str[slen] = 0;

		// Return largest palindrome.
		int idx = kmp();

		for(int i = idx - 1 ; i >= 0 ; i--)
			printf("%c", p[i]);

		printf("\n");

	}
	return 0;
}

#endif