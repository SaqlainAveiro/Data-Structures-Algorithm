#include<bits/stdc++.h>

using namespace std;

typedef long long int lli ;

lli i,j,k,l,m,n,t,a,b,c,d,x,y,sum=0,total=0;

void Couting_Sort(lli ar[])
{
    lli maxi=0;

    maxi=ar[0];

    for(i=1 ; i<t ; i++)
    {
        if(ar[i]>maxi)
        {
            maxi=ar[i];
        }
    }

    lli br[maxi+1]={0},item=0,num=0;

    for(i=0 ; i<t ; i++)
    {
        item=ar[i];

        for(j=0 ; j<t ; j++)
        {
            if(ar[j]==item)
            {
                num++;
            }
        }
        br[item]=num;
        num=0;
    }

    sum=0;

    for(i=0 ; i<=maxi ; i++)
    {
        sum += br[i];

        br[i]=sum;
    }

    lli cr[t+1]={0};

    for(i=0 ; i<t ; i++)
    {
        cr[ br[ ar[i] ] ] = ar[i];                              //if ascending order

        //cr[ abs(br[ ar[i] ] - (sum+1))] = ar[i];    //if descending order

        br[ar[i]]--;
    }

    for(i=0 ; i<t ; i++)
    {
        ar[i]=cr[i+1];
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    freopen("Input.txt","r",stdin);

    cin>>t;

    lli ar[t]={0};

    for(i=0 ; i<t ; i++)
    {
        cin>>ar[i];
    }

    Couting_Sort(ar);

    cout<<"After using Counting Sort , the Array : \n\n";

    for(i=0 ; i<t ; i++)
    {
        cout<<ar[i]<<" ";
    }

    cout<<"\n\n";
}
