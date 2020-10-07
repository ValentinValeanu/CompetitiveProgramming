#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long int ll;

int n;
int a[20],b[20];
ll x,y,dp[2][30][20];

ll memo(int t[20])
{
	memset(dp,0,sizeof(dp)); dp[1][0][0]=1;

	for (int i=1;i<=n;i++) {
		for (int j=1;j<=9;j++)
		    for (int k=0;k<=n+8-j;k++) {
		    	dp[0][k+j][i]=dp[0][k+j][i]+dp[0][k][i-1];
		    	if (j<t[i]) dp[0][k+j][i]=dp[0][k+j][i]+dp[1][k][i-1];
		    	if (j==t[i]) dp[1][k+j][i]=dp[1][k+j][i]+dp[1][k][i-1];
		    }
	}

	return dp[0][n+8][n]+dp[1][n+8][n];
}

int main()
{
	freopen("cifreco.in","r",stdin);
	freopen("cifreco.out","w",stdout);

	scanf("%d",&n);

	scanf("%lld",&x);
	scanf("%lld",&y);

	int l=0; x--;

	while (x>0) { l++; a[l]=x%10; x=x/10; }

	l=0; x=y;

	while (x>0) { l++; b[l]=x%10; x=x/10; }

	reverse(a+1,a+n+1);
	reverse(b+1,b+n+1);

	printf("%lld",memo(b)-memo(a));

	return 0;
}
