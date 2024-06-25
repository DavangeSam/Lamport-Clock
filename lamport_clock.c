
#include <stdio.h>

// Displaying the time stamps of events in process 1
void display_process_1(int event_process_1, int process_no_1[7])
{
	
	printf("\n\nLet's look at the time stamps of events in Process 1 ! \n\n");

	for (int i = 0; i < event_process_1; i++) {
		if(process_no_1[i]==0){							//If timestamp is zero then display error to check value
			printf("e");
			printf("%d ", i+1);
			printf(": check value");

		}
			
		else {
		printf("e");
		printf("%d ", i+1);
		printf(": ");
		printf("%d ", process_no_1[i]);
		printf("\n");
		}
	}
}

// Displaying the time stamps of events in process 2
void display_process_2(int event_process_2, int process_no_2[6])
{

	printf("\n\nLet's look at the time stamps of events in Process 2 !\n\n");

	
	for (int i = 0; i < event_process_2; i++)
	{
		if(process_no_2[i]==0){							//If timestamp is zero then display error to check value
			printf("e");
			printf("%d ", i+1);
			printf(": check value");

		}

		else{
		printf("e");
		printf("%d ", i+1);
		printf(": ");
		printf("%d ", process_no_2[i]);
		printf("\n");
		}
	}	
		
}

// Calculate timestamp of Process 1 and Process 2
void clock_lamport_calc(int event_process_1, int event_process_2, int matrix_incoming[7][6], int process_no_1[7], int process_no_2[6])
{
	int i, j;
	int p;
	int bigger;

	for (i = 0; i < event_process_1; i++) {
		for (j = 0; j < event_process_2; j++) {

			// Calculating timestamp according to IR2
			int temp = matrix_incoming[i][j];
			switch(temp)
			{
				case 1:													//message sent by process 1
				//Finding max timestamp amongst 2 events according to IR2 using ternary operator
				bigger = (process_no_2[j] > (process_no_1[i] + 1)) ? process_no_2[j] : (process_no_1[i] + 1);
				process_no_2[j] = bigger;
				for (p = j + 1; p < event_process_2; p++)
					process_no_2[p] = process_no_2[p - 1] + 1;
				break;

				case -1:												//message received by process 1
				//Finding max timestamp amongst 2 events according to IR2 using ternary operator
				bigger = (process_no_1[i] > (process_no_2[j] + 1)) ? process_no_1[i] : (process_no_2[j] + 1);
				process_no_1[i] = bigger;
				for (p = i + 1; p < event_process_1; p++)
					process_no_1[p] = process_no_1[p - 1] + 1;
				break;

			}
			
		}
	}

	// Calling fuction to display the timestamps of Process 1
	display_process_1(event_process_1, process_no_1);

	// Calling fuction to display the timestamps of Process 2
	display_process_2(event_process_2, process_no_2);
}

// Main Fuction

int main()
{
    //Process 1 has 7 events 
    //Process 2 has 6 events
	int event_process_1 = 7, event_process_2 = 6;
	int matrix_incoming[7][6];
	int process_no_1[event_process_1];
	int process_no_2[event_process_2];

	for(int i = 0; i < event_process_1; i++)					//Initially setting all values inside matrix to 0
	{
		for(int j = 0; j < event_process_2; j++)
		{
			matrix_incoming[i][j] = 0;
		}
	}

    // matrix is defined according to following cases which apply between 2 processes
	//case 1 : matrix_incoming[i][j] = 1 if message is sent from event i to event j
	//case 2 : matrix_incoming[i][j] = -1 if message is sent from event j to event i i.e., received by i from j
	//case 3 : matrix_incoming[i][j] = 0 if none sent or received from event i to event j

	matrix_incoming[1][2] = 1;									//message sent from e12 to e23
	matrix_incoming[4][4] = 1;									//message sent from e15 to e25
	matrix_incoming[6][3] = -1;									//message sent from e24 to e17

	
//Printing Matrix 
	printf("\n\nMatrix of incoming messages is as following :\n\n");
	for (int i = 0; i < event_process_1; i++)
		process_no_1[i] = i + 1;
	
	for (int i = 0; i < event_process_2; i++)
		process_no_2[i] = i + 1;

	//Printing e2 columns
	for (int i = 0; i < event_process_2; i++)
		printf("\te2%d", i + 1);

	//printing e1 rows
	for (int i = 0; i < event_process_1; i++) {

		printf("\n e1%d \t", i + 1);
	//printing matrix values
		for (int j = 0; j < event_process_2; j++)
			printf("%d\t", matrix_incoming[i][j]);
	}

	// Calling fuction to calculate timestamps of lamport clock
	clock_lamport_calc(event_process_1, event_process_2, matrix_incoming, process_no_1, process_no_2);

	return 0;
}
