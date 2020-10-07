#include <stdio.h>
#include <vector>
#include <algorithm>
#define nmax 16010

using namespace std;

struct point { int x,y; };

int n,m,x11,y11,x22,y22,sol;
point t[nmax];
vector <point> arb[3*nmax];

bool cmp(const point &a,const point &b)
{
    if (a.x==b.x) return (a.y<b.y); else
       return (a.x<b.x);
}


int binary_searchx1(int st,int dr,int val)
{
    int sol=-1;

    while (st<=dr) {
        int m=(st+dr)/2;

        if (t[m].x>=val) { sol=m; dr=m-1; } else
            st=m+1;

    }

    return sol;
}

int binary_searchx2(int st,int dr,int val)
{
    int sol=-1;

    while (st<=dr) {
        int m=(st+dr)/2;

        if (t[m].x<=val) { sol=m; st=m+1; } else
            dr=m-1;

    }

    return sol;
}

int binary_searchy1(int st,int dr,int val,vector <point> &t)
{
    int sol=-1;

    while (st<=dr) {
        int m=(st+dr)/2;

        if (t[m-1].y>=val) { sol=m; dr=m-1; } else
            st=m+1;
    }

    return sol;
}

int binary_searchy2(int st,int dr,int val,vector <point> &t)
{
    int sol=-1;

    while (st<=dr) {
        int m=(st+dr)/2;

        if (t[m-1].y<=val) { sol=m; st=m+1; } else
            dr=m-1;
    }

    return sol;
}

void query(int nod,int st,int dr,int l,int r,int y1,int y2)
{
    if (st>=l && dr<=r) {
        int ly=binary_searchy1(1,arb[nod].size(),y1,arb[nod]);
        int ry=binary_searchy2(1,arb[nod].size(),y2,arb[nod]);

        if (ly<=ry && ly!=-1) sol=sol+(ry-ly+1);

        return;

    } else
    {
        int m=(st+dr)/2;
        if (l<=m) query(nod*2,st,m,l,r,y1,y2);
        if (r>m) query(nod*2+1,m+1,dr,l,r,y1,y2);
    }
}

void build(int nod,int st,int dr)
{
    if (st==dr) {
        arb[nod].resize(1);
        arb[nod][0]=t[st];
        return;
    } else
    {
        int m=(st+dr)/2;
        build(nod*2,st,m);
        build(nod*2+1,m+1,dr);
        arb[nod].resize(dr-st+1);

        int i=0,j=0,nr=-1;

        while (i<m-st+1 && j<dr-m) {

            if (arb[nod*2][i].y<arb[nod*2+1][j].y) nr++,arb[nod][nr]=arb[nod*2][i],i++; else
                nr++,arb[nod][nr]=arb[nod*2+1][j],j++;

        }

        while (i<m-st+1) nr++,arb[nod][nr]=arb[nod*2][i],i++;
        while (j<dr-m) nr++,arb[nod][nr]=arb[nod*2+1][j],j++;

    }
}

int main()
{
    freopen("zoo.in","r",stdin);
    freopen("zoo.out","w",stdout);

    scanf("%d",&n);

    for (int i=1;i<=n;i++) scanf("%d %d",&t[i].x,&t[i].y);

    sort(t+1,t+n+1,cmp);

    build(1,1,n);

    scanf("%d",&m);

    for (int i=1;i<=m;i++) {
        scanf("%d %d %d %d",&x11,&y11,&x22,&y22); sol=0;
        int l=binary_searchx1(1,n,x11);
        int r=binary_searchx2(1,n,x22);
        if (l<=r && l!=-1) { query(1,1,n,l,r,y11,y22); printf("%d\n",sol); } else
            printf("0\n");
    }

    return 0;
}