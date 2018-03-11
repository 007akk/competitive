//*************************************
//  NAME : ABHISHEK KUMAR 
// 	ROLL : 160101007
//*************************************

//	RECURSIVE VERSION OF THE CODE 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))  // to calculate the minimum of 2 integers
int matrix[4][4];			// this is to store the cost of the mutual pairs of the elements in the set S = { A, C , G , T }
int opt_sol[1000][1000] ={0};    // 2d array to store 2 bit info of which cell is chosen among the 3
int delta = 10;			// this the value of the penelty of mapping the blank space to a element in S.
int MAX_OPT_VALUE = 10000000;  // just a big number for optimal upper limit

int OPT_VALUE_CALCULATOR(char X[], char Y[], int x_length, int y_length, int opt_value ){   // function to calculate the optimum value of the cost i.e min cost

	if (x_length == 0 && y_length != 0){    // these are the base cases
		return y_length * delta ;
	}
	else if (x_length != 0 && y_length == 0){
		return x_length * delta;
	} 
	else if (x_length == 1 && y_length == 1){    // each string consist of a single character
		int x_i;
		int y_j;
		if (X[0] == 'A') x_i = 0;
		else if (X[0] == 'C') x_i = 1;
		else if (X[0] == 'G') x_i = 2;
		else if (X[0] == 'T') x_i = 3;

		if (Y[0] == 'A') y_j = 0;
		else if (Y[0] == 'C') y_j = 1;
		else if (Y[0] == 'G') y_j = 2;
		else if (Y[0] == 'T') y_j = 3;

		return matrix[x_i][y_j];
	}
	else if (x_length == 0 && y_length == 0){	 // trivial case of empty strings
		return 0;
	} 
	else {
		// we are using this recurrence relation to fill the table 
		int val1 = delta + OPT_VALUE_CALCULATOR(X, Y, x_length-1 , y_length, opt_value );  	// finally we will get the value of val_1_2_3 which is 
		int val2 = delta + OPT_VALUE_CALCULATOR(X, Y, x_length, y_length -1, opt_value);	//  the min of all adjacent cells in the table
		
		int val1_2 = MIN( val1, val2 );
		int x_i;
		int y_j;
		if (X[x_length-1] == 'A') x_i = 0;
		else if (X[x_length-1] == 'C') x_i = 1;
		else if (X[x_length-1] == 'G') x_i = 2;
		else if (X[x_length-1] == 'T') x_i = 3;

		if (Y[y_length-1] == 'A') y_j = 0;
		else if (Y[y_length-1] == 'C') y_j = 1;
		else if (Y[y_length-1] == 'G') y_j = 2;
		else if (Y[y_length-1] == 'T') y_j = 3;

		int f_xi_yi = matrix[x_i][y_j];
		int val3 = f_xi_yi + OPT_VALUE_CALCULATOR(X, Y, x_length-1 , y_length -1, opt_value );

		int val1_2_3 = MIN( val1_2 , val3 );

		if (val1_2_3 == val1) opt_sol[x_length][y_length] = 1;
		else if (val1_2_3 == val2) opt_sol[x_length][y_length] = 2;
		else if (val1_2_3 == val3) opt_sol[x_length][y_length] = 3;

		return val1_2_3;
	}
}


void print_opt_SOL_string(char X[], char Y[], int x_length, int y_length){  // function to print the final mapping of the string 1 to string 2 
	int x_len = x_length;
	int y_len = y_length;
	int i = x_len;
	int j = y_len;
	while(i >= 0 && j >= 0 ){
			if (i == 0 && j == 0) break;

			if (opt_sol[i][j] == 3){
				i--; j--;
				printf("%d\n",3 );
				printf("[X: %c , Y: %c ]\n",X[i], Y[j] );
			}
			else if (opt_sol[i][j] == 2){
				j--;
				printf("%d\n",2 );
				printf("[X: %c , Y: %c ]\n",' ', Y[j] );
			}
			else if (opt_sol[i][j] == 1){
				i--;
				printf("%d\n",1 );
				printf("[X: %c , Y: %c ]\n",X[i], ' ' );
			}
			else if (opt_sol[i][j] == 0){
				i--; j--;
				printf("%d\n",0 );
				printf("[X: %c , Y: %c ]\n",X[i], Y[j] );
				break;
			}
			else {
				break;
			}
		}
}

int main() {

	clock_t t;
    t = clock();		// to calculate the execution time
    

    int n,m;
	scanf("%d%d",&n,&m);
    char X[n];
    char Y[m];
    int j;
    int i;
    int x_length = n;		// length of string 1
    int y_length = m;		// length of string 2
    char a;
    char b;
    
    scanf("%s",X);		// taking the input strings 
    scanf("%s",Y);
    

    int opt_value_m_n = MAX_OPT_VALUE;

    for(int i=0;i<4;++i){		// this iteration is to fill the table of cost of mapping the elements of S to itself
    	for(int j=0;j<4;++j){

    		if (abs(i - j) == 0) matrix[i][j] = 0;
	    	else if (abs(i - j) == 1) matrix[i][j] = 1;
	    	else if (abs(i - j) == 2) matrix[i][j] = 2;
	    	else if (abs(i - j) == 3) matrix[i][j] = 3;
    	}
    }


    opt_value_m_n = OPT_VALUE_CALCULATOR(X, Y, x_length, y_length, MAX_OPT_VALUE );

    printf("COST: %d\n", opt_value_m_n);
    
    
    print_opt_SOL_string(X, Y, x_length, y_length);

     t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("----- execution time for the program: %f seconds.------- \n", time_taken);

    
    return 0;
}

