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




lli TotalWaitingTime=0,TotalCPUTime=0,Timer=0,SmallestPriority=0,index=0,previous_index=0,extra=0,current_Process=0;
double AvgWaitingTime=0.0,AvgTurnaroundTime=0.0,AvgCPUTime=0.0;
vector<lli>ProcessEntryTime;

struct Pr_Algo
{
    lli CPU_Time1,ArrivalTime,WaitingTime,TurnAroundTime,InputSerial,CPU_Time2,Priority; 
};
struct Pr_Algo Process[100];



bool SortProcess(Pr_Algo x, Pr_Algo y)
{
    return x.ArrivalTime < y.ArrivalTime;
}

bool SerialProcess(Pr_Algo x, Pr_Algo y)
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



void Pr_NonPreemptive()
{
    SmallestPriority = Process[0].Priority;  index=0;

    fr1(i,t-1)
    {
        if(Process[i].ArrivalTime == Process[0].ArrivalTime)
        {
            if(SmallestPriority > Process[i].Priority)
            {
                SmallestPriority = Process[i].Priority;   index=i;
            }
        }
    }

    TotalWaitingTime = 0;

    TotalCPUTime = Process[index].TurnAroundTime = Process[index].CPU_Time1;

    TotalCPUTime += Process[index].ArrivalTime;

    ProcessEntryTime.push_back(Process[index].ArrivalTime);

    Process[index].WaitingTime = 0;

    Process[index].Priority = INF;


    pf("\n\n"); pf("Output: "); pf("\n\n");

    pf("Grant Chart: ");    pf("\n\n");

    pf("|--P%lld--|",Process[index].InputSerial);

    fr0(j,t)
    {
        SmallestPriority = INF;  k=-1;

        fr0(i,t)
        {  
            if(i==index)    continue;

            if(TotalCPUTime>=Process[i].ArrivalTime)
            {
                if(Process[i].Priority < SmallestPriority)  
                {
                    SmallestPriority = Process[i].Priority;      k=i;
                }
            }
        }

        //pf("Smallest CPU Time found = %lld | Arrival Time = %lld | Serial = %lld\n",SmallestCPUTime,Process[k].arrivalTime,Process[k].InputSerial);         

        if(k==-1)
        {
            fr0(i,t)
            {
                if(TotalCPUTime<=Process[i].ArrivalTime)
                {
                    ProcessEntryTime.push_back(TotalCPUTime);
                    extra = Process[i].ArrivalTime - TotalCPUTime;
                    TotalCPUTime = Process[i].ArrivalTime;
                    //pf(" <%lld> ",TotalCPUTime);
                    pf("------|");
                    j--;
                    break;
                }
            }
        }
        else
        {
            pf("--P%lld--|",Process[k].InputSerial);
            
            Process[k].WaitingTime      = TotalCPUTime - Process[k].ArrivalTime;
            TotalWaitingTime            += Process[k].WaitingTime;
            Process[k].TurnAroundTime   =  Process[k].WaitingTime + Process[k].CPU_Time1;
            
            //Process[k].turnaroundTime   =  TotalCPUTime - Process[k].arrivalTime;


            if(j<t-1)   
            {
                //pf(" (%lld) ",TotalCPUTime);
                ProcessEntryTime.push_back(TotalCPUTime);
            }
            TotalCPUTime += Process[k].CPU_Time1;

            Process[k].Priority = INF;
        }
    }
    ProcessEntryTime.push_back(TotalCPUTime);

    pf("\n%lld",ProcessEntryTime[0]);

    fr1(j,ProcessEntryTime.size()-1)
    {
        if(ProcessEntryTime[j]<10)   pf("------%lld",ProcessEntryTime[j]);
        else    pf("-----%lld",ProcessEntryTime[j]);
    }

    pf("\n\n");

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




void Pr_Preemptive()
{
    SmallestPriority = Process[0].Priority;  index=0;

    fr1(i,t-1)
    {
        if(Process[i].ArrivalTime == Process[0].ArrivalTime)
        {
            if(SmallestPriority > Process[i].Priority)
            {
                SmallestPriority = Process[i].Priority;   index=i;
            }
        }
    }

    TotalWaitingTime = 0;

    TotalCPUTime = Process[index].TurnAroundTime = Process[index].CPU_Time1;

    TotalCPUTime += Process[index].ArrivalTime;

    Process[index].WaitingTime = 0;

    p=index;       
    
    pf("\n\nOutput : \n\n");

    pf("Grant Chart: \n\n");

    pf("|--P%lld--|",Process[index].InputSerial);
    
    ProcessEntryTime.push_back(Process[index].ArrivalTime);
    current_Process = Process[index].InputSerial;    
    
    frx(i,Process[p].ArrivalTime,Timer)
    {
        fr0(j,t)
        {
            if(i>=Process[j].ArrivalTime)
            {
                if(SmallestPriority > Process[j].Priority)
                {
                    SmallestPriority = Process[j].Priority;   index=j;                    
                }
            }
        }

        if(current_Process != Process[index].InputSerial)
        {            
            current_Process = Process[index].InputSerial;

            ProcessEntryTime.push_back(i);

            pf("--P%lld--|",current_Process);
        }
        else    SmallestPriority = INF;

        Process[index].CPU_Time1--;

        if(Process[index].CPU_Time1 == 0)   
        {
            Process[index].TurnAroundTime = i+1 - Process[index].ArrivalTime;
            Process[index].Priority = INF;
        }
    }

    ProcessEntryTime.push_back(Timer);  


    
    pf("\n");    pf("%lld",ProcessEntryTime[0]);

    fr1(j,ProcessEntryTime.size()-1)
    {
        if(ProcessEntryTime[j]<10)   pf("------%lld",ProcessEntryTime[j]);
        else    pf("-----%lld",ProcessEntryTime[j]);
    }
    
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
        Process[i-1].InputSerial=i;
        Timer+=x;
    }

    pf("\n\n");   pf("Enter the Arrival Times: ");

    fr1(i,t)      sf1(x),     Process[i-1].ArrivalTime=x;

    pf("\n\n");   pf("Enter the Priorities: ");

    fr1(i,t)      sf1(x),     Process[i-1].Priority=x;

    
    pf("Input: ");  pf("\n\n");

    fr0(i,t)
    {
        pf("Process %lld:- Arrival Time: %lld , CPU Time: %lld , Priority: %lld\n",Process[i].InputSerial,Process[i].ArrivalTime,Process[i].CPU_Time1,Process[i].Priority);
    }

    sort(Process,Process+t,SortProcess);

    //Pr_NonPreemptive();
    //Pr_Preemptive();
}