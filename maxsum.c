/* File: maxsum.c */

#include <stdio.h>
#include <stdlib.h>
#include "solve.h"                           /*Header containing the declaration of the "solve" function*/

int max(int a, int b, int c) {               /*"Max" function with 3 inputs, to be used in all the variations of "solve"*/
	if ((a >= b) && (a >= c)) {
		return a;
	}
	if ((b >= a) && (b >= c)) {
		return b;
	}
	if ((c >= a) && (c >= b)) {
		return c;
	}
}

int main(void) {
	int n, m, **matr, i, j;                         /* n: amount of lines, m: amount of columns, **matr: matrix to be solved, i/j: current matrix row/column */
	scanf("%d%d", &n, &m);                          /* Read the size of the matrix */
	if ((matr = malloc(n*sizeof(int *))) == NULL) { /* Allocate memory for the matrix in the heap, and exit with an error if memory allocation fails */
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	for (i = 0 ; i < n ; i++) {
		if ((*(matr + i) = malloc(m*sizeof(int))) == NULL) {
			printf("Sorry, cannot allocate memory\n");
			return -1;
		}
	}
	for (i = 0 ; i < n ; i++) {                     /* Initialise the matrix with input data */
		for (j = 0 ; j < m ; j++) {
			scanf("%d", &(matr[i][j]));
		}
	}
	solve(n, m, matr);                              /* Call the function to "solve" the matrix */
	for (i = 0 ; i < n ; i++) {                     /* Free the memory allocated for the matrix */
		free(*(matr + i));
	}
	free(matr);
	return 0;
}
