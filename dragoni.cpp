#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <bitset>
#include <string>
#include <vector>
#include <math.h>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <limits.h>
#include <algorithm>
#include <deque>
#include <utility>
#define inf 0x3f3f3f3f
#define eps 1e-9
#define nmax 810
using namespace std;
int n,m,i,x,y,z,maxx,t[810],tip,fr[810][810],cost[810][810];
vector <pair<int,int> > g[810];
bitset <nmax> frr;
queue <pair<int,int> > que;
inline int max(int x,int y) { if (x>y) return x; else return y; }
inline int min(int x,int y) { if (x<y) return x; else return y; }
void dfs(int x)
{
    int i; frr[x]=1;
    if (x!=1) maxx=max(maxx,t[x]);
    for (i=0;i<g[x].size();i++)
        if (g[x][i].second<=y && frr[g[x][i].first]==0) dfs(g[x][i].first);
}
int main(){
	freopen("dragoni.in","r",stdin);
	freopen("dragoni.out","w",stdout);
	scanf("%d",&tip);
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&t[i]);
	for (i=1;i<=m;i++) {
		scanf("%d %d %d",&x,&y,&z);
		g[x].push_back(make_pair(y,z));
		g[y].push_back(make_pair(x,z));
	}
	if (tip==1) {
		maxx=0;  y=t[1]; dfs(1);
		printf("%d\n",maxx);
	} else
	{
		que.push(make_pair(1,1)); memset(cost,inf,sizeof(cost)); cost[1][1]=0;
		while (!que.empty()) {
			x=que.front().first; y=que.front().second; que.pop();
			for (int i=0;i<g[y].size();i++)
			   if (g[y][i].second<=t[x] && cost[x][g[y][i].first]>cost[x][y]+g[y][i].second) {
				   fr[x][g[y][i].first]=1; cost[x][g[y][i].first]=cost[x][y]+g[y][i].second; cost[g[y][i].first][g[y][i].first]=cost[x][g[y][i].first];
				   que.push(make_pair(x,g[y][i].first)); que.push(make_pair(g[y][i].first,g[y][i].first));
			}
		}
		maxx=inf;
		for (i=1;i<=n;i++) maxx=min(maxx,cost[i][n]);
		printf("%d",maxx);
	}
return 0;
}