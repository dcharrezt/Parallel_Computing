#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <iostream>

using namespace std;

void mat_vect_mult(double matrix[], double vect[], double res[],
      						int rows, int cols, int n_threads);

void create_matrix(double matrix[], int rows, int cols);
void create_vector(double vect[], int size);

void print_matrix(double matrix[], int rows, int cols);
void print_vector(double* vect, double size);

int main(int argc, char** argv) {

	double* matrix;
	double* vect;
	double* res;

	int n_threads = strtol(argv[1], NULL, 10);
	int rows = strtol(argv[2], NULL, 10);
	int cols = strtol(argv[3], NULL, 10);

	matrix = (double*) malloc(rows*cols*sizeof(double));
	vect = (double*) malloc(cols*sizeof(double));
	res = (double*) malloc(rows*sizeof(double));

	create_matrix(matrix, rows, cols);
	create_vector(vect, cols);

	mat_vect_mult(matrix, vect, res, rows, cols, n_threads);

  /*  int tests_threads[5] = {1, 2, 4, 8, 16};
   for (int i = 0; i < 5; ++i) {

		n_threads = tests_threads[i];

		matrix = (double*) malloc(rows*cols*sizeof(double));
		vect = (double*) malloc(cols*sizeof(double));
		res = (double*) malloc(rows*sizeof(double));

		create_matrix(matrix, rows, cols);
		create_vector(vect, cols);

		mat_vect_mult(matrix, vect, res, rows, cols, n_threads);

		free(matrix);
		free(vect);
		free(res);
	} */

	free(matrix);
	free(vect);
	free(res);	


	return 0;
}


void mat_vect_mult(double matrix[], double vect[], double res[],
      						int rows, int cols, int n_threads) {

	int i, j;
	double start, finish;
	start = omp_get_wtime();
	#  pragma omp parallel for num_threads(n_threads)  \
	  	default(none) private(i, j)  shared(matrix, vect, res, rows, cols)
	for ( i = 0; i < rows; i++) {
	  res[i] = 0.0;
	  for ( j = 0; j < cols; j++)
	     res[i] += matrix[i*cols+j]*vect[j];
	}
	finish = omp_get_wtime();
	cout << "Time: " <<  finish - start << " seconds" << endl;
} 

void create_matrix(double matrix[], int rows, int cols) {
   int i, j;
   for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
         matrix[i*cols+j] = random()/((double) RAND_MAX);
}

void create_vector(double vect[], int size) {
   for (int i = 0; i < size; i++)
      vect[i] = random()/((double) RAND_MAX);
}

void print_matrix(double matrix[], int rows, int cols) {
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++)
        cout << matrix[i*cols + j] << ' ';
      cout << endl;
   }
}

void print_vector(double* vect, double size) {
   for (int i = 0; i < size; i++)
      cout << vect[i] << ' ';
   cout << endl;
}
