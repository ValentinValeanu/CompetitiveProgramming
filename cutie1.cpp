#include <stdio.h>
#include <cstring>
#define nmax 10010

using namespace std;

int tt,n,k,m,x;
int dpl[nmax],dpr[nmax],v[nmax];

int main()
{
    freopen("cutie1.in","r",stdin);
    freopen("cutie1.out","w",stdout);

    scanf("%d",&tt);

    for (int o=1;o<=tt;o++) {
        scanf("%d %d %d",&n,&k,&m);

        v[0]=v[1]=v[2]=0;
        memset(dpl,0,sizeof(dpl));
        memset(dpr,0,sizeof(dpr));

        for (int i=1;i<=k;i++) {
            scanf("%d",&x); dpl[x]=dpr[x]=x;
        }

        dpl[1]=1; dpr[n]=n;

        for (int i=2;i<=n;i++)
            if (dpl[i]==0) dpl[i]=dpl[i-1];

        for (int i=n-1;i>=1;i--)
            if (dpr[i]==0) dpr[i]=dpr[i+1];

        for (int i=1;i<=m;i++) { scanf("%d",&x); v[(x-dpl[x])%2+(dpr[x]-x)%2]++; }

        if (v[1]%2==1) printf("1"); else
            if (v[2]%2==1) printf("1"); else
               printf("0");

    }

    return 0;
}