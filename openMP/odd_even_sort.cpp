#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <iostream>

using namespace std;

const int rand_max_value = 100;
int n_threads;

void odd_even_sort(int* a, int n);
void odd_even_sort_1(int* a, int n);
void odd_even_sort_2(int* a, int n);

void create_random_list(int* a, int n);
void print_list(int* a, int n);

int main(int argc, char* argv[]) {

   double start, finish;
   n_threads = strtol(argv[1], NULL, 10);
   int n_elements = strtol(argv[2], NULL, 10);


   int tests_threads[6] = {1, 2, 3, 4, 8, 16};

   for (int i = 0; i < 6; ++i) {
      n_threads = tests_threads[i];
      int* a = (int*) malloc(n_elements*sizeof(int));

      create_random_list(a, n_elements);
      start = omp_get_wtime();
      odd_even_sort_2(a, n_elements);
      finish = omp_get_wtime();

      cout << "Time: " << finish-start << " seconds"<<endl;

      free(a);
   }

   return 0;
}

void print_list(int a[], int n) {
   for (int i = 0; i < n; i++)
      cout << a[i] << ' ';
   cout << endl;
}


void create_random_list(int a[], int n) {
   int i;
   srandom(0);
   for (i = 0; i < n; i++)
      a[i] = random() % rand_max_value;
}

void odd_even_sort(
      int  a[]  /* in/out */, 
      int  n    /* in     */) {
   int phase, i, temp;

   for (phase = 0; phase < n; phase++) 
      if (phase % 2 == 0) { /* Even phase */
         for (i = 1; i < n; i += 2) 
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
            }
      } else { /* Odd phase */
         for (i = 1; i < n-1; i += 2)
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
            }
      }
}

void odd_even_sort_1(int a[], int n) {
   int phase, i, tmp;

   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
#        pragma omp parallel for num_threads(n_threads) \
            default(none) shared(a, n) private(i, tmp)
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
#        pragma omp parallel for num_threads(n_threads) \
            default(none) shared(a, n) private(i, tmp)
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
}

void odd_even_sort_2(int a[], int n) {
   int phase, i, tmp;

#  pragma omp parallel num_threads(n_threads) \
      default(none) shared(a, n) private(i, tmp, phase)
   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
#        pragma omp for 
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
#        pragma omp for 
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
}