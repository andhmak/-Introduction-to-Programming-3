/* File: maxsumrec.c */

#include <stdio.h>

int max(int a, int b, int c);                 /*"Max" declaration. Full implementation in "maxsum.c" (main).*/

int Sij(int m, int **matr, int i, int j) {    /* (m: columns, **matr: matrix, i, j: coordinates) Recursive function returning the maximum possible sum down to the position with the given coordinates */
	if (i == 0) {                         /* If the position is on the first line*/
		return matr[0][j];            /* Then the maximum sum is equal to its content */
	}
	                                      /* Else it is equal to its content plus the greatest maximum sum down to the 3 positions above (with the matrix folding around the sides) */
	else if (j == 0) {                    /* In case it's on the left edge */
		return matr[i][0] + max(Sij(m, matr, i - 1, m - 1), Sij(m, matr, i - 1, 0), Sij(m, matr, i - 1, 1));
	}
	else if (j == (m - 1)) {              /* In case it's on the right edge */
		return matr[i][j] + max(Sij(m, matr, i - 1, m - 2), Sij(m, matr, i - 1, m - 1), Sij(m, matr, i - 1, 0));
	}
	else {                                /* In case it's not on the edge */
		return matr[i][j] + max(Sij(m, matr, i - 1, j - 1), Sij(m, matr, i - 1, j), Sij(m, matr, i - 1, j + 1));
	}
}

void solve(int n, int m, int **matr) {        /* The "solve" function taking a matrix and its dimensions as inputs and printing the maximum printing sum */
	int sum = 0, maxsum = 0, j;           /* sum: maximum sum down to the current position, maxsum: the maximum value of "sum", j: current matrix column*/
	printf("Running maxsumrec\n");        /* Print message indicating that the process has started */
	for (j = 0 ; j < m; j++) {            /* For each column of the matrix */
		sum = Sij(m, matr, n - 1, j); /* Count the maximum sum down to the bottom position */
		if (sum > maxsum) {           /* Store the greatest value found */
			maxsum = sum;
		}
	}
	printf("Max sum is %d\n", maxsum);    /* Print the maximum sum found down to any of the bottom positions */
}
