#include <stdio.h>



int main()
{
    int alloc[5][3];
    int max[5][3];
    int avail[3];

    FILE *fptr;
    // Open a file in read mode
    fptr = fopen("input.txt", "r");
    // Store the content of the file
    char myString[10];

    // If the file exist
    if(fptr != NULL) {
        //filter and process input
        int processCount = 0;
        int resourceCount = 0;
        while(fgets(myString, 10, fptr)) {
            if (processCount <= 4) {
                for (int i = 0; i < 10; i++) {
                    if (myString[i] == ',') {
                        resourceCount++;
                    }
                    else if (myString[i] == '\n') {
                        resourceCount = 0;
                        break;
                    }
                    else {
                        alloc[processCount][resourceCount] = myString[i] - '0';
                    }
                }
            }
            else if (processCount >= 5 && processCount <= 9) {
                for (int i = 0; i < 10; i++) {
                    if (myString[i] == ',') {
                        resourceCount++;
                    }
                    else if (myString[i] == '\n') {
                        resourceCount = 0;
                        break;
                    }
                    else {
                        max[processCount % 5][resourceCount] = myString[i] - '0';
                    }
                }
            }
            else {
                for (int i = 0; i < 10; i++) {
                    if (myString[i] == ',') {
                        resourceCount++;
                    }
                    else if (myString[i] == '\n' || myString[i] == '\0') {
                        resourceCount = 0;
                        break;
                    }
                    else {
                        avail[resourceCount] = myString[i] - '0';
                    }
                }
            }
            processCount++;
        }

    // If the file does not exist 
    } else {
    printf("Not able to open the file.");
    }


    
	int numOfProcesses, numOfResources, i, j, k;
	numOfProcesses = 5;
	numOfResources = 3;


	int f[numOfProcesses], ans[numOfProcesses], ind = 0;
	for (k = 0; k < numOfProcesses; k++) {
		f[k] = 0;
	}

	int need[numOfProcesses][numOfResources];
	for (i = 0; i < numOfProcesses; i++) {
		for (j = 0; j < numOfResources; j++)
			need[i][j] = max[i][j] - alloc[i][j]; //calculate i need of j
	}

	int y = 0;
	for (k = 0; k < 5; k++) {
		for (i = 0; i < numOfProcesses; i++) {
			if (f[i] == 0) {

				int flag = 0;
                //check if needed resources are more than available
				for (j = 0; j < numOfResources; j++) {
					if (need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}

                //if not put in process to ans and adjust available accordingly
				if (flag == 0) {
					ans[ind++] = i;
					for (y = 0; y < numOfResources; y++)
						avail[y] += alloc[i][y];
					f[i] = 1;
				}
			}
		}
	}

	int flag = 1;
	

    //check if sequence safe or not
	for (int i = 0; i < numOfProcesses; i++) {
        if(f[i] == 0) {
            flag = 0;
            printf("The system is not safe");
            break;
        }
	}
	
	if (flag == 1) {
        printf("Safe Sequence: ");
        for (i = 0; i < numOfProcesses - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[numOfProcesses - 1]);
	}
	
    // Close the file
    fclose(fptr);
	return 0;

}