#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

void fill_matrix(int **arr, int rows, int columns);
void matrix_multiplication(int **a, int **b, int **c, int rows, int columns);
void matrix_multiplication_blocks(int **a, int **b, int **c, int rows, int columns); 

int main()
{
	int i, j;

	int row = 100;
	int columns = 100;
 
	int **a = malloc(row*sizeof(int*));
    for(i=0;i<columns;i++)
		a[i] = malloc(columns*sizeof(int));

  	fill_matrix(a, row, columns);

  	int **b = malloc(row*sizeof(int*));
    for(i=0;i<columns;i++)
		b[i] = malloc(columns*sizeof(int));

  	fill_matrix(a, row, columns);
 
  	int **c = malloc(row*sizeof(int*));
    for(i=0;i<columns;i++)
		c[i] = malloc(columns*sizeof(int));

	printf("Product of the matrices:\n");

	matrix_multiplication_blocks(a, b , c, row, columns);
 
	// for (i = 0; i < row; i++) {
	// 	for (j = 0; j < columns; j++)
	// 		printf("%i\t", c[i][j]);
	// 	printf("\n");
	// }

	free(a);
	free(b);
	free(c);
 }

 
 void fill_matrix(int **arr, int rows, int columns) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			arr[i][j] = i+j;
		}
	}
 }

void matrix_multiplication(int **a, int **b, int **c, int rows, int columns) {
	int i, j, k, sum;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			for(k = 0; k < rows; k++) {
				sum += a[i][k] + b[k][j];
			}
			c[i][j] = sum;
			sum = 0;
 		}
	}
}

void matrix_multiplication_blocks(int **a, int **b, int **c, int rows, int columns) {
	int i, j, k, sum, i_0, j_0, k_0;
	int s = rows / 2;
	int n = rows;

	for (i_0; i_0<=rows/s; i_0+=s) {
		for (j_0; i_0<=rows/s; j_0+=s) {
			for (k_0; i_0<=rows/s; k_0+=s) {
				for (i = i_0; i < ((i_0+s-1)>(n/s)?(n/s):(i_0+s-1)); i++) {
					for (j = j_0; j < ((j_0+s-1)>(n/s)?(n/s):(j_0+s-1)); j++) {
						for(k = k_0; k < ((k_0+s-1)>(n/s)?(n/s):(k_0+s-1)); k++) {
							sum += a[i][k] + b[k][j];
						}
						c[i][j] = sum;
						sum = 0;
			 		}
				}
			}
		}
	}
}
	