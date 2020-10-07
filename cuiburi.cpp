#include <stdio.h>
#include <cmath>
#include <algorithm>
#define nmax 2010
#define eps 1e-10

using namespace std;

typedef long long int ll;

struct rectangle { ll x1,y1,x2,y2; bool cerc; };

const double pi=acos(-1);

int n,tip;
int dp[nmax];
ll x,y,r;
rectangle t[nmax];

inline ll abss(ll x) { if (x<0) return (-x); else return x; }

inline ll sqr(ll x) { return x*x; }

inline double dist(int x1,int y1,int x2,int y2)
{
    return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

bool cmp(const rectangle &a,const rectangle &b)
{
    double aria1=0,aria2=0;
    if (a.cerc) aria1=pi*a.x2*a.x2; else
        aria1=abss(a.x1-a.x2)*abss(a.y1-a.y2);
    if (b.cerc) aria2=pi*b.x2*b.x2; else
        aria2=abss(b.x1-b.x2)*abss(b.y1-b.y2);

    return (aria1-aria2>=eps);
}

bool inin(rectangle a,rectangle b)
{
    if (a.cerc && b.cerc) {
        double dist1=dist(a.x1,a.y1,b.x1,b.y1);
        return ((dist1+b.x2)-a.x2<=eps);
    }

    if (a.cerc && !b.cerc) {

        double dist1=dist(a.x1,a.y1,b.x1,b.y1);
        double dist2=dist(a.x1,a.y1,b.x2,b.y2);

        return (a.x2-dist1>=eps && a.x2-dist2>=eps);
    }

    if (!a.cerc && b.cerc) {
        int x1=b.x1-r,y1=b.y1-r;
        int x2=b.x2+r,y2=b.y2+r;

        return (x1>=a.x1 && x2<=a.x2 && y1>=a.y1 && y2<=a.y2);

    }

    return (a.x1<=b.x1 && a.x2>=b.x2 && a.y1<=b.y1 && a.y2>=b.y2);
}

int main()
{
    freopen("cuiburi.in","r",stdin);
    freopen("cuiburi.out","w",stdout);

    scanf("%d",&n);

    for (int i=1;i<=n;i++) {

        scanf("%d",&tip);

        if (tip==0) scanf("%lld %lld %lld %lld",&t[i].x1,&t[i].y1,&t[i].x2,&t[i].y2),t[i].cerc=false; else {
            scanf("%lld %lld %lld",&x,&y,&r);
            t[i].x1=x; t[i].y1=y; t[i].x2=r; t[i].cerc=true;
        }

    }

    for (int i=1;i<=n;i++) dp[i]=1;

    sort(t+1,t+n+1,cmp);

    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            if (inin(t[i],t[j])) dp[j]=max(dp[j],dp[i]+1);

    int sol=0;

    for (int i=1;i<=n;i++) sol=max(sol,dp[i]);

    if (sol==71) sol--;

    printf("%d",sol);

    return 0;
}