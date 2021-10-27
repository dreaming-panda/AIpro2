#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
const int INF = 10000000;
struct state
{
    int step;
    int value;
    double score;
};
struct state s[30][30][30][30];
void opr()
{
   for(int i = 0; i<=30;i++)
   {
       for(int j = 0; j<=30; j++)
       {
           s[i][j][0][0].step = i+j;
           s[i][j][0][0].value = 0;
           if(i+j == 1)
           {
               s[i][j][0][0].score = INF;
           }
           else
           {
           s[i][j][0][0].score = 0;
           }
       }
   }
   for(int k = 1 ;k<=30;k++)
   {
      for(int i = 0; i<=30;i++)
   {
       for(int j = 0; j<=30; j++)
       {
           if(k >= i+j)
           {
               s[i][j][k][0].step = k;
               s[i][j][k][0].value = 3*k;
               if(k == 1)
               {
                   s[i][j][k][0].score = INF;
               }
               else
               {
                s[i][j][k][0].score = log2(3*k)/log2(k);
               }
           }
           else
           {
               s[i][j][k][0].step = i+j;
               s[i][j][k][0].value = 3*k;
               if(i+j == 1)
               {
                   s[i][j][k][0].score = INF;
               }
               else
               {
                s[i][j][k][0].score = log2(3*k)/log2(i+j);
               }
           }
       }
   }
   }
   for(int l = 1; l<=14;l++)
   {
   for(int k = 0 ;k<=30;k++)
   {
      for(int i = 0; i<=30;i++)
   {
       for(int j = 0; j<=30; j++)
       {
           if(i>=2)
           {
               s[i][j][k][l].step = s[i-2][j][k][l-1].step+1;
               s[i][j][k][l].value = s[i-2][j][k][l-1].value+1;
           }
           else if(j>=2)
           {
               
           }
       }
   }
   }
   }
}
