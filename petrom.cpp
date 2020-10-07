#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int n, k;
int t[510], sum[510], dp[510][510], best[510][510], p[510][510];
pair <int, int> _path[510][510];

void find_path(int x, int y)
{
	if (x <= 0) return;
	
	find_path(x - 1, _path[x][y].first);
	
	cout << _path[x][y].second << '\n';
}

int main()
{
	freopen("petrom.in", "r", stdin);
	freopen("petrom.out", "w", stdout);

	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) cin >> t[i];
	
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + t[i];
	
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
		
			// in interval [i, j] assume that l is the best option
		
			int answer = 2e9;
			int middle = -1;
		
			for (int l = i; l <= j; l++) {
				
				int y = ( t[l] * (l - i) - (sum[l - 1] - sum[i - 1]) ) + ( (sum[j] - sum[l]) - t[l] * (j - l) );
				
				if (y < answer) {
					
					answer = y;
					middle = l;
				}
			}
			
			p[i][j] = middle;
			dp[i][j] = answer;
		}
		
	for (int i = 0; i <= k; i++) 
		for (int j = 0; j <= n; j++) 
			best[i][j] = 2e9;
			
	best[0][0] = 0;
	
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= n; j++) {
		
			if (best[i - 1][j - 1] == 2e9) continue;
			
			for (int l = j; l <= n; l++)
				if (best[i - 1][j - 1] + dp[j][l] < best[i][l]) {
					
					best[i][l] = best[i - 1][j - 1] + dp[j][l];
					
					_path[i][l] = { j - 1, p[j][l] };
				}
		}
		
	cout << best[k][n] << '\n';
	
	find_path(k, n);
	
	return 0;
}