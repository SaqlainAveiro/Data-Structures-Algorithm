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




lli TotalWaitingTime=0,TotalCPUTime=0,Timer=0,SmallestCPUTime=0,index=0,extra=0;
double AvgWaitingTime=0.0,AvgTurnaroundTime=0.0,AvgCPUTime=0.0;
vector<lli>ProcessEntryTime;


struct SJF_Algo
{
    lli cpuTime,arrivalTime,waitingTime,turnaroundTime,InputSerial;    
};
struct SJF_Algo Process[100];



bool SortProcess(SJF_Algo x, SJF_Algo y)
{
    return x.arrivalTime < y.arrivalTime;
}

bool SerialProcess(SJF_Algo x, SJF_Algo y)
{
    return x.InputSerial < y.InputSerial;
}






void SJF()
{
    SmallestCPUTime = Process[0].cpuTime;  index=0;

    fr1(i,t-1)
    {
        if(Process[i].arrivalTime == Process[0].arrivalTime)
        {
            if(SmallestCPUTime > Process[i].cpuTime)
            {
                SmallestCPUTime = Process[i].cpuTime;   index=i;
            }
        }
    }

    TotalWaitingTime = 0;

    TotalCPUTime = Process[index].turnaroundTime = Process[index].cpuTime;

    TotalCPUTime += Process[index].arrivalTime;

    ProcessEntryTime.push_back(Process[index].arrivalTime);

    Process[index].waitingTime = 0;

    Process[index].cpuTime = SmallestCPUTime = INF;




    pf("\n\n"); pf("Output: "); pf("\n\n");

    pf("Grant Chart: ");    pf("\n\n");

    pf("|--P%lld--",Process[index].InputSerial);

    fr0(j,t)
    {
        SmallestCPUTime = INF;  k=-1;

        fr0(i,t)
        {  
            if(i==index)    continue;

            if(TotalCPUTime>=Process[i].arrivalTime)
            {
                if(Process[i].cpuTime<SmallestCPUTime)  
                {
                    SmallestCPUTime = Process[i].cpuTime;      k=i;
                }
            }
        }

        //pf("Smallest CPU Time found = %lld | Arrival Time = %lld | Serial = %lld\n",SmallestCPUTime,Process[k].arrivalTime,Process[k].InputSerial);         

        if(k==-1)
        {
            fr0(i,t)
            {
                if(TotalCPUTime<=Process[i].arrivalTime)
                {
                    ProcessEntryTime.push_back(TotalCPUTime);
                    extra = Process[i].arrivalTime - TotalCPUTime;
                    TotalCPUTime = Process[i].arrivalTime;
                    //pf(" <%lld> ",TotalCPUTime);
                    pf("|------");
                    j--;
                    break;
                }
            }
        }
        else
        {
            pf("|--P%lld--",Process[k].InputSerial);
            
            Process[k].waitingTime      = TotalCPUTime - Process[k].arrivalTime;
            TotalWaitingTime            += Process[k].waitingTime;
            Process[k].turnaroundTime   =  Process[k].waitingTime + Process[k].cpuTime;
            
            //Process[k].turnaroundTime   =  TotalCPUTime - Process[k].arrivalTime;


            if(j<t-1)   
            {
                //pf(" (%lld) ",TotalCPUTime);
                ProcessEntryTime.push_back(TotalCPUTime);
            }
            TotalCPUTime                += Process[k].cpuTime;

            Process[k].cpuTime          = INF;
        }
    }
    ProcessEntryTime.push_back(TotalCPUTime);


    pf("|\n");

    pf("%lld",ProcessEntryTime[0]);

    fr1(j,ProcessEntryTime.size()-1)
    {
        if(ProcessEntryTime[j]<10)   pf("------%lld",ProcessEntryTime[j]);
        else    pf("-----%lld",ProcessEntryTime[j]);
    }

    pf("\n\n");


    AvgCPUTime          = (double)(TotalCPUTime-extra-Process[index].arrivalTime)/(double)t;
    AvgWaitingTime      = (double)TotalWaitingTime/(double)t;
    AvgTurnaroundTime   = AvgCPUTime + AvgWaitingTime;

    sort(Process,Process+t,SerialProcess);

    fr0(i,t)
    {
        pf("Process %lld:- Waiting Time: %lld , Tunraround Time: %lld\n",Process[i].InputSerial,Process[i].waitingTime,Process[i].turnaroundTime);
    }

    pf("\n\n");
    
    pf("Total Waiting Time: %lld\n",TotalWaitingTime);
    pf("Total CPU Time: %lld\n",TotalCPUTime);
    pf("Average Waiting Time: %0.2lf\n",AvgWaitingTime);
    pf("Average Turnaround Time: %0.2lf\n",AvgTurnaroundTime);
}



int main()
{
    //FastIO;

    read(in);    write(out);

    //pf("Enter the number of process: ");    
    
    sf1(t);     
    
    //pf("\n\n");   pf("Enter the CPU Times: ");

    fr1(i,t)      sf1(x),     Process[i-1].cpuTime=x, Process[i-1].InputSerial=i;

    //pf("\n\n");   pf("Enter the Arrival Times: ");

    fr1(i,t)      sf1(x),     Process[i-1].arrivalTime=x;

    pf("Input: ");  pf("\n\n");

    fr0(i,t)
    {
        pf("Process %lld:- Arrival Time: %lld , CPU Time: %lld\n",Process[i].InputSerial,Process[i].arrivalTime,Process[i].cpuTime);
    }

    sort(Process,Process+t,SortProcess);

    SJF();
}