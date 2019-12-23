#include <stdlib.h>
#include <string.h>


#define DEBUG_SUFFIXTABLE 1

#if DEBUG_SUFFIXTABLE
#  define PATTERN_LEN 10
#  include <stdio.h>
#endif


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
    for (i = 0; i < m + 1; i++)
    {
        if (shift[i] == 0)
            shift[i] = j;

        if (i == j)
            j = f[j];
    }

    for (i = 1; i < (m / 2) + 1; i++) {
        int temp;
        temp = shift[i];
        shift[i] = shift[m - i];
        shift[m - i] = temp;
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

    for (i = 1; i < strlen(pat); i++) {
        printf("%c %d\n", pat[strlen(pat) - i], shift[i]);
    }

    return 0;

}
#endif
