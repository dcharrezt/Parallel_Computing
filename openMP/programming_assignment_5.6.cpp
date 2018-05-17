#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	long thread_count;
	int i, iters;

	thread_count = strtol(argv[1], NULL, 10);

	printf("Iterations: ");
	scanf("%d", &iters);
	printf("\n");
	double * a = (double *)malloc(iters* sizeof(double));

	# pragma omp parallel num_threads(thread_count)

		# pragma omp for

			for (i = 0; i < iters; ++i) {
				printf("Thread %d - Iterations %d\n", omp_get_thread_num(), i);
			}

	for (i = 0; i < iters; i++)
		a[i] = i * (i + 1) / 2;

	#pragma omp parallel for num_threads(thread_count) \
 		default(none) private(i) shared(a, iters)
	for (i = 0; i < iters; i++)
		a[i] = i * (i + 1) / 2;

	free(a);
	return 0;
}