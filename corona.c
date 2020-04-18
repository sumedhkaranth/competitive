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
    int flag=0, l=r1c(n,x);
    for(int i=0;i<l;i++)
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
    int i=0;
    while((a[i]!=y)&&(i<n))
    {
        i++;
    }
    return i;
}   
int find_last_post(int n, int a[n], int y)
{
    int i=find_first_post(n,a,y);
    while((a[i]==y)&&(i<n))
    {
        i++;
    }
    return i-1;
}
int give_post(int n, int a[n], int y)
{
    int i=0;
    while((a[i]!=y)&&(i<n))
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
int reduce(int s, int infec[s], int reduc[s])
{
    int size=0, c=0,co=0,l=0,counter=0;
    for(int i=0;i<s;i++)
    {
        if(is_equal(s,infec,infec[i])>1)
        {
            c+=is_equal(s,infec,infec[i]);
            co++;
        }
        else
            l++;
    }
    if(co>0)
        size=(c/(co*co))+l;
    else
        size=l;
    qsort(infec,s,sizeof(int),compare);
    int i=0;
    while(i<s)
    {
        if(is_equal(s,infec,infec[i])>1)
        {
            reduc[i]=infec[i];
            i=find_last_post(s,infec,infec[i])+1;
            counter++;
        }
        else
        {
            if(counter>0)
            {
                reduc[i-1]=infec[i];
                i++;
            }
            else if(counter==0)
            {
                reduc[i]=infec[i];
                i++;
            }   
        }
    }
    return size;
}
int infec_round2(int n, int a[n], int x, int infec2[n], int infec[r1c(n,x)])
{
    int flag=0,flag1=0, s=r1c(n,x),check=0;
    int i,size=0,j=0,si=0;
    initialize(n,infec2);
    int reduc[s];
    si=reduce(s,infec,reduc);
    for(i=0;i<si;i++)
    {  
        if(((is_equal(n,a,reduc[i]))>1))
        {
            int first=find_first_post(n,a,reduc[i]);
            int last=find_last_post(n,a,reduc[i]);
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
            check=is_equal(s,infec,infec[i]);
            for(j=0;j<((is_equal(n,a,infec[i]))-check);j++)
            {
                
                infec2[j+size]=a[first+j];
            }
            size=size+j;
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
        }
     
    }
    return size;
}
void display(int a, int b)
{
    printf("%d\n%d\n",a,b);
}
void find_infec(int n, int a[n], int x, int infec[r1c(n,x)], int infec2[n])
{
    int os=infec_round2(n,a,x,infec2,infec);
    int s=r1c(n,x),ti[os+s+1];
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
    int death=0;
    for(int i=0;i<os+s;i++)
    {
        if(ti[i]>60)
            death++;
    }
    display(os+s,death);
}
int main()
{
    int n,key=0;
    n=input();
    int a[n];
    input1(n,a);
    key=infected_post();
    int s=r1c(n,key);               
    int infec[s], infec2[n];
    infect_round1(n,a,key,infec);
    sort(n,a);
    find_infec(n,a, key, infec,infec2);
    return 0;
}
    
            
         
    
