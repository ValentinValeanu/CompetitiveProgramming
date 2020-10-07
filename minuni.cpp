#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define MAXN 100100
#define llong long long
#define MAXARB (1<<18)
#define left (nod << 1)
#define right ((nod << 1) | 1)
#define mid ((st+dr) >> 1)

int N, M;
int viz[MAXN], Ind[MAXN], T[MAXN];
pair<int, int> query[MAXN], A[2*MAXN];

int Max[MAXARB];

void update(int nod, int st, int dr, int a, int val)
{
	if(st == dr) { Max[nod] = val; return ; }
	if(a <= mid) update(left, st, mid, a, val);
	if(a > mid) update(right, mid+1, dr, a, val);
	Max[nod] = max(Max[left], Max[right]);
}

int querya(int nod, int st, int dr, int a, int b)
{
	if(st > dr || a > b) return 0;
	if(a <= st && dr <= b)
		return Max[nod];
	int q1 = 0, q2 = 0;
	if(a <= mid) q1 = querya(left, st, mid, a, b);
	if(b > mid) q2 = querya(right, mid+1, dr, a, b);
	return max(q1, q2);
}

void preproc(void)
{
	int i, j, k, timp = 0;
	for(i = 1; i <= M; i++)
		A[i].first = query[i].first, A[i].second = i,
		A[M+i].first = query[i].second, A[M+i].second = i;
	sort(A+1, A+2*M+1);
	for(i = 1; i <= 2*M; i++)
	{
		if(viz[A[i].second] == 0) // deschid
		{
			viz[A[i].second] = 1;
			j = querya(1, 1, M, 1, A[i].second-1);
			Ind[A[i].second] = T[j];
			T[++timp] = A[i].second;
			update(1, 1, M, A[i].second, timp);
		}
		else // inchid
		{
			update(1, 1, M, A[i].second, 0);
		}
	}
}

void read_and_solve(void)
{
	int i, j, k, a, b;

	scanf("%d %d\n", &N, &M);

	for(i = 1; i <= M; i++)
	{
		scanf("%d %d\n", &a, &b);
		query[i].first = a, query[i].second = b;
	}

	preproc();

	for(i = 1; i <= M; i++)
	{
		if(Ind[i] == 0)
			printf("%lld\n", (llong)query[i].first*(N-query[i].second+1));
		else
		{
			int p = query[Ind[i]].first, q = query[Ind[i]].second;
			a = query[i].first, b = query[i].second;
			printf("%lld\n", (llong)a*(q-b)+(llong)(a-p)*(N-b+1)-(llong)(a-p)*(q-b));
		}
	}
}

int main(void)
{
	freopen("minuni.in", "rt", stdin);
	freopen("minuni.out", "wt", stdout);

	read_and_solve();

	return 0;
}
