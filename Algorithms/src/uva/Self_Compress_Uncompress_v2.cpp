#include "CommonHeader.h"

#ifdef SELF_COMPRESS_UNCOMPRESS
READ_INPUT(SELF_COMPRESS_UNCOMPRESS)

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


#include<stdio.h> 
#include<stdlib.h>

int N;

#define T 50
#define MAXVAL 999996 
#define MAXS 166666

static char TC[T][MAXVAL]; 
static int OP[T][MAXS]; 
static char ANS[T][MAXVAL]; 
static int length[T];

static char c[31]  = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n', 'o','p','q','r','s','t','u','v','w','x','y','z','+','-','/','*',' '
};


extern void compress(const char *input, int inputLength, int *output, int outputLength); 
extern void decompress(const int *input, int inputLength, char *output, int outputLength); 
extern void Init();


void generateTC()
{
	{
		N = MAXVAL;
		length[0] = N;
		for(int j=0;j<N;j++)
			TC[0][j] = c[rand()%31];
	}

	for(int i = 1; i < T;i++)
	{
		N = 500000 + rand() % 500000; 
		N = N - N%6;

		length[i] = N; 
		for(int j=0;j<N;j++)
			TC[i][j] = c[rand() % 31];
	}
}


int tcorder[T] = {0,}; 
int visited[T] = {0,};
int op[50];


//int main()
//{
//	char str[50] = {0,};
//	char str2[50] = {0,};
//
//	strncpy(str, c, 31);
//	str[31] = 0;
//
//	printf("%s\n", str);
//	compress(str, 31, op, 50);
//	decompress(op, 50, str2, 50);
//	str2[49] = 0;
//
//	printf("%s\n", str2);
//
//}



int main()
{
	int t = 0,i,j; 
	srand(31);

	while(t != T)
	{
		i = rand() % T; 
		if(visited[i] == 0)
		{
			tcorder[t] = i; 
			visited[i] = 1; 
			t++;

		}
	}

	generateTC(); 
	Init();

	for(i = 0;i < T; i++)
		compress(TC[tcorder[i]], length[tcorder[i]], OP[tcorder[i]], MAXS);

	for(i=0;i<T;i++)
		decompress(OP[i], MAXS, ANS[i], MAXVAL);

	for(i = 0; i < T; i++) 
	{
		int lim = length[i]; 
		for(j = 0;j < lim;j++) 
		{
			if(TC[i][j] != ANS[i][j])
			{
				printf("0\n"); 
				break;
			}
		}
		if(j == lim)
			printf("1\n");
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

struct Header
{
	struct Stuff
	{
		unsigned int len:2;
		unsigned int a11:5;
		unsigned int a12:5;
		unsigned int a13:5;
		unsigned int a14:5;
		unsigned int a15:5;
		unsigned int a16:5;
	} TenSuff[10];
};

void MemCpy(void* dest, void* src, int n)
{
	char *d = (char*) dest;
	char *s = (char*) src;
	while(n--)
		*d++ = *s++;
}

typedef struct strTab
{
	char c;
	int idx;
}Tab;

const Tab sp[] = 
{
	{ '+', 1 },
	{ '-', 2 },
	{ '/', 3 },
	{ '*', 4 },
	{ ' ', 5 }
};

#define CountOf(x) sizeof(x)/sizeof(x[0])

int GetIndex(char c)
{
	if(c >= 'a' && c <= 'z')
		return c - 'a';

	FOR(i, 0, CountOf(sp))
		if(c == sp[i].c)
			return 'z' - 'a' + sp[i].idx;
}

char GetChar(int idx)
{
	idx &= 0x1F;
	if(idx >= 'a' - 'a' && idx <= 'z' - 'a')
		return idx + 'a';

	int sIdx = idx - ('z' - 'a');

	FOR(i, 0, CountOf(sp))
		if(sIdx == sp[i].idx)
			return sp[i].c;
}


void compress(const char *input, int inputLength, int *output, int outputLength)
{
	struct Header h = { 0,};
	int sizeOfHeader = sizeof(h);

	FOR(i, 0, 10)
	{
		h.TenSuff[i].len = (inputLength & (0x3 << (i*2))) >> (i*2);
		h.TenSuff[i].a11 = GetIndex(input[6 * i + 0]);
		h.TenSuff[i].a12 = GetIndex(input[6 * i + 1]);
		h.TenSuff[i].a13 = GetIndex(input[6 * i + 2]);
		h.TenSuff[i].a14 = GetIndex(input[6 * i + 3]);
		h.TenSuff[i].a15 = GetIndex(input[6 * i + 4]);
		h.TenSuff[i].a16 = GetIndex(input[6 * i + 5]);
	}

	MemCpy(output, &h, sizeOfHeader);

	int *ptr = (int*)((char*)output + sizeOfHeader);

	for(int i = 0; i < inputLength - 60; )
	{
		int k = i/6;
		ptr[k] = 0;

		for(int j = 0; j < 6 && i < (inputLength - 60); ++j) 
			ptr[k] |= (GetIndex(input[i+60]) << (5 * j)), ++i;
	}
}

void decompress(const int *input, int inputLength, char *output, int outputLength)
{
	struct Header *h1 = (struct Header*)input;
	struct Header h = *h1;
	int len = 0;

	int sizeOfHeader = sizeof(h);

	FOR(i, 0, 10)
		len |= (h.TenSuff[i].len << (i*2));

	int idx = 0;

	FOR(i, 0, 10)
	{
		output[6 * i + 0] = GetChar(h.TenSuff[i].a11);
		if(++idx >= len) break;
		output[6 * i + 1] = GetChar(h.TenSuff[i].a12);
		if(++idx >= len) break;
		output[6 * i + 2] = GetChar(h.TenSuff[i].a13);
		if(++idx >= len) break;
		output[6 * i + 3] = GetChar(h.TenSuff[i].a14);
		if(++idx >= len) break;
		output[6 * i + 4] = GetChar(h.TenSuff[i].a15);
		if(++idx >= len) break;
		output[6 * i + 5] = GetChar(h.TenSuff[i].a16);
		if(++idx >= len) break;
	}

	char *ptr = (char*)((char*)output + 60);

	for(int i = 0; i < (len - 60); )
	{
		int k = i/6;
		int tmp = input[k+10];

		for(int j = 0; j < 6 &&  i < (len - 60); ++j)
		{
			int idx = (tmp >> (5*j)) & 0x1F;
			ptr[i++] = GetChar(idx);
		}
	}
}

void Init()
{
}


#endif
