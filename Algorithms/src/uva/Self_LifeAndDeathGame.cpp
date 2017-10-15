#include "CommonHeader.h"

#ifdef SELF_LIFEANDDEATHGAME
READ_INPUT(SELF_LIFEANDDEATHGAME)
#include <stdio.h>

	static const int INIT_METHOD = 0;
static const int CHANGE_CELL_STATE_METHOD = 1;
static const int SIMULATE_METHOD = 2;
static const int EDIT_BOARD_METHOD = 3;
static const int SHOW_METHOD = 4;

static const int ROTATE_LEFT = 0;
static const int ROTATE_RIGHT = 1;

static const int MAX_SIZE = 800;
typedef struct {
	int height;
	int width;
	int matrix[MAX_SIZE][MAX_SIZE];
} board;

void init(int width, int height);
void changeCellState(int row, int column);
void simulate(int times);
void editBoard(int editType);
board* show();

int getStrLen(char* str);
int doHash(board* b);

int main() {
	//freopen("input.txt", "r", stdin);

	int tests;
	scanf("%d", &tests);
	int totalActualPoints = 0;
	int totalUserPoints = 0;
	for (int i = 0; i<tests; i++) {
		int actualPoints = 0;
		int userPoints = 0;

		int numberOfMethodCalls;
		scanf("%d", &numberOfMethodCalls);
		for (int j = 0; j<numberOfMethodCalls; j++) {
			int methodName;
			scanf("%d", &methodName);

			switch (methodName) {
			case INIT_METHOD:
				{
					int width;
					scanf("%d", &width);
					int height;
					scanf("%d", &height);
					init(width, height);
				}
				break;
			case CHANGE_CELL_STATE_METHOD:
				{
					int row;
					scanf("%d", &row);
					int column;
					scanf("%d", &column);
					changeCellState(row, column);
				}
				break;
			case SIMULATE_METHOD:
				{
					int times;
					scanf("%d", &times);
					simulate(times);
				}
				break;
			case EDIT_BOARD_METHOD:
				{
					char types[200];
					scanf(" %[^\r\n]", types);
					int typesLength = getStrLen(types);
					for (int k = 0; k<typesLength; k++) {
						int editType = types[k] - 48;
						editBoard(editType);
					}
				}
				break;
			case SHOW_METHOD:
				{
					board* br = show();
					int userHash = doHash(br);
					int actualHash;
					scanf("%d", &actualHash);

					actualPoints++;
					if (userHash == actualHash) {
						userPoints++;
					}
				}
				break;
			}
		}

		printf("Test-%d points: %d of %d\n", (i + 1), userPoints, actualPoints);
		totalUserPoints += userPoints;
		totalActualPoints += actualPoints;
	}
	printf("-----------------------------\n");
	printf("Total points: %d of %d\n", totalUserPoints, totalActualPoints);

	fclose(stdin);
	return 0;
}

int getStrLen(char* str) {
	int len = 0;

	while (str[len]) {
		len++;
	}

	return len;
}

int doHash(board* b) {
	int hash = 0;

	for (int i = 0; i<b->height; i++) {
		for (int j = 0; j<b->width; j++) {
			hash += (b->matrix[i][j] * (i + j) * 7) % (j + 7);
		}
	}

	return hash;
}


//////////////////////////////

//User Code

#define FOR(i, init, count) for(int i = init; i < count; ++i)

board b;

int inEditMode = 0;

class Point
{
public:
	Point() {};
	Point(int l, int c1, int r1)
	{
		alive = l, r = r1, c = c1;
	}
	bool alive;
	int c, r;
};

class Queue
{
public:
	Queue()
	{
		reset();
	}

	void reset()
	{
		front = 0, tail = 0;
	}

	Point& pop() { return p[tail++]; }
	void push(Point p1) { p[front++] = p1; }
	bool isEmpty() { return front == tail; }

	Point p[MAX_SIZE*MAX_SIZE+5];
	int front;
	int tail;
};

Queue qp[2];
int activeQ;
int transform;
void init(int width, int height) 
{
	b.width = width;
	b.height = height;

	FOR(i, 0, height)
		FOR(j, 0, width)
		b.matrix[i][j] = 0;
	activeQ = 0;
	inEditMode = 0;
	transform = 0;
	qp[0].reset();
	qp[1].reset();
}

//#define DEBUG

void printboard(int i)
{
#ifdef DEBUG
	printf(" %d //////////////////////////\n\n", i);
	FOR(i, 0, b.height)
	{
		FOR(j, 0, b.width)
			printf("%d ", b.matrix[i][j]);
		printf("\n");
	}
	printf("//////////////////////////\n\n");
#endif
}
void checkAndApplyEdit()
{
	if(inEditMode)
	{
		inEditMode = 0;
		printboard(100);

		qp[activeQ].reset();

		FOR(i, 0, transform)
		{
			int mat[MAX_SIZE+1][MAX_SIZE+1];
			FOR(i, 0, b.height)
				FOR(j, 0, b.width)
				mat[j][i] = b.matrix[i][j];

			int tmp = b.height;
			b.height = b.width;
			b.width = tmp;

			FOR(i, 0, b.height)
				FOR(j, 0, b.width)
			{
				b.matrix[i][j] = mat[i][b.width - j - 1];

				if(b.matrix[i][j])
					qp[activeQ].push(Point(1, j, i));
			}
		}

		transform = 0;
		printboard(200);
	}
}


void changeCellState(int row, int column) 
{
	checkAndApplyEdit();

	if(b.matrix[row][column])
	{
		b.matrix[row][column] = 0;
	}
	else
	{
		b.matrix[row][column] = 1;
		qp[activeQ].push(Point(1, column, row));
	}
}

int dr[] = { -1, -1, -1,  0, 0, 1, 1, 1 };
int dc[] = { -1,  0,  1, -1, 1, -1, 0, 1 };


void simulate(int times) 
{
	Queue qd;
	Queue ql;
	checkAndApplyEdit();

	FOR(i, 0, times)
	{
		qd.reset();
		ql.reset();
		printboard(i);
		int v[800][800] = { 0, };
		int alt = activeQ ^ 1;
		qp[alt].reset();

		while(qp[activeQ].isEmpty() == false)
		{
			Point p = qp[activeQ].pop();
			if(p.alive)
			{
				int nCnt = 0;
				FOR(x, 0, 8)
				{
					int vr = p.r + dr[x];
					int vc = p.c + dc[x];

					if(vr < 0 || vr >= b.height || vc < 0 || vc >= b.width)
						continue;

					if(b.matrix[vr][vc] == 1)
						++nCnt;
					else
					{
						if(v[vr][vc] == 0)
							v[vr][vc] = 1, qp[activeQ].push(Point(0, vc, vr));
					}
				}

				if(nCnt < 2 || nCnt > 3)
				{
					qd.push(Point(0, p.c, p.r));
				}
				else
				{
					qp[alt].push(Point(1, p.c, p.r));
				}
			}
			else
			{
				int nCnt = 0;
				FOR(x, 0, 8)
				{
					int vr = p.r + dr[x];
					int vc = p.c + dc[x];

					if(vr < 0 || vr >= b.height || vc < 0 || vc >= b.width)
						continue;

					if(b.matrix[vr][vc] == 1)
						++nCnt;
				}

				if(nCnt == 3)
				{
					ql.push(Point(1, p.c, p.r));
					qp[alt].push(Point(1, p.c, p.r));
				}
			}
		}

		while(qd.isEmpty() == false)
		{
			Point p = qd.pop();
			b.matrix[p.r][p.c] = 0;
		}
		while(ql.isEmpty() == false)
		{
			Point p = ql.pop();
			b.matrix[p.r][p.c] = 1;
		}

		activeQ = alt;
	}
}

void editBoard(int editType) 
{
	inEditMode = 1;
	if(editType == 0)
	{
		--transform;
		if(transform < 0)
			transform = 3;
	}
	else
	{
		++transform;
		transform %= 4;
	}
}

board* show() 
{
	checkAndApplyEdit();
	return &b;
}

#endif
