/* File: maxsummem.c */

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b, int c);                                   /* "Max" declaration. Full implementation in "maxsum.c" (main). */

int Sij(int m, int **matr, int i, int j, int **memmatr) {       /* Equivalent to the "Sij" in the recursive implementation, but it also uses the memory matrix */
	if (memmatr[i][j] == -1) {                              /* If the maximum sum down to a certain pasition hasn't been calculated yet, use the recursive algorithm, and store it in the memory matrix */
		if (i == 0) {
			return memmatr[i][j] = matr[0][j];
		}
		else if (j == 0) {
			return memmatr[i][j] = matr[i][0] + max(memmatr[i][j] = Sij(m, matr, i - 1, m - 1, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, 0, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, 1, memmatr));
		}
		else if (j == (m - 1)) {
			return memmatr[i][j] = matr[i][j] + max(memmatr[i][j] = Sij(m, matr, i - 1, m - 2, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, m - 1, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, 0, memmatr));
		}
		else {
			return memmatr[i][j] = matr[i][j] + max(memmatr[i][j] = Sij(m, matr, i - 1, j - 1, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, j, memmatr), memmatr[i][j] = Sij(m, matr, i - 1, j + 1, memmatr));
		}
	}
	else {                                                  /* Else, use the result from the memory matrix */
		return memmatr[i][j];
	}
}

int solve(int n, int m, int **matr) {                           /* The "solve" function taking a matrix and its dimensions as inputs and printing the maximum possible sum */
	int **memmatr, sum = 0, maxsum = 0, i, j, max_location; /* memmatr: partial sum memory matrix, sum: maximum sum down to the current position, maxsum: the maximum value of "sum", i/j: coordinates, max_location: the column where maxsum was found */
	printf("Running maxsummem\n");                          /* Print message indicating that the process has started */
	if ((memmatr = malloc(n*sizeof(int *))) == NULL) {      /* Allocate memory for the memory matrix, and terminate the program with an error if memory allocation fails, using the "exit" function, as we're not in "main" */
		printf("Sorry, cannot allocate memory\n");
		exit(-1);
	}
	for (i = 0 ; i < n ; i++) {
		if ((*(memmatr + i) = malloc(m*sizeof(int))) == NULL) {
			printf("Sorry, cannot allocate memory\n");
			exit(-1);
		}
	}
	for (i = 0 ; i < n ; i++) {                             /* Initialise the memory matrix with negative values, which wll be overwritten by positive values when computed */
		for (j = 0 ; j < m ; j++) {
			memmatr[i][j] = -1;
		}
	}
	for (j = 0 ; j < m; j++) {                              /* For each column of the matrix */
		sum = Sij(m, matr, n - 1, j, memmatr);          /* Count the maximum sum down to the bottom position */
		if (sum > maxsum) {
			maxsum = sum;                           /* Store the greatest sum found down to the bottom */
			max_location = j;                       /* As well as the column on which it was found */
		}
	}
	printf("Max sum is %d\n", maxsum);                      /* Print the maximum sum found down to any of the bottom positions */
	#ifdef PATH                                             /* If PATH is defined */
	for (i = n - 1, j = max_location ; i > 0 ; i--) {       /* From the location where the maximum sum was found in the bottom of the partial sum matrix going upwards */
		memmatr[i][m - 1] = matr[i][j];                 /* Store the equivalent value of the original matrix in the last column of the same row of the memory matrix */
		if (j == 0) {                                   /* And move to one of the three positions above, the one with the maximum value, with the matrix wrapping around the sides */
			if ((memmatr[i - 1][m - 1] >= memmatr[i - 1][0]) && (memmatr[i - 1][m - 1] >= memmatr[i - 1][1])) {
				j = m - 1;
			}
			else if ((memmatr[i - 1][1] >= memmatr[i - 1][0]) && (memmatr[i - 1][1] >= memmatr[i - 1][m - 1])) {
				j = 1;
			}
		}
		else if (j == m - 1) {
			if ((memmatr[i - 1][m - 2] >= memmatr[i - 1][m - 1]) && (memmatr[i - 1][m - 2] >= memmatr[i - 1][0])) {
				j--;
			}
			else if ((memmatr[i - 1][0] >= memmatr[i - 1][m - 1]) && (memmatr[i - 1][0] >= memmatr[i - 1][m - 2])) {
				j = 0;
			}
		}
		else {
			if ((memmatr[i - 1][j - 1] >= memmatr[i - 1][j]) && (memmatr[i - 1][j - 1] >= memmatr[i - 1][j + 1])) {
				j--;
			}
			else if ((memmatr[i - 1][j + 1] >= memmatr[i - 1][j]) && (memmatr[i - 1][j + 1] >= memmatr[i - 1][j - 1])) {
				j++;
			}
		}
	}
	memmatr[i][m - 1] = matr[i][j];                         /* Print the modified last column of the memory matrix from top to bottom, with " -> " in between */
	for (i = 0 ; i < n - 1 ; i++) {
		printf("%d -> ", memmatr[i][m - 1]);
	}
	printf("%d\n", memmatr[n - 1][m - 1]);
	#endif
	for (i = 0 ; i < n ; i++) {                             /* Free the memory allocated for the memory matrix */
		free(*(memmatr + i));
	}
	free(memmatr);
}
