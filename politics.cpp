#include <stdio.h>
#include <vector>
#include <algorithm>
#define nmax 1010

using namespace std;

struct date { int x,y; };

int n,m,x,y;
int tata[nmax],sz[nmax],rang[nmax];
bool dad[nmax];
date t[50*nmax],p[nmax];

bool cmp1(const date &a,const date &b) { return (a.x<b.x); }
bool cmp2(const date &a,const date &b) { return (a.y>b.y); }

int root(int x)
{
    if (x==tata[x]) return x; else
        return tata[x]=root(tata[x]);
}

void unite(int x,int y)
{
    x=root(x); y=root(y);

    if (x!=y) {

        if (rang[x]>rang[y]) tata[y]=x,sz[x]=sz[x]+sz[y]; else
            tata[x]=y,sz[y]=sz[y]+sz[x];

        if (rang[x]==rang[y]) rang[y]++;

    }

}

int main()
{
    freopen("politics.in","r",stdin);
    freopen("politics.out","w",stdout);

    scanf("%d %d",&n,&m);

    for (int i=1;i<=n;i++) { tata[i]=i; sz[i]=1; rang[i]=0; }

    for (int i=1;i<=m;i++) scanf("%d %d",&t[i].x,&t[i].y);

    sort(t+1,t+m+1,cmp1);

    for (int i=1;i<=m;i++) unite(t[i].x,t[i].y);

    int nr=0;

    for (int i=1;i<=n;i++)
        if (!dad[root(i)]) { nr++; p[nr].x=i; p[nr].y=sz[root(i)]; dad[root(i)]=true; }

    sort(p+1,p+nr+1,cmp2); vector <int> sol; int curent=0;

    for (int i=1;i<=nr;i++) {
        curent=curent+p[i].y; sol.push_back(p[i].x);
        if (curent>n/2) break;
    }

    sort(sol.begin(),sol.end());

    printf("%d\n",sol.size());

    for (int i=0;i<(int)sol.size();i++) printf("%d ",sol[i]);

    return 0;
}