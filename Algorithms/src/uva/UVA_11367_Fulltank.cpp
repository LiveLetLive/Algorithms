#include "CommonHeader.h"


#ifdef UVA_11367_FULLTANK
READ_INPUT(UVA_11367_FULLTANK)

#include <iostream>
#include <cstdio>
#include <queue>
#include <climits>

using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXC 101
#define MAXN 1001
#define MAXM MAXN*MAXC

#define INF INT_MAX
typedef int ll;

typedef struct tagEdge
{
	int idxSecondEdge;
	int wt;
}Edge;

int N, M;
int p[MAXN];
int dp[MAXN][MAXC];
int cntEdge[MAXN];
Edge edge[MAXN][MAXN];
int s,e,c;

#define PRINTF(...) printf(__VA_ARGS__)

inline int MyMin(int i, int j)
{
	return i<j ? i : j;
}

inline int MyMax(int i, int j)
{
	return i>j ? i : j;
}

void AddEdge(int i, int j, int wt)
{
	int idx = cntEdge[i];
	edge[i][idx].wt = wt;
	edge[i][idx].idxSecondEdge = j;
	cntEdge[i]++;
}

void resetDP()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXC)
			dp[i][j] = INF;
	}
}

void reset()
{
	FOR(i, 0, MAXN)
	{
		p[i] = 0;
		cntEdge[i] = 0;

		FOR(j, 0, MAXN)
			edge[i][j].idxSecondEdge = -1, edge[i][j].wt = -1; 
	}
}

class State
{
public:
	State() {}; 
	State(int i,int  f,int  p) 
	{
		nID = i;
		fuel = f;
		priceSpent = p;
	};

	bool operator < (const State& that) const
	{
		return this->priceSpent <= that.priceSpent;
	}

	int nID;
	int fuel;
	int priceSpent;
};


//#define HAVE_STL

#ifdef HAVE_STL

template <class T>
class PQ
{
public:
	std::priority_queue<T> q;
	T deque() { T tmp = q.top(); q.pop(); return tmp;};
	void enqueue(T& s){ q.push(s); }
	bool empty(){ return q.empty(); }
};

#else

template <class T>
class PQ
{
public:
	T q[MAXM];
	int size;

	PQ() 
	{
		size = 0;
		FOR(i,0,MAXM)
			q[i].fuel = 0, q[i].nID = -1, q[i].priceSpent = INF;
	}

	void sink(int i, int N)
	{
		int left = i*2;
		int right = left + 1;

		int mc = -1;

		if(right <= N && q[left] < q[i])
			mc = left;
		else
			mc = i;

		if(right <= N && q[right] < q[mc])
			mc = right;

		if(mc != i && mc != -1)
		{
			swap(q[i], q[mc]);
			sink(mc,N);
		}
	}

	void heapify()
	{
		for(int i = N/2; i >=1 ; i--)
		{
			sink(i,N);
		}
	}

	void heapsort()
	{
		//Heapify
		for(int i = N/2; i >=1 ; i--)
		{
			sink(i,N);
		}

		//Sort
		FOR(i, 1, N+1)
		{
			swap(q[1],q[N-i+1]);
			sink(1, N-i);
		}
	}

	T removeMin(int &size)
	{
		T ret = q[1];
		q[1] = q[size];
		size--;

		sink(1, size);
		return ret;
	}

	T deque() 
	{ 
		return removeMin(size); 
	}

	void enqueue(T& s)
	{ 
		size++;
		q[size] = s;
		swim(size);
	}

	void swim(int idx)
	{
		int parent = idx/2;
		if(q[idx] < q[parent] && idx > 1)
		{
			swap(q[idx], q[parent]);
			swim(parent);
		}

		return;
	}

	bool empty(){ return (size <= 0); }
};


#endif

//#define DEBUG

void PrintDPTable(State &st)
{
	//PRINTF("[nID=%03d Fuel=%02d PriceSpent=%05d]\n", st.nID, st.fuel, (st.priceSpent >= INF) ? -1 : st.priceSpent );
#ifdef DEBUG
	PRINTF("[nID=%03d Fuel=%02d PriceSpent=%05d]\n", st.nID, st.fuel, (st.priceSpent >= INF) ? -1 : st.priceSpent );
	PRINTF("/////////////////////////////////////\n");
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXC)
			PRINTF("%03d ,",   (dp[i][j] >= INF) ? -1 : dp[i][j]);
		PRINTF("\n");
	}
	PRINTF("/////////////////////////////////////\n");
#endif
}

PQ<State> pq;

int dijkastra()
{
	while(!pq.empty()) pq.deque();

	State sLocal(s,0,0);

	pq.enqueue(sLocal);
	dp[s][0] = 0;

	while(!pq.empty())
	{
		State st = pq.deque();

		if(st.nID == e)
			return st.priceSpent;

		if(dp[st.nID][st.fuel] < st.priceSpent)
			continue;

		//Spend 1 more litre of fuel
		if(st.fuel + 1 <= c && dp[st.nID][st.fuel+1] >= st.priceSpent + p[st.nID])
		{
			dp[st.nID][st.fuel+1] = st.priceSpent +  p[st.nID];
			State s(st.nID, st.fuel+1 ,dp[st.nID][st.fuel+1]);
			pq.enqueue(s);
		}

		FOR(idx, 0, cntEdge[st.nID])
		{
			int v = edge[st.nID][idx].idxSecondEdge;

			if(st.fuel >= edge[st.nID][idx].wt)
			{
				int fRemain = st.fuel - edge[st.nID][idx].wt;
				if(st.priceSpent < dp[v][fRemain])
				{
					dp[v][fRemain] = st.priceSpent; 
					State s(v, fRemain, st.priceSpent);
					pq.enqueue(s);
				}
			}
		}
		//PrintDPTable(st);
	}

	return INF;
}

int main()
{
	//freopen("Text.txt", "r", stdin);

	scanf("%d ", &N);

	{
		reset();
		scanf("%d ", &M);

		FOR(k, 0, N)
			scanf("%d ", &p[k]);

		FOR(k, 0, M)
		{
			int i = 0, j = 0;

			scanf("%d ", &i);
			scanf("%d ", &j);

			int tmp = 0;
			scanf("%d ", &tmp);

			AddEdge(i, j, tmp);
			AddEdge(j, i, tmp);
		}

		int Q = 0;
		scanf("%d ", &Q);

		FOR(q, 0, Q)
		{
			resetDP();
			scanf("%d ", &c);
			scanf("%d ", &s);
			scanf("%d ", &e);

			int ans = dijkastra();

			if(ans >= INF)
				printf("impossible\n");
			else
				printf("%d\n", ans);
		}
	}
	return 0;
}

#endif


