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




lli TotalWaitingTime=0,TotalCPUTime=0,Timer=0,SmallestCPUTime=0,index=0,previous_index=0,extra=0,current_Process=0;
double AvgWaitingTime=0.0,AvgTurnaroundTime=0.0,AvgCPUTime=0.0;
vector<lli>ProcessEntryTime;

struct SRTN_Algo
{
    lli CPU_Time1,ArrivalTime,WaitingTime,TurnAroundTime,InputSerial,CPU_Time2; 
};
struct SRTN_Algo Process[100];



bool SortProcess(SRTN_Algo x, SRTN_Algo y)
{
    return x.ArrivalTime < y.ArrivalTime;
}

bool SerialProcess(SRTN_Algo x, SRTN_Algo y)
{
    return x.InputSerial < y.InputSerial;
}






void SRTN()
{
    SmallestCPUTime = Process[0].CPU_Time1;  index=0;

    fr1(i,t-1)
    {
        if(Process[i].ArrivalTime == Process[0].ArrivalTime)
        {
            if(SmallestCPUTime > Process[i].CPU_Time1)
            {
                SmallestCPUTime = Process[i].CPU_Time1;   index=i;
            }
        }
    }



    TotalWaitingTime = 0;

    current_Process = Process[index].InputSerial;

    Timer+=Process[index].ArrivalTime;

    extra+=Process[index].ArrivalTime;

    ProcessEntryTime.push_back(Process[index].ArrivalTime);    
    
    p=index;
    
    
    
    pf("\n\nOutput : \n\n");

    pf("Grant Chart: \n\n");

    pf("|--P%lld--",Process[index].InputSerial);


    frx(i,Process[p].ArrivalTime,Timer)
    {
        fr0(j,t)
        {
            if(i>=Process[j].ArrivalTime)
            {
                if(SmallestCPUTime > Process[j].CPU_Time1 && Process[j].CPU_Time1>0)
                {
                    SmallestCPUTime = Process[j].CPU_Time1;   index=j;
                }
            }
        }

        if(current_Process!=Process[index].InputSerial)
        {
            if(Process[previous_index].CPU_Time1==0)   
            {
                Process[previous_index].TurnAroundTime = i - Process[previous_index].ArrivalTime;
            }
            current_Process=Process[index].InputSerial;

            pf("|--P%lld--",current_Process);

            ProcessEntryTime.push_back(i);

            previous_index=index;
        }
        else   SmallestCPUTime = Process[index].CPU_Time1;

        Process[index].CPU_Time1--;

        if(Process[index].CPU_Time1==0)   
        {
            SmallestCPUTime=INF;
            Process[index].TurnAroundTime = i+1 - Process[index].ArrivalTime;
        }
    }
    pf("|\n");

    ProcessEntryTime.push_back(Timer);    
    
    pf("%lld",ProcessEntryTime[0]);

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

    fr1(i,t)      sf1(x),     Process[i-1].CPU_Time1=Process[i-1].CPU_Time2=x, Process[i-1].InputSerial=i , Timer+=x;

    pf("\n\n");   pf("Enter the Arrival Times: ");

    fr1(i,t)      sf1(x),     Process[i-1].ArrivalTime=x;

    
    
    pf("Input: ");  pf("\n\n");

    fr0(i,t)
    {
        pf("Process %lld:- Arrival Time: %lld , CPU Time: %lld\n",Process[i].InputSerial,Process[i].ArrivalTime,Process[i].CPU_Time1);
    }

    sort(Process,Process+t,SortProcess);

    SRTN();
}