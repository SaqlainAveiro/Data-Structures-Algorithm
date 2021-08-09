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




lli TotalWaitingTime=0,TotalCPUTime=0,Timer=0,CurrentCPUTime=0,index=0,extra=0,time_quantum=0,current_process=0;
double AvgWaitingTime=0.0,AvgTurnaroundTime=0.0,AvgCPUTime=0.0;
vector<lli>ProcessEntryTime;
map<lli,lli>ProcessArrivalTimeMap;
queue<lli>Q;

struct RR_Algo
{
    lli CPU_Time1,ArrivalTime,WaitingTime,TurnAroundTime,InputSerial,CPU_Time2; 
};
struct RR_Algo Process[100];



bool SortProcess(RR_Algo x, RR_Algo y)
{
    return x.ArrivalTime < y.ArrivalTime;
}

bool SerialProcess(RR_Algo x, RR_Algo y)
{
    return x.InputSerial < y.InputSerial;
}

lli FindProcessIndex(lli PI)
{
    fr0(i,t)
    {
        if(Process[i].InputSerial==PI)
        {
            return i;
        }
    }
}




void RR()
{
    Q.push(Process[0].InputSerial);

    Timer = extra = Process[0].ArrivalTime;     
    
    pf("\n\nOutput : \n\n");

    pf("Grant Chart: \n\n");

    pf("|");

    while(1)
    {
        if(!Q.empty())
        {
            pf("--P%lld--|",Q.front());

            index = FindProcessIndex(Q.front());

            CurrentCPUTime = Process[index].CPU_Time1;

            ProcessEntryTime.push_back(Timer);

            Q.pop();

            x=min(Timer+time_quantum , Timer+CurrentCPUTime);

            frx(i,Timer+1,x)
            {
                if(ProcessArrivalTimeMap[i]!=0)
                {
                    Q.push(ProcessArrivalTimeMap[i]);
                    //pf("Found: P%lld\n",ProcessArrivalTimeMap[i]);
                }

                Process[index].CPU_Time1--;

                if(Process[index].CPU_Time1==0)
                {
                    Process[index].TurnAroundTime = i - Process[index].ArrivalTime;
                    x = i;  break;
                }
            }

            Timer = x;

            if(Process[index].CPU_Time1>0)
            {
                Q.push(Process[index].InputSerial);
                //pf("Remaining: P%lld\n",Process[index].InputSerial);
            }
        }
        else
        {
            fr0(i,t)
            {
                if(Process[i].CPU_Time1>0)  
                {
                    Q.push(Process[i].InputSerial);

                    if(Timer < Process[i].ArrivalTime)
                    {
                        ProcessEntryTime.push_back(Timer);
                        extra += Process[i].ArrivalTime - Timer;
                        Timer = Process[i].ArrivalTime;
                        pf("------|");                        
                        break;
                    }
                }
            }
            if(Q.empty())   break;
        }        
    }

    ProcessEntryTime.push_back(Timer);

    pf("\n%lld",ProcessEntryTime[0]);

    fr1(j,ProcessEntryTime.size()-1)
    {
        if(ProcessEntryTime[j]<10)   pf("------%lld",ProcessEntryTime[j]);
        else    pf("-----%lld",ProcessEntryTime[j]);
    }

    pf("\n\n");

    


    fr0(i,t)
    {
        Process[i].WaitingTime = Process[i].TurnAroundTime - Process[i].CPU_Time2;
        TotalWaitingTime += Process[i].WaitingTime;
    }
    
    
    pf("\n\n");pf("\n\n");

    AvgCPUTime          = (double)(Timer-extra)/(double)t;
    AvgWaitingTime      = (double)TotalWaitingTime/(double)t;
    AvgTurnaroundTime   = AvgCPUTime + AvgWaitingTime;

    sort(Process,Process+t,SerialProcess);

    fr0(i,t)
    {
        pf("Process %lld:- Waiting Time: %lld , Tunraround Time: %lld\n",Process[i].InputSerial,Process[i].WaitingTime,Process[i].TurnAroundTime);
    }

    pf("\n\n");
    
    pf("Total Waiting Time: %lld\n",TotalWaitingTime);
    pf("Total CPU Time: %lld\n",Timer);
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
        Process[i-1].CPU_Time1 = Process[i-1].CPU_Time2 = x;
        Process[i-1].InputSerial = i;
    }

    pf("\n\n");   pf("Enter the Arrival Times: ");

    fr1(i,t)      
    {
        sf1(x);
        Process[i-1].ArrivalTime = x;
        ProcessArrivalTimeMap[x] = Process[i-1].InputSerial;
    }

    pf("\n\n");   pf("Enter the Time Quantum: ");

    sf1(time_quantum);
    
    pf("\n\n");  
    
    pf("Input: ");  pf("\n\n");

    fr0(i,t)
    {
        pf("Process %lld:- Arrival Time: %lld , CPU Time: %lld\n",Process[i].InputSerial,Process[i].ArrivalTime,Process[i].CPU_Time1);
    }

    sort(Process,Process+t,SortProcess);

    RR();
}