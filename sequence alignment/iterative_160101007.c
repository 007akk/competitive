//*************************************
//  NAME : ABHISHEK KUMAR 
// 	ROLL : 160101007
//*************************************

//	ITERATIVE VERSION OF THE CODE 

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))  // to calculate the minimum of 2 integers
int matrix[4][4];			// this is to store the cost of the mutual pairs of the elements in the set S = { A, C , G , T }
int opt_sol[1000][1000] ={0};    // 2d array to store 2 bit info of which cell is chosen among the 3
int delta = 10;			// this the value of the penelty of mapping the blank space to a element in S.
int MAX_OPT_VALUE = 10000000;  // just a big number for optimal upper limit
int opt_SOL_iterative[1000][1000] ;

void OPT_VALUE_CALCULATOR(char X[], char Y[], int x_length, int y_length, int opt_value ){
	int i;
	for (i = 0; i<=x_length ; ++i){
		opt_SOL_iterative[i][0] = i *delta; 
	}
	for (i = 0; i<=y_length ; ++i){
		opt_SOL_iterative[0][i] = i *delta; 
	}
	if (x_length >=1 && y_length >=1){
		int x_i;
		int y_j;
		if (X[0] == 'A') x_i = 0;

		opt_SOL_iterative[1][1] = matrix[x_i][y_j];
	}

	int j;
	for (i=1;i<=x_length ;++i){
		for (j = 1;j<=y_length ;++j){
			if ( !(i == 1 && j == 1)){

				int x_i;
				int y_j;
				if (X[i-1] == 'A') x_i = 0;
				else if (X[i-1] == 'C') x_i = 1;
				else if (X[i-1] == 'G') x_i = 2;
				else if (X[i-1] == 'T') x_i = 3;

				if (Y[j-1] == 'A') y_j = 0;
				else if (Y[j-1] == 'C') y_j = 1;
				else if (Y[j-1] == 'G') y_j= 2;
				else if (Y[j-1] == 'T') y_j = 3;

				int v1 = (opt_SOL_iterative[i-1][j] + delta);
				int v2 = (opt_SOL_iterative[i][j-1] + delta);
				int v3;
				v3 = opt_SOL_iterative[i-1][j-1] + matrix[x_i][y_j];
				int temp = MIN( v1, v2);
				opt_SOL_iterative[i][j] = MIN( v3 , temp);
				int val1_2_3 = opt_SOL_iterative[i][j];
				int val1 = v1;
				int val2 = v2;
				int val3 = v3;
				if (val1_2_3 == val1) opt_sol[i][j] = 1;
				else if (val1_2_3 == val2) opt_sol[i][j] = 2;
				else if (val1_2_3 == val3) opt_sol[i][j] = 3;
			}
		}
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
				printf("[X: %c , Y: %c ]\n",X[i], Y[j] );
			}
			else if (opt_sol[i][j] == 2){
				j--;
				printf("[X: %c , Y: %c ]\n",' ', Y[j] );
			}
			else if (opt_sol[i][j] == 1){
				i--;
				printf("[X: %c , Y: %c ]\n",X[i], ' ' );
			}
			else if (opt_sol[i][j] == 0){
				i--; j--;
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
    
    scanf("%s",X);			// taking the input strings 
    scanf("%s",Y);

    int opt_value_m_n = MAX_OPT_VALUE;

    for(int i=0;i<4;++i){			// this iteration is to fill the table of cost of mapping the elements of S to itself
    	for(int j=0;j<4;++j){

    		if (abs(i - j) == 0) matrix[i][j] = 0;
	    	else if (abs(i - j) == 1) matrix[i][j] = 1;
	    	else if (abs(i - j) == 2) matrix[i][j] = 2;
	    	else if (abs(i - j) == 3) matrix[i][j] = 3;
    	}
    }

    OPT_VALUE_CALCULATOR(X, Y, x_length, y_length, MAX_OPT_VALUE );

    printf("COST : %d\n", opt_SOL_iterative[x_length][y_length]);

      t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 	
    print_opt_SOL_string(X, Y, x_length, y_length);

    printf("----- execution time for the program: %f seconds.------- \n", time_taken);
    
    return 0;
}

