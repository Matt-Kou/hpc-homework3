#if defined(_OPENMP)
#include <omp.h>
#endif
#include <iostream>
#include "utils.h"

#define K 1000
#define N 1000

int main()
{
    // initialize u
    double h = 1. / N;
    double hsq = h * h;
    auto u = new double[N][N]();

    Timer t;
    t.tic();
    // calculate
    for (int k = 0; k < K; k++)
    {
#pragma omp parallel for
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = !(i & 1) + 1; j < N - 1; j += 2)
            {
                u[i][j] = (hsq + u[i - 1][j] + u[i][j - 1] + u[i + 1][j] + u[i][j + 1]) / 4;
            }
        }
#pragma omp parallel for
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = (i & 1) + 1; j < N - 1; j += 2)
            {
                u[i][j] = (hsq + u[i - 1][j] + u[i][j - 1] + u[i + 1][j] + u[i][j + 1]) / 4;
            }
        }
    }
    printf("Time used: %6.4fs\n", t.toc());

    // print the results
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%f\t", u[i][j]);
    //     }
    //     printf("\n");
    // }
}