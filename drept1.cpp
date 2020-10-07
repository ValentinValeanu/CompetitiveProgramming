#include <stdio.h>
#define nmax 2000100

using namespace std;

struct date { int x,y; };
typedef long long int ll;

int m,n,a,b;
int mindeq[nmax],maxdeq[nmax];
date t[nmax]; ll sol=0;

ll test(int x,int y)
{
    int pr1=1,pr2=1,ul1=0,ul2=0; ll sol=0;

    for (int i=1;i<=n;i++) {
        while (pr1<=ul1 && t[maxdeq[ul1]].x<=t[i].x) ul1--;
        while (pr2<=ul2 && t[mindeq[ul2]].y>=t[i].y) ul2--;
        ul1++; maxdeq[ul1]=i;
        ul2++; mindeq[ul2]=i;
        if (i-maxdeq[pr1]==x) pr1++;
        if (i-mindeq[pr2]==x) pr2++;
        if (i>=x) {
            if (t[mindeq[pr2]].y-t[maxdeq[pr1]].x+1>=y) sol=sol+((t[mindeq[pr2]].y-t[maxdeq[pr1]].x+1)-y+1);
        }
    }

    return sol;
}

int main()
{
    freopen("drept1.in","r",stdin);
    freopen("drept1.out","w",stdout);

    scanf("%d %d %d %d",&m,&n,&a,&b);

    for (int i=1;i<=n;i++) scanf("%d %d",&t[i].x,&t[i].y),t[i].y=t[i].x+t[i].y-1;

    sol=test(a,b);

    if (a!=b) sol=sol+test(b,a);

    printf("%lld",sol);

    return 0;
}