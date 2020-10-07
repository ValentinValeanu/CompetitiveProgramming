#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define NMAX 100010
#define inf 1000000000
#define INF (1LL << 60)

#define MP make_pair
#define ff first
#define ss second

#define LL long long

#define tip_leg vector <pair<int, pair<int, int> > >

int N;

tip_leg leg[NMAX];
int djos[NMAX];
LL cadd1[NMAX];

LL rez = 0;

int viz[NMAX];

void back(int x)
{
	int nr = 0;

	viz[x] = 1;

	for (tip_leg :: iterator it = leg[x].begin(); it != leg[x].end(); ++it) {
		if (!viz[it->ff]) {
			nr++;
			back(it->ff);

			djos[x] = max(djos[x], it->ss.ff + djos[it->ff]);
			cadd1[it->ff] = min(cadd1[it->ff], (LL) it->ss.ss);
			cadd1[x] = cadd1[x] + cadd1[it->ff];

			viz[it->ff] = x;
		}
	}

	if (nr == 0) cadd1[x] = INF;

	for (tip_leg :: iterator it = leg[x].begin(); it != leg[x].end(); ++it) {
		if (viz[it->ff] != x) continue;


		rez += cadd1[it->ff] * (djos[x] - (djos[it->ff] + it->ss.ff));
	}
}

int main()
{
	int i, x, y, dst, cst;

	freopen("arb1.in", "r", stdin);
	freopen("arb1.out", "w", stdout);

	scanf("%d", &N);

	for (i = 1; i < N; i++) {
		scanf("%d %d %d %d", &x, &y, &dst, &cst);

		leg[x].push_back(MP(y, MP(dst, cst)));
		leg[y].push_back(MP(x, MP(dst, cst)));
	}

	back(1);

	printf("%lld\n", rez);

	return 0;
}
