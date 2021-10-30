# include <cstdio>
# include <iostream>
# include <cstring>
# include <vector>
# include <queue>
# include <math.h>
# include <cstdlib> // Header file needed to use srand and rand
# include <ctime> // Header file needed to use time
# include <fstream>
# define R register int
 
using namespace std;
ofstream outfile("info.txt");
int T,n,ans;
int a[16];
int origin[16];
int dp[55][55][55][55];
int dp_v[55][55][55][55];
int num,col,coun[5];
bool id;
struct ss_state
{
    vector<int>one;
    vector<int>two;
    vector<int>three;
    vector<int>four;
};
struct ss_state ss;
struct state{
    vector<int>start;
    vector<int>itv;
    vector<int>cnt;
    vector<int>number;
    vector<int>details;
    int a[16];
    int coun[5];
    int step;
    int value;
    int joker;
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
      outfile<<S.coun[i]<<" ";
    }
    outfile<<endl;
    outfile<<S.value<<"   "<<S.step<<endl;
    for(unsigned int i = 0; i <= S.start.size()-1;i++)
    {
      outfile<<S.start[i]<<" "<<S.itv[i]<<" "<<S.cnt[i]<<" "<<S.number[i]<<endl;
    }
}
vector<int>start;
vector<int>itv;
vector<int>cntx;
vector<int>number;
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
                start.push_back(i);
                itv.push_back(ind);
                cntx.push_back(cnt);
                number.push_back(k);
                dfs(x+1,value+(k+4));
                for (R j=1;j<=cnt;++j)
                    a[i+(j-1)*ind]+=k;
                start.pop_back();
                itv.pop_back();
                cntx.pop_back();
                number.pop_back();
                cnt++;
            }
        }
    }
    if(a[14] == 1 || a[14] == 0)
    {
    struct state S;
    S.coun[1]=S.coun[2]=S.coun[3]=S.coun[4]=0;
    for (int i=1;i<=14;++i)
    {
        S.coun[ a[i] ]++;
        S.a[i] = a[i];
    }
    S.joker = 0;
    S.step = x;
    S.value = value;
    S.score = 0.0;
    for(int i = 0;i<=cntx.size()-1;i++)
    {
        S.cnt.push_back(cntx[i]);
        S.itv.push_back(itv[i]);
        S.start.push_back(start[i]);
        S.number.push_back(number[i]);
    }
    v.push_back(S);
    }
    if(a[14] == 2)
    {
    struct state S;
    S.coun[1]=S.coun[2]=S.coun[3]=S.coun[4]=0;
    for (int i=1;i<=13;++i)
    {
        S.coun[ a[i] ]++;
        S.a[i] = a[i];
    }
    S.a[14] = a[14];
    S.coun[1]+=2;
    S.joker = 0;
    S.step = x;
    S.value = value;
    S.score = 0.0;
    for(int i = 0;i<=cntx.size()-1;i++)
    {
        S.cnt.push_back(cntx[i]);
        S.itv.push_back(itv[i]);
        S.start.push_back(start[i]);
        S.number.push_back(number[i]);
    }
    v.push_back(S);
    struct state Y;
    Y.coun[1]=Y.coun[2]=Y.coun[3]=Y.coun[4]=0;
    for (int i=1;i<=13;++i)
    {
        Y.coun[ a[i] ]++;
        Y.a[i] = a[i];
    }
    Y.a[14] = 0;
    Y.joker = 1;
    Y.step = x;
    Y.value = value;
    Y.score = 0.0;
    for(int i = 0;i<=cntx.size()-1;i++)
    {
        Y.cnt.push_back(cntx[i]);
        Y.itv.push_back(itv[i]);
        Y.start.push_back(start[i]);
        Y.number.push_back(number[i]);
    }
    v.push_back(Y);
    }
}
void search_simple_state(int h)
{  
   for(int index = 0; index<7;index++)
   {v[h].details.push_back(-1);}
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
                                 outfile<<"invalid"<<endl;
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
                                  v[h].details[0] =i;
                                  v[h].details[1] =j;
                                  v[h].details[2] =j1;
                                  v[h].details[3] =k;
                                  v[h].details[4] =k1;
                                  v[h].details[5] =k2;
                                  v[h].details[6] =k3;
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
{   start.push_back(-1);
    cntx.push_back(-1);
    itv.push_back(-1);
    number.push_back(-1);
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
        if(v[i].score>best_score)
        {
            answer = i;
            best_score = v[i].score;
        }
       
    }
}
void convert_ss()
{
    for(int i =1;i<=13;i++)
    {
        if(v[answer].a[i] == 1)
        {
            ss.one.push_back(i);
        }
        if(v[answer].a[i] == 2)
        {
            ss.two.push_back(i);
        }
        if(v[answer].a[i] == 3)
        {
            ss.three.push_back(i);
        }
        if(v[answer].a[i] == 4)
        {
            ss.four.push_back(i);
        }

    }
    if(v[answer].a[14] == 1)
    {
        ss.one.push_back(14);
    }
     if(v[answer].a[14] == 2)
    {
        ss.one.push_back(14);
        ss.one.push_back(14);
    }
    for(int i=0;i<=v[answer].details[0]-1;i++)
        {
            int x = ss.two[ss.two.size()-1];
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.two.pop_back();
        }
    for(int i=0;i<=v[answer].details[1]-1;i++)
        {
            int x = ss.three[ss.three.size()-1];
            ss.one.push_back(x);
            ss.two.push_back(x);
            ss.three.pop_back();
        }
    for(int i=0;i<=v[answer].details[2]-1;i++)
        {
            int x = ss.three[ss.three.size()-1];
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.three.pop_back();
        }
    for(int i=0;i<=v[answer].details[3]-1;i++)
        {
            int x = ss.four[ss.four.size()-1];
            ss.one.push_back(x);
            ss.three.push_back(x);
            ss.four.pop_back();
        }
    for(int i=0;i<=v[answer].details[4]-1;i++)
        {
            int x = ss.four[ss.four.size()-1];
            ss.two.push_back(x);
            ss.two.push_back(x);
            ss.four.pop_back();
        }
    for(int i=0;i<=v[answer].details[5]-1;i++)
        {
            int x = ss.four[ss.four.size()-1];
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.two.push_back(x);
            ss.four.pop_back();
        }
    for(int i=0;i<=v[answer].details[6]-1;i++)
        {
            int x = ss.four[ss.four.size()-1];
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.one.push_back(x);
            ss.four.pop_back();
        }
}
void play()
{   struct state S = v[answer];
    if(S.joker == 1)
    {  
        outfile<<"14 14"<<endl;
    }
    for(unsigned int i = 1; i <= S.start.size()-1;i++)
    {
      //outfile<<"X"<<endl;
      for(int j = 0;j<=S.cnt[i]-1;j++)
      {
          for(int k = 0;k<=S.number[i]-1;k++)
          {
              outfile<<S.start[i]+j*S.itv[i]<<" ";
          }
      }
      outfile<<endl;
    }
    while(ss.four.size()>0 && ss.one.size()>=2)
    {  // outfile<<"Y"<<endl;
        outfile<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.one[ss.one.size()-1]<<" "<<ss.one[ss.one.size()-2]<<endl;
        ss.four.pop_back();
        ss.one.pop_back();
        ss.one.pop_back();
    }
    while(ss.four.size()>0 && ss.two.size()>=2)
    {   // outfile<<"Z"<<endl; 
        outfile<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.two[ss.two.size()-1]<<" "<<ss.two[ss.two.size()-1]<<" "<<ss.two[ss.two.size()-2]<<" "<<ss.two[ss.two.size()-2]<<endl;
        ss.four.pop_back();
        ss.two.pop_back();
        ss.two.pop_back();
    }
    while(ss.four.size()>0)
    {   
        outfile<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<" "<<ss.four[ss.four.size()-1]<<endl;
        ss.four.pop_back();
    }
    while(ss.three.size()>0 && ss.one.size()>=1)
    {   
        outfile<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<" "<<ss.one[ss.one.size()-1]<<endl;
        ss.three.pop_back();
        ss.one.pop_back();
    }
    while(ss.three.size()>0 && ss.two.size()>=1)
    {  
        outfile<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<" "<<ss.two[ss.two.size()-1]<<" "<<ss.two[ss.two.size()-1]<<endl;
        ss.three.pop_back();
        ss.two.pop_back();
    }
    while(ss.three.size()>0)
    {  
        outfile<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<" "<<ss.three[ss.three.size()-1]<<endl;
        ss.three.pop_back();
    }
    while(ss.two.size()>0)
    {  
        outfile<<ss.two[ss.two.size()-1]<<" "<<ss.two[ss.two.size()-1]<<endl;
        ss.two.pop_back();
    }
    while(ss.one.size()>0)
    {  
        outfile<<ss.one[ss.one.size()-1]<<endl;
        ss.one.pop_back();
    }

}
char r[100];
int main(int argc, char** argv)
{   
    strcpy(r,argv[1]);
    n = atoi(r);
    init();
    unsigned int seed = time(0);
    srand(seed);
    memset(a,0,sizeof(a));
    memset(origin,0,sizeof(origin));
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
        outfile << a[i]<<" ";
    }
    outfile << endl;
    dfs(0,0);
    search();
    convert_ss();
    play();
    outfile<<best_score<<endl;
    
    return 0;
}
