#include <iostream>
using namespace std;

void FCFS(int process,int arrival[],int burst[],int waiting[],int turnaround[],int completion[]){
	 int burs=1;
	 
	 for(int i=0;i<process;i++){
	 	burs+=burst[i];
	 	completion[i]=burs;
	 	turnaround[i]=burs-arrival[i];
	 }
	 for(int i=0;i<process;i++){
	 	waiting[i]=turnaround[i]-burst[i];
	 }
	 	float avg=0,avgw=0;
	
		cout<<"Arrival time\t\tBurst Time\t\tcompletion time\t\tTurnaround time\t     Waiting time" <<endl;
	for(int i=0;i<process;i++)
	{
		cout<<"    "<<arrival[i]<<"\t\t\t"<<"   "<<burst[i]<<"\t\t\t"<<"   "<<completion[i]<<"\t\t\t"<<turnaround[i]<<"\t\t\t"<<waiting[i]<<endl;
	
	}
	for(int i=0;i<process;i++)
	{
		avg=avg+turnaround[i];
	
	}
	for(int i=0;i<process;i++)
	{
		avgw=avgw+waiting[i];
	
	}
	cout<<"Average turnaround  : "<<avg/process<<endl;
	cout<<"Average waiting  : "<<avgw/process;	
}

int main(){
	int ch,p;
	cout<<"Enter the  number of processes : ";
	cin>>p;
	int arrvl[p];
	int burst[p];
	int waiting[p];
	int completion[p];
	int turnaround[p];

	for(int i=0;i<p;i++){
		cout<<"Enter the arrival time for process P"<<i<<"  ";
		cin>>arrvl[i];
	}
	cout<<endl;
	for(int i=0;i<p;i++){
		cout<<"Enter the burst time for process P"<<i<<"  ";		
		cin>>burst[i];
	}
	FCFS(p,arrvl,burst,waiting,turnaround,completion);	
}

