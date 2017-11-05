#include "CommonHeader.h"

#ifdef SELF_CANDYCRUSH1
READ_INPUT(SELF_CANDYCRUSH1)

#include <iostream>
#include <stdio.h>

	using namespace std;

#define MAX_HEIGHT 610
#define MAX_WIDTH 10
#define BLK_SIZE 3

enum ROTATE {
	ROTATE_90 = 1,
	ROTATE_180,
	ROTATE_270,
	ROTATE_360
};

enum CMD {
	INIT = 1,
	NEW_CANDY,
	ROTATE,
	MOVE,
	TIMEDBOMB,
	GROUND
};

// Initialize the grid with a defined width
extern void InitGrid(int width);

// Add a new candy pair at (0,1) locaiton on the top of the grid
extern void AddCandyPair(int candy[]);

// Rotate candy pair by rot steps { 1 -> 90 degree, 2 -> 180 degree, 3 -> 270 degree, 4 -> 360 degree }
extern void RotateCandyPair(int rot);

// Move candy pair horizontally left & right (-10 <= dist <= 10)
extern void MoveCandyPair(int dist);

// Add a bomb chain, with length = count & TimerToBlast = life
extern void AddTimedBomb(int count, int life);

// Drop the candy pair OR bomb to the ground level, return the max height of the top-most row that is occupied (with single candy or more)
extern int GroundCandyPair();

extern void GetTC();

int tc, nc;

int main(void)
{
	int T, WB, NC, cmd;
	int rot, dis, hc, hl;
	int block[2];

	setbuf(stdout, NULL);

	cin >> T;

	for (tc = 0; tc < T; tc++)
	{
		cin >> NC;
		cout << "case #" << tc+1 <<endl;

		nc = 0;

		while (nc < NC)
		{
			cin >> cmd;
			switch (cmd)
			{
			case INIT:
				cin >> WB;
				InitGrid(WB);
				break;
			case NEW_CANDY:
				cin >> block[0] >> block[1];
				AddCandyPair(block);
				break;
			case ROTATE:
				cin >> rot;
				RotateCandyPair(rot);
				break;
			case MOVE:
				cin >> dis;
				MoveCandyPair(dis);
				break;
			case TIMEDBOMB:
				cin >> hc >> hl; 
				AddTimedBomb(hc, hl);
				break;
			case GROUND:
				cout << GroundCandyPair() << endl;
				nc++;
				break;
			} 
		}
	}
}


//////////////////////////////////////////////////////////////

#define FOR(i, init, count) for(int i = init; i < count ; ++i)

int W;
int htArr[MAX_WIDTH];
int grd[MAX_HEIGHT][MAX_WIDTH];
int blk[3][3] = { 0, };
int candyXLoc = 0;
int bombLife = 0;
int bombCnt = 0;
int	isCandy = 0;

int FindMaxHt();

// Initialize the grid with a defined width
void InitGrid(int width)
{
	FOR(i, 0, MAX_HEIGHT)
		FOR(j, 0, MAX_WIDTH)
		grd[i][j] = -1;

	FOR(j, 0, MAX_WIDTH)
		htArr[j] = 0;

	W = width;
}

// Add a new candy pair at (0,1) locaiton on the top of the grid
void AddCandyPair(int candy[])
{
	FOR(i, 0, 3)
		FOR(j, 0, 3)
		blk[i][j] = 0;

	blk[1][1] = candy[0];
	blk[1][2] = candy[1];

	candyXLoc = 0;
	isCandy = 1;
}

//#define DEBUG

void PrintMat(char* str, int s[MAX_HEIGHT][MAX_WIDTH])
{
#ifdef DEBUG
	if(tc == 7)
	{
		printf("%s\n", str);

		int ht = FindMaxHt();

		for(int i = ht - 1; i >= 0; --i)
		{
			FOR(j, 0, W)
				printf("%c", s[i][j] == -1 ? '!' : '0' + s[i][j]);
			printf("\n");
		}
	}
#endif
}

void AdjustPosition()
{
	if(candyXLoc >= 0 &&   candyXLoc <= W - 3)
		return;

	if(candyXLoc < 0)
	{
		//Check Left
		bool found = false;
		FOR(i, 0, 3)
			if(blk[i][0] != 0)
			{
				found = true;
				break;
			}

			if(found)
				candyXLoc = 0;
			else
				candyXLoc = -1;
	}
	else if(candyXLoc > (W-3))
	{
		//Check Right
		bool found = false;
		FOR(i, 0, 3)
			if(blk[i][2] != 0)
			{
				found = true;
				break;
			}

			if(found)
				candyXLoc = W-3;
			else
				candyXLoc = W-2;
	}
}


// Rotate candy pair by rot steps { 1 -> 90 degree, 2 -> 180 degree, 3 -> 270 degree, 4 -> 360 degree }
void RotateCandyPair(int rot)
{
	if(rot == 4)
		return;

	int blk2[3][3] = { 0, };

	FOR(x, 0, rot)
	{
		FOR(i, 0, 3)
			FOR(j, 0, 3)
			blk2[j][i] = blk[i][j];

		FOR(i, 0, 3)
			FOR(j, 0, 3)
			blk[i][2-j] = blk2[i][j];
	}
	AdjustPosition();
}

// Move candy pair horizontally left & right (-10 <= dist <= 10)
void MoveCandyPair(int dist)
{
	candyXLoc += dist;
	AdjustPosition();
}

// Add a bomb chain, with length = count & TimerToBlast = life
void AddTimedBomb(int count, int life)
{
	bombLife = life;
	bombCnt = count;

	isCandy = 0;
}

void Drop()
{
	if(isCandy)
	{
		for(int i = 2; i >= 0; --i)
			FOR(j, 0, 3)
		{
			if(blk[i][j] != 0)
			{
				grd[htArr[candyXLoc + j]][candyXLoc + j] = blk[i][j];
				++htArr[candyXLoc + j];
			}
		}
	}
	else
	{
		FOR(j, 0, bombCnt)
		{
			grd[htArr[j]][j] = 6 + bombLife;
			++htArr[j];
		}
	}
}

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

inline bool isSafe(int i, int j)
{
	if(j < 0 || j >= W)
		return false;

	if(i < 0 || i >= htArr[j] )
		return false;

	if(grd[i][j] == -1)
		return false;

	return true;
}

void MarkScan(int i, int j, int v[MAX_HEIGHT][MAX_WIDTH], int color, int s[MAX_HEIGHT][MAX_WIDTH])
{
	s[i][j] = 1;

	FOR(x, 0, 4)
	{
		int vr = i + dr[x];
		int vc = j + dc[x];

		if(isSafe(vr, vc) == false)
			continue;

		if(s[vr][vc])
			continue;

		if(grd[vr][vc] != color)
			continue;

		MarkScan(vr, vc, v, color, s);
	}
}


void FloodFill(int i, int j, int v[MAX_HEIGHT][MAX_WIDTH], int color, int& len)
{
	v[i][j] = 1;

	FOR(x, 0, 4)
	{
		int vr = i + dr[x];
		int vc = j + dc[x];

		if(isSafe(vr, vc) == false)
			continue;

		if(v[vr][vc])
			continue;

		if(grd[vr][vc] != color)
			continue;

		FloodFill(vr, vc, v, color, ++len);
	}
}
bool Scan()
{
	int v[MAX_HEIGHT][MAX_WIDTH] = { 0,};
	int scn[MAX_HEIGHT][MAX_WIDTH] = { 0,};
	int bombmark[MAX_HEIGHT][MAX_WIDTH] = { 0,};
	bool found = false;

	//Find all candy
	FOR(j, 0, W)
	{
		FOR(i, 0, htArr[j])
		{
			int len = 1;
			if(grd[i][j] != -1 && grd[i][j] != 0 && grd[i][j] < 6 && v[i][j] == 0)
			{
				FloodFill(i, j, v, grd[i][j], len);
				if(len >= 4)
					MarkScan(i, j, v, grd[i][j], scn);
			}
		}
	}

	//Mark bomb
	FOR(j, 0, W)
	{
		FOR(i, 0, htArr[j])
		{
			if(scn[i][j])
			{
				grd[i][j] = 0;
				found = true;
				FOR(x, 0, 4)
				{
					int vr = i + dr[x];
					int vc = j + dc[x];

					if(isSafe(vr, vc) == false)
						continue;

					if(grd[vr][vc] > 6)
						bombmark[vr][vc] = 1;
				}
			}
		}
	}


	if(found)
	{
		//Explode the bomb
		FOR(j, 0, W)
		{
			FOR(i, 0, htArr[j])
			{
				if(bombmark[i][j])
				{
					--grd[i][j];
					if(grd[i][j] == 6)
						grd[i][j] = 0;
				}
			}
		}

		// Merge down
		FOR(j, 0, W)
		{
			int idx = 0;
			FOR(i, 0, htArr[j])
			{
				if(grd[i][j] == 0)
					continue;
				grd[idx][j] = grd[i][j];
				++idx;
			}

			FOR(i, idx, htArr[j])
				grd[i][j] = 0;

			htArr[j] = idx;
		}

		PrintMat("\nMatrix3", grd);

	}
	return found;
}

int FindMaxHt()
{
	int maxHt = -1;

	FOR(i, 0, MAX_WIDTH)
		if(maxHt < htArr[i])
			maxHt = htArr[i];
	return maxHt;
}

// Drop the candy pair OR bomb to the ground level, return the max height of the top-most row that is occupied (with single candy or more)
int GroundCandyPair()
{
	Drop();
	PrintMat("\nMatrix1", grd);

	while(1)
	{
		bool f = Scan();

		if(f)
			PrintMat("\nMatrixT", grd);
		else
			break;
	}
	return FindMaxHt();
}

#endif
