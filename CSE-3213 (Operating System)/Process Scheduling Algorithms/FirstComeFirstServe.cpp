#include<bits/stdc++.h>

using namespace std;

#define FastIO ios_base :: sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define read(in) freopen("Input.txt","r",stdin)
#define write(out) freopen("Output.txt","w",stdout)
#define pf printf
#define sf scanf
#define fr0(i,n) for(long long int i=0 ; i<n ; i++)
#define fr1(i,n) for(long long int i=1 ; i<=n ; i++)
#define fr2(i,n) for(long long int i=n ; i>=1 ; i--)
#define frx(i,x,n) for(long long int i=x ; i<=n ; i++)
#define sf1(val) scanf("%lld",&val)
#define sf2(val1,val2) scanf("%lld %lld",&val1,&val2)
#define INF 999999999999999999
#define Pi 2*acos(0.0)
#define len 200000

typedef long long int lli;

lli a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,sum=0,total=0,res=0,ans=0;


lli TotalWaitingTime=0,TotalCPUTime=0;
double AvgWaitingTime=0.0,AvgTurnaroundTime=0.0,AvgCPUTime=0.0;
vector<lli>ProcessEntryTime;

struct FCFS_Algo
{
    lli cpuTime,arrivalTime,waitingTime,turnaroundTime,InputSerial;    
};

struct FCFS_Algo Process[100];


bool SerialProcess(FCFS_Algo x, FCFS_Algo y)
{
    return x.InputSerial < y.InputSerial;
}



void FCFS()
{
    Process[0].waitingTime=0;

    TotalCPUTime = Process[0].turnaroundTime = Process[0].cpuTime;

    ProcessEntryTime.push_back(0);
    ProcessEntryTime.push_back(TotalCPUTime);

    fr1(i,t-1)
    {        
        Process[i].waitingTime = TotalCPUTime - Process[i].arrivalTime;

        Process[i].turnaroundTime = Process[i].cpuTime+Process[i].waitingTime;
        
        TotalWaitingTime+=Process[i].waitingTime;

        TotalCPUTime+=Process[i].cpuTime;

        ProcessEntryTime.push_back(Process[i].turnaroundTime);
    }

    AvgCPUTime=(double)TotalCPUTime/(double)t;
    AvgWaitingTime=(double)TotalWaitingTime/(double)t;
    AvgTurnaroundTime = AvgCPUTime + AvgWaitingTime;

    pf("\n\n");     pf("Output: ");    pf("\n\n");

    pf("Grant Chart: ");    pf("\n\n");

    pf("|");    fr0(i,t)   pf("--P%lld--|",Process[i].InputSerial);     pf("\n");

    pf("%lld",ProcessEntryTime[0]);

    fr1(j,ProcessEntryTime.size()-1)
    {
        if(ProcessEntryTime[j]<10)   pf("------%lld",ProcessEntryTime[j]);
        else    pf("-----%lld",ProcessEntryTime[j]);
    }

    pf("\n\n");
    
    sort(Process,Process+t,SerialProcess);

    fr0(i,t)
    {
        pf("Process %lld:- Waiting Time: %lld , Tunraround Time: %lld\n",Process[i].InputSerial,Process[i].waitingTime,Process[i].turnaroundTime);
    }

    pf("\n\n");
    pf("Average Waiting Time: %0.2lf\n",AvgWaitingTime);
    pf("Average Turnaround Time: %0.2lf\n",AvgTurnaroundTime);
}



int main()
{
    //FastIO;

    //read(in);    write(out);

    pf("Enter the number of process: ");    
    
    sf1(t);     
    
    pf("\n\n");   pf("Enter the CPU Times: ");

    fr1(i,t)      
    {
        sf1(x);
        Process[i-1].cpuTime=x;
        Process[i-1].InputSerial=i;
        Process[i-1].arrivalTime=0;
    }

    pf("Input: ");  pf("\n\n");

    fr0(i,t)
    {
        pf("Process %lld:- CPU Time: %lld\n",Process[i].InputSerial,Process[i].cpuTime);
    }

    FCFS();
}
