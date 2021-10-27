# include <cstdio>
# include <iostream>
# include <cstring>
# define R register int
 
using namespace std;

int T,n,ans;
int a[16];
int dp[25][25][25][25][3];
int num,col,coun[5];
bool id;

void dfs (int x)
{
    if(x>=ans) return;    
    bool f;
    int cnt;
    for(R ind = 1; ind<=2;++ind)
    {
    for (R k=1;k<=3;++k)
        for (R i=1;i<=12;++i)
        {
            f=true;
            if(k==1) cnt=5;
            if(k==2) cnt=3;
            if(k==3) cnt=2;
            while (f&&i+(cnt-1)*ind<=12)
            {
                for (R j=1;j<=cnt;++j)
                    if(a[i+(j-1)*ind]<k) 
                    {
                        f=false;
                        break;
                    }
                if(f==false) continue;
                for (R j=1;j<=cnt;++j)
                    a[i+(j-1)*ind]-=k;
                dfs(x+1);
                for (R j=1;j<=cnt;++j)
                    a[i+(j-1)*ind]+=k;
                cnt++;
            }
        }
    }
    coun[1]=coun[2]=coun[3]=coun[4]=coun[5]=0;
    for (int i=1;i<=13;++i)
        coun[ a[i] ]++;
    coun[5]=a[14];
    ans=min(ans,x+dp[ coun[1] ][ coun[2] ][ coun[3] ][ coun[4] ][ coun[5] ]);
}

void init ()
{
    int x=100;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0][0][0]=0;
    
    for (int z=0;z<=n;++z)
        for (int k=0;k<=n;++k)
            for (int i=0;i<=n;++i)
                for (int j=0;j<=n;++j)        
                    for (int l=0;l<=2;++l)
                    {
                        x=100;
                        if(i>0) x=min(x,dp[i-1][j][k][z][l]+1);
                        if(j>0) x=min(x,dp[i][j-1][k][z][l]+1);
                        if(k>0) x=min(x,dp[i][j][k-1][z][l]+1);
                        if(z>0) x=min(x,dp[i][j][k][z-1][l]+1);
                        if(l>0) x=min(x,dp[i][j][k][z][l-1]+1);
                        if(l>1) x=min(x,dp[i][j][k][z][l-2]+1);
                        //单权值
                        if(i>0&&k>0) x=min(x,dp[i-1][j][k-1][z][l]+1);
                        if(l>0&&k>0) x=min(x,dp[i][j][k-1][z][l-1]+1); 
                        //三带一 
                        if(j>0&&k>0) x=min(x,dp[i][j-1][k-1][z][l]+1);
                        //三带二                        
                        
                        if(i>1&&z>0) x=min(x,dp[i-2][j][k][z-1][l]+1);
                        if(i>0&&z>0&&l>0) x=min(x,dp[i-1][j][k][z-1][l-1]+1);
                        if(z>0&&l>1) x=min(x,dp[i][j][k][z-1][l-2]+1);
                        if(j>0&&z>0) x=min(x,dp[i][j-1][k][z-1][l]+1);
                        if(j>1&&z>0) x=min(x,dp[i][j-2][k][z-1][l]+1);
                        if(z>1) x=min(x,dp[i][j][k][z-2][l]+1);
                        //四带二
                        if(z>0) x=min(x,dp[i+1][j][k+1][z-1][l]);
                        if(k>0) x=min(x,dp[i+1][j+1][k-1][z][l]);
                        dp[i][j][k][z][l]=min(dp[i][j][k][z][l],x);
                    }
}

int main()
{
    scanf("%d",&n);
    init();
    
    memset(a,0,sizeof(a));
    ans=n;
    for (int i=1;i<=n;++i)
        {
            scanf("%d",&num);
            if(num==0)
            {
                a[14]++;
                continue;
            }
            if(num>=3) a[num-2]++;
            if(num==1) a[12]++;
            if(num==2) a[13]++;
        }
    dfs(0);
    printf("%d\n",ans);
    
    return 0;
}