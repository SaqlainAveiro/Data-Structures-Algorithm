#include<bits/stdc++.h>

using namespace std;

typedef long long int lli ;

lli i,j,k,l,m,n,a,b,c,d,x,y,sum=0,total=0;

void Bucket_Sort(double ar[],lli t)
{
    vector<double>br[t];

    for(i=0 ; i<t ; i++)
    {
        x=t*ar[i];
        br[x].push_back(ar[i]);
    }
    for(i=0 ; i<t ; i++)
    {
        sort(br[i].begin(),br[i].end());
    }

    k=0;

    for(i=0 ; i<t ; i++)
    {
        for(j=0 ; j<br[i].size() ; j++)
        {
            ar[k]=br[i][j];
            k++;
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    freopen("Input.txt","r",stdin);

    lli t;

    cin>>t;

    double ar[t];

    for(i=0 ; i<t ; i++)
    {
        cin>>ar[i];
    }

    Bucket_Sort(ar,t);

    cout<<"After using Bucket Sort , the Array : \n\n";

    for(i=0 ; i<t ; i++)
    {
        cout<<ar[i]<<" ";
    }
    cout<<"\n\n";
}
