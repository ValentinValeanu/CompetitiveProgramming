#include <stdio.h>
#include <stack>
#include <algorithm>
#define nmax 1010

using namespace std;

int n,m;
short int t[nmax][nmax],dp[nmax][nmax],dpl[nmax][nmax],dpr[nmax][nmax];

int main()
{
    freopen("matrice1.in","r",stdin);
    freopen("matrice1.out","w",stdout);

    scanf("%d %d",&n,&m);

    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&t[i][j]);

    for (int i=1;i<=n;i++) {
        dpl[i][1]=1; dpr[i][1]=1; dp[i][1]=1;
        for (int j=2;j<=m;j++) {
            if (t[i][j]>t[i][j-1]) dpl[i][j]=dpl[i][j-1]+1; else dpl[i][j]=1;
            if (t[i][j]<t[i][j-1]) dpr[i][j]=dpr[i][j-1]+1; else dpr[i][j]=1;
            dp[i][j]=max(max(dpl[i][j],dpr[i][j]),(short int)max(dpl[i][j-dpr[i][j]]+dpr[i][j],dpr[i][j-dpl[i][j]]+dpl[i][j]));
        }
    }

    int sol=0,x11,y11,x22,y22;

    for (int i=1;i<=m;i++) {

        stack <int> st; int j;

        for (j=1;j<=n;j++) {
            while (st.size()>0 && dp[st.top()][i]>dp[j][i]) {
                int top=st.top(); st.pop();
                if (st.size()==0) {
                    if (dp[top][i]*(j-1)>sol) x11=1,y11=i-dp[top][i]+1,x22=j-1,y22=i;
                    sol=max(sol,dp[top][i]*(j-1));
                } else {
                    if (dp[top][i]*(j-st.top()-1)>sol) x11=st.top()+1,y11=i-dp[top][i]+1,x22=j-1,y22=i;
                    sol=max(sol,dp[top][i]*(j-st.top()-1));
                }
            }
            st.push(j);
        }

        while (st.size()>0) {
            int top=st.top(); st.pop();
            if (st.size()==0) {
                if (dp[top][i]*(j-1)>sol) x11=1,y11=i-dp[top][i]+1,x22=j-1,y22=i;
                sol=max(sol,dp[top][i]*(j-1));
            } else {
                if (dp[top][i]*(j-st.top()-1)>sol) x11=st.top()+1,y11=i-dp[top][i]+1,x22=j-1,y22=i;
                sol=max(sol,dp[top][i]*(j-st.top()-1));
            }
        }
    }

    printf("%d %d %d %d",x11,y11,x22,y22);

    return 0;
}