//round robin solution 

#define PId 0       
#define AvT 1       
#define BT 2        
#define CT 3        
#define WT 4        
#define TaT 5       
#define maxCol 6    
#include<iostream>
using namespace std;

void printPDetailTable(int mat[][maxCol], int totalProcesses,  int uptoColumn=maxCol)
{
    for (int i = 0; i < totalProcesses; i++)
    {
        cout<<"| P";
        for (int j = 0; j < uptoColumn; j++)
        {
            if(j==0)
            {
                cout<<mat[i][j]<<"\t\t|";
            }
            else
            {
                cout<<"|\t"<<mat[i][j]<<"\t|";
            }
            
        }
		cout<<endl;
	}
}

void getJobDetails(int mat[][maxCol], int totalProcesses)
{
    cout<<endl<< "------------------------------------------------------------------------";
    cout<<endl<< "...Enter the process Details..."<<endl<<endl;
	for (int i = 0; i < totalProcesses; i++)
    {
		cout << "...For Process " << i + 1 << "..."<<endl;
		cout << "Enter Process Id: ";
		cin >> mat[i][PId];
		cout << "Enter Arrival Time: ";
		cin >> mat[i][AvT];
		cout << "Enter Burst Time: ";
		cin >> mat[i][BT];
	}
    cout<<endl<< "------------------------------------------------------------------------";
}

void sortMat(int mat[][maxCol], int totalProcesses)
{
    for(int i=0;i<totalProcesses;i++)
	{		
		for(int j=i+1;j<totalProcesses;j++)
		{
			if(mat[i][PId]>mat[j][PId])
            {
                for(int k=0;k<maxCol;k++)
                {
                    swap(mat[i][k],mat[j][k]);
                }
            }
        }
	}
}

void arrangeArrival(int mat[][maxCol], int totalProcesses)
{
	for (int i = 0; i < totalProcesses; i++) {
		for (int j = 0; j < totalProcesses - i - 1; j++) {
			if (mat[j][AvT] > mat[j + 1][AvT]) {
				for (int k = 0; k < 5; k++) {
					swap(mat[j][k], mat[j + 1][k]);
				}
			}
		}
	}
}

float avgWaitingTime(int mat[][maxCol], int totalProcesses)
{
    int sum = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        sum+=mat[i][WT];
    }
    return ((float)sum/(float)totalProcesses);
}

float avgTurnAroundTime(int mat[][maxCol], int totalProcesses)
{
    int sum = 0;
    for (int i = 0; i < totalProcesses; i++)
    {
        sum+=mat[i][TaT];
    }
    return ((float)sum/(float)totalProcesses);
}

void copyColumnToArray(int mat[][maxCol], int totalProcesses, int columnNumber, int destination[])
{
    for (int i = 0; i < totalProcesses; i++)
    {
        destination[i]= mat[i][columnNumber];
    }
}

void calculate_time(int mat[][maxCol], int totalProcesses, int quantumNumber)
{
    
    int remainingBurst[totalProcesses];
    copyColumnToArray(mat, totalProcesses, BT, remainingBurst);
    int i, compTime=0;
    int processDone=0;
    int left = totalProcesses;
    for(i=0, compTime=0; left!=0 ;)
    {
        if(remainingBurst[i]<=quantumNumber && remainingBurst[i]>0)
        {
            compTime = compTime + remainingBurst[i];
            remainingBurst[i] = 0;
            processDone=1;
        }
        else if(remainingBurst[i]>0)
        {
            remainingBurst[i] -= quantumNumber;
            compTime = compTime + quantumNumber;
        }

        if(remainingBurst[i]==0 && processDone==1)
        {
            left--;
            mat[i][CT]=compTime;
            mat[i][TaT]= mat[i][CT] - mat[i][AvT];
            mat[i][WT]= mat[i][TaT] - mat[i][BT];
            processDone=0;
        }
        if(i==totalProcesses-1)  
        {  
            i=0;  
        }  
        else if(mat[i+1][AvT]<=compTime)  
        {  
            i++;  
        }  
        else  
        {  
            i=0;  
        }              
    }
}


int main()
{
    int totalProcesses, quantumNumber;
    cout<<endl<<">> Enter Total Number of Processes: "<<endl<<">> ";
    cin>>totalProcesses;
    int mat[totalProcesses][maxCol] = {0};

    getJobDetails(mat, totalProcesses);
    cout<<endl<<">> Enter Quantum Number: ";
    cin>>quantumNumber;
    arrangeArrival(mat, totalProcesses);
    calculate_time(mat, totalProcesses, quantumNumber);

    cout<<endl<< "----------------------------------------------------------------------------------------------------";
	cout<<endl<< ">> After Calculation, Final Result...";
    cout<<endl<< "----------------------------------------------------------------------------------------------------"<<endl;
	cout<<"   Process ID\t   Arrival Time\t    Burst Time\t  Completion Time\t\b\b\b\b\bWaiting Time\t\b\b\b\b\b\bTurnaround Time"<<endl;
	printPDetailTable(mat, totalProcesses, maxCol);

    cout<<endl<<endl<<"Average Waiting Time = "<<avgWaitingTime(mat, totalProcesses);
    cout<<endl<<"Average Turn Around Time = "<<avgTurnAroundTime(mat, totalProcesses);

	return 0;
}
