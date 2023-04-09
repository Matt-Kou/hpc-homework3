# Homework 3
## OpenMP warm-up

1. The execution time is capped by $\max_{i\in [1,n)}f(i)$.

1. It will be the same

1. It would be much better when $\exists i^*$ s.t. $f(i^*)$ is much slower than others. In that way, during the execution of that $f(i^*)$, other threads would continue to run other $f(i)$ instead of being blocked and wait for $f(i^*)$ to finish.

1. nowait

## Machine Architecture

I am using a intel-cpu windows machine with i9-12900H with 14 cores and 20 logical processors.
