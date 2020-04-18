#include<stdio.h>
#include<stdlib.h>
int input()
{
    int q;
    scanf("%d",&q);
    return q;
}
void input1(int n, int a[n] )
{
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
int infected_post()
{
    int x;
    scanf("%d",&x);
    return x;
}
int r1c(int n,int x)
{
    int index=x-1,s=1;
    if(index!=0)
    {
        s++;
    }
    if(index!=(n-1))
    {
        s++;
    }
    return s;
}
void infect_round1(int n, int a[n], int x, int infec[r1c(n,x)])
{
    int index=x-1,s=r1c(n,x),i=1;
    infec[0]=a[index];
    while(i<s)
    {
        if(index!=0)
        {
            infec[i]=a[index-1];
            i++;
        }
        if(index!=(n-1))
        {
            infec[i]=a[index+1];
            i++;
        }
    }
}
int compare(const void *p, const void *q)
{
    const int *pc=(const int *)p;
    const int *pq=(const int *)q;
    return *pc-*pq;
}
void sort(int n, int a[n])
{
    qsort(a,n,sizeof(int),compare);
}
int is_equal(int n, int a[n], int y)
{
    int i=0,flag=0;
   for(i=0;i<n;i++)
   {
        if(a[i]==y)
            flag++;
   }
   return flag;
}
int is_infec(int n, int x,int r, int infec[r1c(n,x)])
{
    int flag=0;
    for(int i=0;i<3;i++)
    {
        if(r==infec[i])
        {
            flag=1;
        }
        
    }
    return flag;
}            
int find_first_post(int n, int a[n], int y)
{
    int i=0,first=0;
    while((a[i]!=y)&&(i<n))
    {
        first++;
        i++;
    }
    return first;
}   
int find_last_post(int n, int a[n], int y)
{
    int i=find_first_post(n,a,y),last=i;
    while((a[i]==y)&&(i<n))
    {
        last++;
        i++;
    }
    return last-1;
}
int give_post(int n, int a[n], int y)
{
    int i=0,post=0;
    while(a[i]!=y)
    {
        i++;
    }
    return i;
}
void initialize(int n,int infec2[n])
{
    for(int i=0;i<n;i++)
    {
        infec2[i]=0;
    }
}
int flagger(int a, int b)
{
    int flag=0;
    if(a==b)
    {
        flag=1;
    }
    return flag;
}   
int infec_round2(int n, int a[n], int x, int infec2[n], int infec[r1c(n,x)])
{
    int flag=0,flag1=0, s=r1c(n,x);
    int i,size=0,j=0,c=0,ic=0;
    initialize(n,infec2);
    printf("\n");
    for(i=0;i<s;i++)
    {
        if(i==0)
        {
            flag=0;
            flag1=flagger(infec[0],infec[1]);
        }
         else if((i!=(s-1))&&(i!=0))
         {
            if(flag1==1)
            {
                flag=1;
            }
            else
                flag=flagger(infec[i],infec[i+1]);
         }
           
        else
            flag=flagger(infec[i],infec[0]);
            
            if(flag==0)
            {
                if(((is_equal(n,a,infec[i]))>1))
                {
                    int first=find_first_post(n,a,infec[i]);
                    int last=find_last_post(n,a,infec[i]);
                    if((is_infec(n,x,a[first-1],infec)==0)&&(first!=0)&&(is_infec(n,x,a[first-1],infec2)==0))
                    {
                        infec2[size]=a[first-1];
                        size++;
                    }
                    if((is_infec(n,x,a[last+1],infec)==0)&&(last<(n-1))&&(is_infec(n,x,a[last+1],infec2)==0))
                    {
                        infec2[size]=a[last+1];
                        size++;
                    }
                    if(((is_equal(n,infec,infec[i]))!=(is_equal(n,a,infec[i]))))
                    {
                        int con=is_equal(n,infec,infec[i]);
                        for(j=0;j<=(last-first-con+1);j++)
                        {
                            
                            infec2[j+size]=a[first+j];
                        }
                        size=size+j-1;
                    }
                }
                else
                {
                    int pos=give_post(n,a,infec[i]);
                    if((pos!=0)&&(is_infec(n,x,a[pos-1],infec)==0)&&(is_infec(n,x,a[pos-1],infec2)==0))
                    {
                        infec2[size]=a[pos-1];
                        size++;
                    }
                    if((is_infec(n,x,a[pos+1],infec)==0)&&(pos!=n-1)&&(is_infec(n,x,a[pos+1],infec2)==0))
                    {
                        infec2[size]=a[pos+1];
                        size++;
                    }
                    if(i==0)
                        flag=1;
                }
                
            } 
        }
    return size;
}

void find_infec(int n, int a[n], int x, int infec[r1c(n,x)], int infec2[n])
{
    int os=infec_round2(n,a,x,infec2,infec);
    infec2[os];
    int s=r1c(n,x),ti[os+s];
    int i=0,j=0;
    while(i<s)
    {
        ti[j]=infec[i];
        i++;
        j++;
    }
    i=0;
    while(i<os)
    {
        ti[j]=infec2[i];
        i++;
        j++;
    }
    int inf=os+s,death=0;
    for(int i=0;i<os+s;i++)
    {
        if(ti[i]>=60)
            death++;
    }
    printf("%d\n",os+s);
    printf("%d\n",death);
}
int main()
{
    int n,key=0;
    n=input();
    int a[n];
    input1(n,a);
    key=infected_post();
    int infec[3], infec2[n];
    infect_round1(n,a,key,infec);
    sort(n,a);
    find_infec(n,a, key, infec,infec2);
    return 0;
}
    
            
         
    
