#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int input()
{
    int q;
    scanf("%d",&q);
    return q;
}
void input1(int n, long int a[n])
{
    for(int i=0;i<n;i++)
    {
        scanf("%ld",&a[i]);
    }
}
int simplify(long int x, long int simp[x])
{
    int i,cv=0;
    for(i=1;i<=x;i++)
    {
        if(((i-2)%3)==0)
        {
            simp[cv]=(i-2)/3;
            cv++;
        }
    }
    return cv;
}
int cardano(long int x, long int simp[(x)])
{
    int i,j,k,os,c=0;
    os=simplify(x,simp);
    simp[os];
    for(k=0;k<os;k++)                      
    {
        for(i=1;i<=x;i++)
        {
            for(j=i;j<=x;j++)
            {
                if((((simp[k])*3)+2+j+i)<=x)
                {
                    if((((pow((simp[k]+1),2))*(8*simp[k]+5))==(j*j*i))||((pow((simp[k]+1),2))*(8*simp[k]+5))==(i*i*j))
                    {
                        c++;
                    }
                }
                else
                {
                    break;
                }
            }
            if(simp[k]*3+2+i>x)
            {
                break;
            }
        }
        if(simp[k]*3+3>x)
            break;
    }
    return c;
}
void solve_and_display(int n, long int a[n])
{
    int i;
    for(i=0;i<n;i++)
    {
        int os=0;
        long int simp[a[i]];
        os=cardano(a[i],simp);
        printf("%d\n",os);
    }
}
int main()
{
    int n;
    n=input();
    long int a[n];
    input1(n,a);
    solve_and_display(n,a);
    return 0;
}           
