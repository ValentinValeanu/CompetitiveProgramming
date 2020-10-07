#include <stdio.h>
#include <queue>
#define nmax 1000010

using namespace std;

int n;
int t[nmax],arb[4*nmax];
unsigned short int v[4*nmax];

inline void lazyupdate(int nod,int st,int dr)
{
    if (v[nod]==0) return;

    arb[nod]=arb[nod]-v[nod];

    if (st<dr) v[nod*2]+=v[nod],v[nod*2+1]+=v[nod];

    v[nod]=0;
}

void build(int nod,int st,int dr)
{
    if (st==dr) arb[nod]=t[st]+st-1; else
    {
        int m=(st+dr)/2;
        build(nod*2,st,m);
        build(nod*2+1,m+1,dr);

        arb[nod]=max(arb[nod*2],arb[nod*2+1]);
    }
}

void update(int nod,int st,int dr,int pos,int val)
{
    lazyupdate(nod,st,dr);
    if (st==dr) { arb[nod]=t[st]+val; return; } else
    {
        int m=(st+dr)/2;

        if (pos<=m) update(nod*2,st,m,pos,val); else
            update(nod*2+1,m+1,dr,pos,val);

        lazyupdate(nod*2,st,m); lazyupdate(nod*2+1,m+1,dr);

        arb[nod]=max(arb[nod*2],arb[nod*2+1]);
    }
}

int main()
{
    freopen("munte2.in","r",stdin);
    freopen("munte2.out","w",stdout);

    scanf("%d",&n);

    for (int i=1;i<=n;i++) scanf("%d",&t[i]);

    build(1,1,n); int sol=arb[1],pos=1;

    for (int i=2;i<=n;i++) {
        v[1]=v[1]+1;
        update(1,1,n,i-1,n-1);
        if (arb[1]<sol) sol=arb[1],pos=i;
    }

    printf("%d %d",pos,sol);

    return 0;
}