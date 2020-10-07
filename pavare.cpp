#include <stdio.h>
     
using namespace std;
 
int n,m,x,y,nr,b;
int fi[160][160];
 
void putf1(int x,int y)
{
	b++; fi[x][y]=fi[x][y+1]=fi[x+1][y]=fi[x+2][y]=fi[x+2][y+1]=fi[x+3][y]=b;
	b++; fi[x][y+2]=fi[x][y+3]=fi[x+1][y+3]=fi[x+2][y+3]=fi[x+2][y+2]=fi[x+3][y+3]=b;
	b++; fi[x+1][y+1]=fi[x+1][y+2]=b;
	b++; fi[x+3][y+1]=fi[x+3][y+2]=b;
}
 
void putf2(int x,int y)
{
	b++; fi[x][y]=fi[x][y+1]=fi[x+1][y+1]=fi[x][y+2]=fi[x][y+3]=fi[x+1][y+3]=b;
	b++; fi[x+1][y]=fi[x+2][y]=fi[x+2][y+1]=fi[x+2][y+2]=fi[x+1][y+2]=fi[x+2][y+3]=b;
}
 
void putf3(int x,int y)
{
	b++; fi[x][y]=fi[x][y+1]=fi[x+1][y]=fi[x+2][y]=fi[x+2][y+1]=fi[x+3][y]=b;
	b++; fi[x][y+2]=fi[x+1][y+2]=fi[x+1][y+1]=fi[x+2][y+2]=fi[x+3][y+2]=fi[x+3][y+1]=b;
}
 
int main()
{
	freopen("pavare.in","r",stdin);
	freopen("pavare.out","w",stdout);
 
	scanf("%d %d",&n,&m); x=1; y=1; nr=1;
 
	while (nr<=n*m/12 && n%2==m%2 && n%2==0 && n%3!=0 && m%3!=0) {
		putf1(x,y); 
		if (y+4<=m) y=y+4; else
		   x=x+4,y=1;
		nr+=2;
	}
 
	while (nr<=n*m/12 && m%3==0 && n!=3) {
		putf3(x,y);
		if (y+3<=m) y=y+3; else
		   x=x+4,y=1;
		nr+=2;
	}
	
	while (nr<=n*m/12 && n%3==0 && m!=3) {
		putf2(x,y);
		if (y+4<=m) y=y+4; else
		   x=x+3,y=1;
		nr+=2;
	}
 
	if (m%2>0) {
 
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (fi[i][j]==0 && fi[i+1][j]==0) b++,fi[i][j]=fi[i+1][j]=b;
 
	} else {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (fi[i][j]==0 && fi[i][j+1]==0) b++,fi[i][j]=fi[i][j+1]=b;
	}
 
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) printf("%d ",fi[i][j]);
		printf("\n");
	}
 
	return 0;
}