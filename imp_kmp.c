#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <limits.h>

#include <signal.h>

#if __WORDSIZE == 32
typedef int64_t ws;
#elif __WORDSIZE == 64
typedef int32_t ws;
#endif


// processing the pattern
int *compute_prefix_function(char *pattern, int patlen)
{
    int m = patlen;
    int *pi = (int *)malloc((m + 1) * sizeof(int));     // computing the pi table

    pi[0] = 0;
    int k = 0;
    for (int q = 2; q <= m; q++)
    {
        while (k > 0 && pattern[k + 1] != pattern[q])
        {
            k = pi[k];
        }
        if (pattern[k+1] == pattern[q])
        {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

