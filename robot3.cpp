#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#define INF 1000000000

using namespace std;

struct matrix
{
	int m[1010][1010][3];
};

const int moveX[] = {0, 1, 0, -1};
const int moveY[] = {1, 0, -1, 0};

typedef pair <int, int> pii;

int n, nr1;
int minDist, countMinDist;
int t[1010][1010];
matrix dp_s, dp_f;
bool viz[1010][1010];
pii s, f;

void lee(pii sp, matrix &m)
{
	queue<pii> que;

	que.push(sp);
	
	viz[sp.first][sp.second] = true;
	m.m[sp.first][sp.second][0] = m.m[sp.first][sp.second][1] = 0;

	while (!que.empty()) {

		int x = que.front().first;
		int y = que.front().second;

		viz[x][y] = false;

		que.pop();

		for (int i = 0; i < 4; i++) {

			int nextX = x + moveX[i];
			int nextY = y + moveY[i];

			if (t[nextX][nextY] != 0) continue;

			if (x == nextX && m.m[x][y][0] < m.m[nextX][nextY][0]) {

				m.m[nextX][nextY][0] = m.m[x][y][0];

				if (!viz[nextX][nextY]) que.push({ nextX, nextY });

				viz[nextX][nextY] = true;
			}
			else
			if (x != nextX && m.m[x][y][0] + 1 < m.m[nextX][nextY][1]) {
		
				m.m[nextX][nextY][1] = m.m[x][y][0] + 1;

				if (!viz[nextX][nextY]) que.push({ nextX, nextY }); 
					
				viz[nextX][nextY] = true;
			}
			
			if (y == nextY && m.m[x][y][1] < m.m[nextX][nextY][1]) {
				
				m.m[nextX][nextY][1] = m.m[x][y][1];
				
				if (!viz[nextX][nextY]) que.push({ nextX, nextY }); 
				
				viz[nextX][nextY] = true;
			}
			else
			if (y != nextY && m.m[x][y][1] + 1 < m.m[nextX][nextY][0]) {
					
				m.m[nextX][nextY][0] = m.m[x][y][1] + 1;
					
				if (!viz[nextX][nextY]) que.push({ nextX, nextY }); 
					
				viz[nextX][nextY] = true;
			}
		}
	}
}

void solve(matrix &dp_s, matrix &dp_f)
{
	minDist = INF;
	countMinDist = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (t[i][j] == 1) {

				int currentDist = INF;

				for (int li = 0; li < 4; li++)
					for (int lj = 0; lj < 4; lj++)
						if (li != lj) {

							int xin = i + moveX[li];
							int yin = j + moveY[li];

							int xout = i + moveX[lj];
							int yout = j + moveY[lj];

							if (t[xin][yin] != 0 || t[xout][yout] != 0) continue;

							if (xin == xout) {

								currentDist = min(currentDist, min(dp_s.m[xin][yin][0] + dp_f.m[xout][yout][0], dp_s.m[xin][yin][1] + dp_f.m[xout][yout][1] + 2));
								currentDist = min(currentDist, min(dp_s.m[xin][yin][1] + dp_f.m[xout][yout][0] + 1, dp_s.m[xin][yin][0] + dp_f.m[xout][yout][1] + 1));
							} else
							if (yin == yout) {

								currentDist = min(currentDist, min(dp_s.m[xin][yin][1] + dp_f.m[xout][yout][1], dp_s.m[xin][yin][0] + dp_f.m[xout][yout][0] + 2));
								currentDist = min(currentDist, min(dp_s.m[xin][yin][1] + dp_f.m[xout][yout][0] + 1, dp_s.m[xin][yin][0] + dp_f.m[xout][yout][1] + 1));
							} else
							if (xin == i) {

								currentDist = min(currentDist, min(dp_s.m[xin][yin][0] + dp_f.m[xout][yout][0] + 2, dp_s.m[xin][yin][1] + dp_f.m[xout][yout][1] + 2));
								currentDist = min(currentDist, min(dp_s.m[xin][yin][1] + dp_f.m[xout][yout][0] + 3, dp_s.m[xin][yin][0] + dp_f.m[xout][yout][1] + 1));
							} else {

								currentDist = min(currentDist, min(dp_s.m[xin][yin][1] + dp_f.m[xout][yout][0] + 1, dp_s.m[xin][yin][0] + dp_f.m[xout][yout][0] + 2));
								currentDist = min(currentDist, min(dp_s.m[xin][yin][0] + dp_f.m[xout][yout][1] + 3, dp_s.m[xin][yin][1] + dp_f.m[xout][yout][1] + 2));
							}
						}

				if (currentDist < minDist) {

					minDist = currentDist; countMinDist = 1;
				}
				else
					if (currentDist == minDist) countMinDist++;
			}
}

int main()
{
	freopen("robot3.in", "r", stdin);
	freopen("robot3.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &t[i][j]);

			if (t[i][j] == 1) nr1++;
		}

	scanf("%d %d %d %d", &s.first, &s.second, &f.first, &f.second);

	for (int i = 0; i <= n + 1; i++) t[0][i] = t[i][0] = t[n + 1][i] = t[i][n + 1] = -1;

	for (int i = 0; i <= n + 1; i++)
		for (int j = 0; j <= n + 1; j++)
			dp_s.m[i][j][0] = dp_s.m[i][j][1] = dp_f.m[i][j][0] = dp_f.m[i][j][1] = INF;

	lee(s, dp_s);
	lee(f, dp_f);

	solve(dp_s, dp_f);

	if (min(dp_s.m[f.first][f.second][0], dp_s.m[f.first][f.second][1]) == minDist) printf("%d %d %d", min(dp_s.m[f.first][f.second][0], dp_s.m[f.first][f.second][1]), minDist, nr1); else
		printf("%d %d %d", min(dp_s.m[f.first][f.second][0], dp_s.m[f.first][f.second][1]), minDist, countMinDist);

	return 0;
}