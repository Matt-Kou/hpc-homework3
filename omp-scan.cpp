#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// Scan A array and write result into prefix_sum array;
// use long data type to avoid overflow
void scan_seq(long *prefix_sum, const long *A, long n)
{
  if (n == 0)
    return;
  prefix_sum[0] = 0;
  for (long i = 1; i < n; i++)
  {
    prefix_sum[i] = prefix_sum[i - 1] + A[i - 1];
  }
}

void scan_omp(long *prefix_sum, const long *A, long n)
{
  int p;
  long cell_group;
  if (n == 0)
    return;
#pragma omp parallel
  {
    p = omp_get_num_threads();
    cell_group = (n + p - 1) / p; // ceil(n/p)
    int t = omp_get_thread_num();
    // Fill out parallel scan: One way to do this is array into p chunks
    // Do a scan in parallel on each chunk, then share/compute the offset
    // through a shared vector and update each chunk by adding the offset
    // in parallel
    int start = t * cell_group;
    int end = (t == p - 1) ? n : (t + 1) * cell_group;
    if (start == 0)
    {
      prefix_sum[start] = 0;
    }
    else
    {
      prefix_sum[start] = A[start - 1];
    }

    for (long i = start + 1; i < end; i++)
    {
      prefix_sum[i] = prefix_sum[i - 1] + A[i - 1];
    }
  }
#pragma omp parallel
  {
    int t = omp_get_thread_num();
    long v = 0;
    for (long i = 0; i < t; i += 1)
    {
      v += prefix_sum[(i + 1) * cell_group - 1];
    }
# pragma omp barrier
    int start = t * cell_group;
    int end = (t == p - 1) ? n : (t + 1) * cell_group;
    for (long i = start; i < end; i++)
    {
      prefix_sum[i] += v;
    }
  }
}

int main()
{
  long N = 100000000;
  long *A = (long *)malloc(N * sizeof(long));
  long *B0 = (long *)malloc(N * sizeof(long));
  long *B1 = (long *)malloc(N * sizeof(long));
  for (long i = 0; i < N; i++)
    A[i] = rand();
  for (long i = 0; i < N; i++)
    B1[i] = 0;

  double tt = omp_get_wtime();
  scan_seq(B0, A, N);
  printf("sequential-scan = %fs\n", omp_get_wtime() - tt);

  tt = omp_get_wtime();
  scan_omp(B1, A, N);
  printf("parallel-scan   = %fs\n", omp_get_wtime() - tt);

  long err = 0;
  for (long i = 0; i < N; i++)
    err = std::max(err, std::abs(B0[i] - B1[i]));
  printf("error = %ld\n", err);

  free(A);
  free(B0);
  free(B1);
  return 0;
}
