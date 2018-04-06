// - Implementar y comparar los 2-bucles anidados FOR presentados en el cap. 2 del libro, pag 22.
// - Implementar en C/C++ la multiplicación de matrices clásica, la versión de tres bucles anidados y evaluar su desempeño considerando el tamaño de las matrices.
// - Implementar la version por bloques, seis bloques anidados, evaluar su desempeño y compararlo con la multiplicación de matrices clásica.
// - Ejecutar ambos algoritmos paso a paso, y analisar el movimiento de datos entre la memoria principal y la memoria cache. Hacer una evaluación de acuerdo a la complejidad algoritmica.
// - Ejecutar ambos algoritmos utilizando las herramientas valgrind y kcachegrind para obtener una evaluación mas precisa de su desempeño en términos de cache misses.


// valgrind --leak-check=yes ./a.out
// valgrind --tool=callgrind ./a.out

#include <stdio.h>
// #include <mpi.h>

typedef double DD;
typedef float FF;
typedef int II;

#define MAX 4

void first_loops();
void second_loops();

void matrix_multiplicacion();
void matrix_multiplicacion_blocks();


DD A[MAX][MAX] = { {1.5, 1.9, 3.2, 4.5}, {2.3, 4.5, 6.8, 7.3}, 
					{8.5, 9.6, 1.2, 4.3}, {5.7, 6.6, 2.4, 8.6} };
DD x[MAX] = {1.1, 3.2, 2.8, 4.6};
DD y[MAX] = {0};
DD z[MAX] = {0};


int main() {

	int i,j;

	printf("A:\n");
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			printf("%f\t", A[i][j]);
		}
		printf("\n");
	}

	printf("X:\n");
	for (i = 0; i < MAX; ++i)
	{
		printf("%f\n", x[i]);
	}

	printf("Y:\n");
	for (i = 0; i < MAX; ++i)
	{
		printf("%f\n", y[i]);
	}

	printf("Z:\n");
	for (i = 0; i < MAX; ++i)
	{
		printf("%f\n", z[i]);
	}

	// first_loops();

	// printf("Y:\n");
	// for (i = 0; i < MAX; ++i)
	// {
	// 	printf("%f\n", y[i]);
	// }

	second_loops();
	printf("Z:\n");
	for (i = 0; i < MAX; ++i)
	{
		printf("%f\n", z[i]);
	}


    return 0;
}


void first_loops() {
	int i, j;
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			y[i] += A[i][j]*x[j];
		}
	}
}

void second_loops() {
	int i, j;
	for (j = 0; j < MAX; ++j)
	{
		for (i = 0; i < MAX; ++i)
		{
			z[i] += A[i][j]*x[j];
		}
	}
}

void matrix_multiplicacion();
void matrix_multiplicacion_blocks();