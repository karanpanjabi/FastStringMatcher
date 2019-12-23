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
    for (int q = 1; q <= m-1; q++)
    {
        while (k > 0 && pattern[k] != pattern[q])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[q])
        {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

void kmp_matcher(char *text, int n, char *pattern, int m)
{
    int found = -1;
    int *pi = compute_prefix_function(pattern, m);

    int q = 0;
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = pi[q-1];
        }
        if(pattern[q] == text[i])
        {
            q++;
        }
        if (q == m)
        {
            printf("%d ", i-m+1);
            found = 1;
            q = pi[q-1];
        }
        
        
    }

    free(pi);

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("\n");
    
}

int main(int argc, char const *argv[])
{
    char *text = (char *)malloc(((int)1e8) * sizeof(char));
    scanf("%[^\n]s", text);
    getchar();

    int tlen = strlen(text);

    int t;
    scanf("%d", &t);
    getchar();

    int plen;
    char *pattern = (char *)malloc(((int)1e6) * sizeof(char));
    for (int tests = 0; tests < t; tests++)
    {
        scanf("%[^\n]s", pattern);
        getchar();

        plen = strlen(pattern);

        kmp_matcher(text, tlen, pattern, plen);
        // kmp_matcher_imp(text, tlen, pattern, plen);
    }

    free(pattern);
    free(text);
}

