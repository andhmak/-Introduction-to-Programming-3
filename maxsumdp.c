/* File: maxsumdp.c */

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b, int c);                              /* "Max" declaration. Full implementation in "maxsum.c" (main). */

int solve(int n, int m, int **matr) {                      /* The "solve" function taking a matrix and its dimensions as inputs and printing the maximum possible sum */
	int **parmatr, maxsum = 0, i, j, max_location;     /* parmatr: partial sum matrix, sum: maximum sum down to the current position, maxsum: the maximum value of "sum", i/j: coordinates, max_location: the column where maxsum was found */
	printf("Running maxsumdp\n");                      /* Print message indicating that the process has started */
	if ((parmatr = malloc(n*sizeof(int *))) == NULL) { /* Allocate memory for the memory matrix, and terminate the program with an error if memory allocation fails, using the "exit" function, as we're not in "main" */
		printf("Sorry, cannot allocate memory\n");
		exit(-1);
	}
	for (i = 0 ; i < n ; i++) {                        /* Initialise the memory matrix with negative values, that wll be overwritten by positive values when computed */
		if ((*(parmatr + i) = malloc(m*sizeof(int))) == NULL) {
			printf("Sorry, cannot allocate memory\n");
			exit(-1);
		}
	}
	for (i = 0 ; i < n ; i++) {                        /* Fill the partial sum matrix iteratively, using an equivalent algorithm to the one used in the recursive implementation */
		for (j = 0 ; j < m ; j++) {
			if (i == 0) {
				parmatr[i][j] = matr[i][j];
			}
			else if (j == 0) {
				parmatr[i][j] = matr[i][j] + max(parmatr[i - 1][m - 1], parmatr[i - 1][0], parmatr[i - 1][1]);
			}
			else if (j == (m - 1)) {
				parmatr[i][j] = matr[i][j] + max(parmatr[i - 1][m - 2], parmatr[i - 1][m - 1], parmatr[i - 1][0]);
			}
			else {
				parmatr[i][j] = matr[i][j] + max(parmatr[i - 1][j - 1], parmatr[i - 1][j], parmatr[i - 1][j + 1]);
			}
		}
	}
	for (j = 0 ; j < m ; j++) {                        /* For each column of the matrix */
		if (parmatr[n - 1][j] > maxsum) {
			maxsum = parmatr[n - 1][j];        /* Store the greatest sum found down to the bottom */
			max_location = j;                  /* As well as the column on which it was found */
		}
	}
	printf("Max sum is %d\n", maxsum);                 /* Print the maximum sum found down to any of the bottom positions */
	#ifdef PATH
	for (i = n - 1, j = max_location ; i > 0 ; i--) {  /* From the location where the maximum sum was found in the bottom of the partial sum matrix going upwards */
		parmatr[i][m - 1] = matr[i][j];            /* Store the equivalent value of the original matrix in the last column of the same row of the partial sum matrix */
		if (j == 0) {                              /* And move to one of the three positions above, the one with the maximum value, with the matrix wrapping around the sides */
			if ((parmatr[i - 1][m - 1] >= parmatr[i - 1][0]) && (parmatr[i - 1][m - 1] >= parmatr[i - 1][1])) {
				j = m - 1;
			}
			else if ((parmatr[i - 1][1] >= parmatr[i - 1][0]) && (parmatr[i - 1][1] >= parmatr[i - 1][m - 1])) {
				j = 1;
			}
		}
		else if (j == m - 1) {
			if ((parmatr[i - 1][m - 2] >= parmatr[i - 1][m - 1]) && (parmatr[i - 1][m - 2] >= parmatr[i - 1][0])) {
				j--;
			}
			else if ((parmatr[i - 1][0] >= parmatr[i - 1][m - 1]) && (parmatr[i - 1][0] >= parmatr[i - 1][m - 2])) {
				j = 0;
			}
		}
		else {
			if ((parmatr[i - 1][j - 1] >= parmatr[i - 1][j]) && (parmatr[i - 1][j - 1] >= parmatr[i - 1][j + 1])) {
				j--;
			}
			else if ((parmatr[i - 1][j + 1] >= parmatr[i - 1][j]) && (parmatr[i - 1][j + 1] >= parmatr[i - 1][j - 1])) {
				j++;
			}
		}
	}
	parmatr[i][m - 1] = matr[i][j];                    /* Print the modified last column of the partial sum matrix from top to bottom, with " -> " in between */
		for (i = 0 ; i < n - 1 ; i++) {
		printf("%d -> ", parmatr[i][m - 1]);
	}
	printf("%d\n", parmatr[n - 1][m - 1]);
	#endif
	for (i = 0 ; i < n ; i++) {                        /* Free the memory allocated for the memory matrix */
		free(*(parmatr + i));
	}
	free(parmatr);
}
