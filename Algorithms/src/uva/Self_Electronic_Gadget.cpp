#include "CommonHeader.h"

#ifdef SELF_ELECTRONIC_GADGET
READ_INPUT(SELF_ELECTRONIC_GADGET)

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
#define MAXN 10003
#define INF 0x3f3f3f3fL
typedef long long ll;


int b[10];
int bcnt = 0;
int w[10];
int wcnt = 0;

int sw[10][4];
int currTryIdx = 0;
int currTryVal = 1;
int stage = 0;
int oldInput[4];


typedef struct
{
	int har;
	int iso;
}MatchRes;

typedef struct Result
{
	int in[4];
	MatchRes m;
}Res;

Res steps[100];
int stepIdx;

void PrintDebug()
{
	FOR(i, 0, stepIdx)
	{
		printf("{ ");
		FOR(j, 0, 4)
			printf("%d, ", steps[i].in[j]);
		printf("[%d, %d]", steps[i].m.har, steps[i].m.iso);
		printf(" }\n");
	}
}

void init()
{
	FOR(i, 0, 100)
	{
		steps[i].m.har = 0;
		steps[i].m.iso = 0;
		FOR(j, 0, 4)
			steps[i].in[j] = -1;
	}

	stepIdx = 0;

	FOR(i, 0, 10)
	{
		b[i] = -1, w[i] = -1, oldInput[i] = -1;
		FOR(j, 0, 4)
			sw[i][j] = 1;
	}
	currTryIdx = 0;
	currTryVal = 1;
	stage = 0;
	bcnt = 0;
	wcnt = 0;
}

MatchRes match(int inputD[])
{
	MatchRes r = {0};
	return r;
}

void UpdateStep(int in[], MatchRes m)
{
	int idx = stepIdx++;
	steps[idx].m.har = m.har;
	steps[idx].m.iso = m.iso;
	FOR(j, 0, 4)
		steps[idx].in[j] = in[j];
}

void HarIsoTrivialCheck(MatchRes n, int in[])
{
	if(n.har == 0)
		FOR(i, 0, 4)
		sw[in[i]][i] = 0;
	else if(n.har == 4)
		FOR(i, 0, 4)
		w[wcnt++] = in[i];

	if(n.iso == 0)
		FOR(i, 0, 4)
		b[bcnt++] = in[i];
	else if(n.iso == 4)
		FOR(i, 0, 4)
		w[wcnt++] = in[i];
}

void UpdateAllDB(int in[], int oldin[], MatchRes n, MatchRes o)
{
	//Just update database without decision
	if(oldin == NULL)
	{

		UpdateStep(in, n);
	}

	//Make decision 
}

int getStatus(MatchRes n)
{
	if(n.har == 4)
		return 2;
	if(n.iso == 4)
		return 1;
	return 0;
}

void solve(int inputD[])
{
	init();

	inputD[0] = 0;
	inputD[1] = 7;
	inputD[2] = 8;
	inputD[3] = 9;

	MatchRes or = match(inputD);

	int ret = getStatus(or);
	if(ret == 2) return;
	else if(ret == 1) stage = 1;
	
	UpdateAllDB(inputD, NULL, or, or);

	MatchRes r = { 0, 0};

	while(1)
	{
		//Finding whitelist
		if(stage == 0)
		{
			r = match(inputD);
			int ret = getStatus(r);
			if(ret == 2) return;
			else if(ret == 1) stage = 1;
		
			UpdateAllDB(inputD, oldInput, r, or);

			or = r;
			FOR(i, 0, 4) oldInput[i] = inputD[i];
			continue;
		}
		// Finding indexes
		else
		{
		}
		//update all b, w, sw

	}
}


int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{


	}
	return 0;
}

#endif
