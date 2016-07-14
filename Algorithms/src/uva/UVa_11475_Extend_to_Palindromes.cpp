#include "CommonHeader.h"

#ifdef UVA_11475_EXTEND_TO_PALINDROMES
READ_INPUT(UVA_11475_EXTEND_TO_PALINDROMES)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 100005

char str[MAXN*2];
char p[MAXN*2];
int b[MAXN*2];
int slen = 0;

void reset()
{
	FOR(i, 0, (slen*2))
		p[i] = 0, b[i] = 0;
}

void kmpPreProcess()
{
	int i = 0;
	int j = -1;
	b[0] = -1;

	while(i < slen)
	{
		while(j >= 0 && (p[i] != p[j]) ) 
			j = b[j];

		j++;
		i++;
		b[i] = j;
	}
}

int kmp()
{
	kmpPreProcess();
	int j = 0;
	int i = 0;

	while(i < slen)
	{
		while(j >= 0 && (str[i] != p[j]) ) 
			j = b[j];

		j++;		
		i++;
	}

	return j;
}


int main()
{
	while(scanf("%s ", &str) != EOF)
	{
		slen = strlen(str);
		reset();

		FOR(i, 0, slen)
			p[slen - i - 1] = str[i];

		p[slen] = 0;

		int idx = kmp();

		if(idx == slen)
			printf("%s\n", str);
		else
		{
			int len = slen - idx;
			FOR(i, 0, len)
				str[slen+i] = str[len-i-1];
			
			str[slen + len] = 0;
	
			printf("%s\n", str);
		}

	}
	return 0;
}

#endif