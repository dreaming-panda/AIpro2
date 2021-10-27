# include <cstdio>
# include <iostream>
# include <cstring>
# include <vector>
# include <queue>
# include <math.h>
# include <cstdlib> // Header file needed to use srand and rand
# include <ctime> // Header file needed to use time
# define R register int
 
using namespace std;

int T,n,ans;
int a[16];
int dp[55][55][55][55];
int dp_v[55][55][55][55];
int num,col,coun[5];
bool id;
struct state{
    int coun[5];
    int step;
    int value;
    double score;
    
};
struct simple_state
{
    int coun[5];
    int step;
    int value;
    double score;
};
double best_score = 0.0;
vector<state>v;
void printS(state S)
{
    for(int i = 1;i<=4;i++)
    {
      cout<<S.coun[i]<<" ";
    }
    cout<<endl;
    cout<<S.value<<"   "<<S.step<<endl;
}
void dfs (int x,int value)
{    
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
                dfs(x+1,value+(k+4));
                for (R j=1;j<=cnt;++j)
                    a[i+(j-1)*ind]+=k;
                cnt++;
            }
        }
    }
    struct state S;
    S.coun[1]=S.coun[2]=S.coun[3]=S.coun[4]=0;
    for (int i=1;i<=14;++i)
        S.coun[ a[i] ]++;
    S.step = x;
    S.value = value;
    S.score = 0.0;
    v.push_back(S);
}
void search_simple_state(int h)
{  
   int temp_step = 0;
   int temp_value = 0;
   double temp_score = 0.0;
   for(int i = 0; i<=v[h].coun[2];i++) // 2 = 1+1
   {
       for(int j = 0;j<=v[h].coun[3];j++)// 3 = 1+2
       {
           for(int j1=0;j1<=v[h].coun[3]-j;j1++)// 3 = 1+1+1
           {
               for(int k = 0; k<=v[h].coun[4];k++)// 4 = 1+3
               {
                   for(int k1 = 0; k1<=v[h].coun[4]-k;k1++)// 4 = 2+2
                   {
                       for(int k2 = 0;k2<=v[h].coun[4]-k1-k;k2++)// 4 = 1+1+2
                       {
                           for(int k3=0;k3<=v[h].coun[4]-k1-k2-k;k3++)// 4 = 1+1+1+1
                           {
                              /*
                              1:coun[1]+2i+j+3j1+k+2k2+4k3
                              2:coun[2]-i+j+2k1+k2
                              3:coun[3]-j-j1+k
                              4:coun[4]-k-k1-k2-k3
                              */
                             int a1 = v[h].coun[1]+2*i+j+3*j1+k+2*k2+4*k3;
                             int a2 = v[h].coun[2] - i+j+2*k1+k2;
                             int a3 = v[h].coun[3]-j-j1+k;
                             int a4 = v[h].coun[4]-k-k1-k2-k3;
                             if(a1<0||a2<0||a3<0||a4<0||a1>54||a2>54||a3>54||a4>54)
                             {
                                 cout<<"invalid"<<endl;
                             }
                             int tt_step = dp[a1][a2][a3][a4]+v[h].step;
                             int tt_value = dp_v[a1][a2][a3][a4]+v[h].value;
                             double tt_score = 0.0;
                             if (tt_step == 1)
                             {
                                 tt_score = 20000;
                             }
                             else
                             {
                                 tt_score = log2(1.0*tt_value)/log2(1.0*tt_step);
                             }
                             if(tt_score > temp_score)
                             {
                                 temp_score = tt_score;
                                 temp_step = tt_step;
                                 temp_value = tt_value;
                                                              }
                           }
                       }
                       
                   }
               }
           }
       }
   }
   v[h].step = temp_step;
   v[h].value = temp_value;
   v[h].score = temp_score;
   //cout <<"scoress:   "<<v[h].score<<endl;
}
void init ()
{
    for(int i=0;i<=54;i++)
    {
        for(int j=0;j<=54;j++)
        {
            for(int k = 0;k<=54;k++)
            {
                for(int m = 0; m<=54;m++)
                {
                    if(m==0&&k==0)
                    {
                        dp[i][j][k][m] = i+j;
                        dp_v[i][j][k][m] = 0;
                    }
                    else
                    {
                        if(m == 0)
                        {
                           if(i+j>=k)
                           {
                               dp[i][j][k][m] = i+j;
                               dp_v[i][j][k][m] = 3*k;
                           } 
                           else
                           {
                               dp[i][j][k][m] = k;
                               dp_v[i][j][k][m] = 3*k;
                           }
                        }
                        else
                        {
                            if(i>=2)
                            {
                                dp[i][j][k][m] = dp[i-2][j][k][m-1]+1;
                                dp_v[i][j][k][m] = dp_v[i-2][j][k][m-1]+4;
                            }
                            else
                            {
                                if(j>=2)
                                {
                                     dp[i][j][k][m] = dp[i][j-2][k][m-1]+1;
                                     dp_v[i][j][k][m] = dp_v[i][j-2][k][m-1]+4;
                                }
                                else
                                {
                                    dp[i][j][k][m] = dp[i][j][k][0]+m;
                                    dp_v[i][j][k][m] = dp_v[i][j][k][0]+3*m;
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    
}
int answer = -1;
void search()
{
    for(unsigned int i = 0 ;i<=v.size()-1;i++)
    {
        search_simple_state(i);
        best_score = max(best_score,v[i].score);
        answer = i;
    }
}
int main()
{
    scanf("%d",&n);
    init();
    unsigned int seed = time(0);
    srand(seed);
    memset(a,0,sizeof(a));
    ans=n;
    for (int i=1;i<=n;++i)
        {
 Start:      num = rand()%14;
            if(num==0)
            {
                if(a[14]<2)
                {
                a[14]++;
                continue;
                }
                else
                {
                   goto Start;
                }
            }
            if(num>=3) 
            {  if(a[num-2]<4)
               {
                a[num-2]++;
               }
               else
               {
                   goto Start;
               }
            }
            if(num==1) 
            {  if(a[12]<4)
              {
                a[12]++;
              }
              else
              {
                  goto Start;
              }
            }
            if(num==2)
            { if(a[13]<4)
             {
                a[13]++;
             }
             else
             {
                 goto Start;
             }
            }
        }
    for(int i = 1;i<=14;i++)
    {
        cout << a[i]<<" ";
    }
    cout << endl;
    dfs(0,0);
    search();
    cout<<best_score<<endl;
    
    return 0;
}