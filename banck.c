#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int n, m; // Number of processes and resources
int allocation[MAX_P][MAX_R]; // Allocation matrix
int max[MAX_P][MAX_R]; // Maximum demand matrix
int available[MAX_R]; // Available resources
int need[MAX_P][MAX_R]; // Need matrix
bool finished[MAX_P]; // Process completion flag
int safeSequence[MAX_P];

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe()
{
int work[m];
for(int i=0;i<m;i++)
{
work[i]=available[i];
}
int count=0;
while(count<n)
{
     bool found=false;
     for(int i=0;i<n;i++)
     {   if(!finished[i])
	     {
	           bool canexecute=true;
                   for(int j=0;j<m;j++)
		   {
	                  if(need[i][j]>work[j])
			  {
			  canexecute=false;
			  break;
			  }		  
	            }
            if(canexecute)
	    {
	    for(int j=0;j<m;j++)
	    {
	    work[j]+=allocation[i][j];
	    }
	    }
           finished[i]=true;
	   found=true;
           safeSequence[count++]=i;
     }

}




if(!found)
{
return false;
}


}
return true;
}
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter maximum matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize finished array
    for (int i = 0; i < n; i++) {
        finished[i] = false;
    }

    calculateNeed();

    if (isSafe()) {
        printf("System is in a SAFE STATE.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("System is in an UNSAFE STATE (Deadlock may occur).\n");
    }

    return 0;
}

