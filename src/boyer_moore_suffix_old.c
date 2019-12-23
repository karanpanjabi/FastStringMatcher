#include <stdlib.h>
#include <string.h>


#define DEBUG_SUFFIXTABLE 1

#if DEBUG_SUFFIXTABLE
#  define PATTERN_LEN 10
#  include <stdio.h>
#endif

int* badsymbolshift(char *p, int m)
{
    int *table = (int *) malloc(256*sizeof(char));

    for (int i = 0; i < 256; i++)
    {
        table[i] = m;
    }

    for (int j = 0; j <= m-2; j++)
    {
        table[p[j]] = m - 1 - j;
    }

    return table;
}

int suffixtable(char *p, int *shift)
{

    int r;
    int *f;
    int m;
    int i, j;

    r = 1;

    m = strlen(p);

    f = malloc((m + 1) * sizeof(int));
    if (f == NULL) {
        goto ERR_MALLOC_F;
    }

    for (i = 0; i < m; i++) {
        f[i] = 0;
        shift[i] = 0;
    }
    f[i] = m + 1;

    i = m;
    j = m + 1;
    f[i] = j;

    while (i > 0) {
        while (j <= m && p[i - 1] != p[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = f[j];
        }
        i--;
        j--;
        f[i] = j;
    }

    j = f[0];
    for(i=0; i<=m; i++)
    {
        if(shift[i]==0)
            shift[i] = j;

        if (i==j)
            j = f[j];
    }

    r = 0;
    goto SUCCESS;

    SUCCESS:

        free(f);
    ERR_MALLOC_F:

    return r;

}


#if DEBUG_SUFFIXTABLE
int main(void)
{

    char pat[PATTERN_LEN];
    int shift[PATTERN_LEN];
    int i;

    scanf("%s", pat);

    suffixtable(pat, shift);

    int *badsym = badsymbolshift(pat, strlen(pat));

    for (i = 0; i < strlen(pat); i++) {
        printf("%c %d %d\n", pat[i], shift[i], badsym[pat[i]]);
    }

    free(badsym);

    return 0;

}
#endif
