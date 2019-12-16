#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <limits.h>

#include <signal.h>

#if __WORDSIZE == 64
typedef int64_t ws;
#elif __WORDSIZE == 32
typedef int32_t ws;
#endif

int suffixtable(char *p, int m, int *shift)
{

    int r;
    int *f;
    int i, j;

    r = 1;


    f = malloc((m + 1) * sizeof(int));
    if (f == NULL)
    {
        goto ERR_MALLOC_F;
    }

    for (i = 0; i < m; i++)
    {
        f[i] = 0;
        shift[i] = 0;
    }
    f[i] = m + 1;

    i = m;
    j = m + 1;
    f[i] = j;

    while (i > 0)
    {
        while (j <= m && p[i - 1] != p[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = f[j];
        }
        i--;
        j--;
        f[i] = j;
    }

    j = f[0];
    for (i = 0; i <= m; i++)
    {
        if (shift[i] == 0)
            shift[i] = j;

        if (i == j)
            j = f[j];
    }

    r = 0;
    goto SUCCESS;

SUCCESS:

    free(f);
ERR_MALLOC_F:

    return r;
}

int *badsymbolshift(char *p, int m)
{
    int *table = (int *)malloc(256 * sizeof(char));

    for (int i = 0; i < 256; i++)
    {
        table[i] = m;
    }

    for (int j = 0; j <= m - 2; j++)
    {
        table[p[j]] = m - 1 - j;
    }

    return table;
}

// n = len(text), m = len(pattern)
void boyer_matcher(char *text, int n, char *pattern, int m)
{
    int found = -1;

    int *badsym = badsymbolshift(pattern, m);

    int *goodsuff = (int *) malloc((m+2)*sizeof(int));
    suffixtable(pattern, m, goodsuff);

    int i = m - 1;
    int k;

    int d1; int d2;
    while (i <= n - 1)
    {
        k = 0;
        while(k <= m-1 && pattern[m-1-k] == text[i-k])
        {
            k++;
        }
        if(k == m)
        {
            // printf("%d ", i-m+1);
            found = 1;
            i++;
            continue;
        }
        
        // shift for mismatching character
        d1 = badsym[text[i-k]] - k;
        if(d1 <= 0)
            d1 = 1;
        
        d2 = goodsuff[m-k];

        // i = i+badsym[text[i]];

        if(k != 0)
            i = i + (d1 > d2 ? d1 : d2);
        else
            i = i + d1;
        
    }

    free(badsym);
    free(goodsuff);

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("1\n");
    
    
}

// finds the number of chars that have matched from right
int getmatchedpos(ws num)
{
    static int wsbytes = sizeof(ws);
    //works with little endian num ?
    static ws low_3 = 1;
    static ws high_3 = 255;

    static ws low_2 = 1 << 8;
    static ws high_2 = (1 << 16) - 1;
    
    static ws low_1 = 1 << 16;
    static ws high_1 = (1 << 24) - 1;

    // indices 7 to 1 are used
    static ws low_arr[sizeof(ws)];
    static ws high_arr[sizeof(ws)];

    for (int i = wsbytes - 1; i >= 1; i--)
    {
        (1 << (wsbytes - (i+1))
        low_arr[i] = 1 << ;
        high_arr[i] = (1 << )
    }
    

    if(num == 0)
        return sizeof(ws);
    else if(num >= low_3 && num <= high_3)
        return 3;
    else if(num >= low_2 && num <= high_2)
        return 2;
    else if(num >= low_1 && num <= high_1)
        return 1;  
    else
        return 0;
}

int get_matched_amt(char *pattern, char *text, int m, int n, int i)
{
    // to check pattern[m-1 .. 0] against text[i .. i - m + 1] in reverse direction

    // read ws blocks of data, the amt of matched chars should be from right to left

}

void boyer_matcher_imp(char *text, int n, char *pattern, int m)
{
    int found = -1;

    int *badsym = badsymbolshift(pattern, m);

    int i = m - 1;
    int k;
    while (i <= n - 1)
    {
        k = 0;

        // check how much of the m characters match from the end and store in k
        while(k <= m-1 && pattern[m-1-k] == text[i-k])
        {
            k++;
        }

        get_matched_amt(pattern, text, m, n, i);


        if(k == m)
        {
            // printf("%d ", i-m+1);
            found = 1;
        }

        i = i + badsym[text[i]];    // using horspools logic for now
    }

    free(badsym);

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("1\n");
    
    
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

        boyer_matcher(text, tlen, pattern, plen);
        // naive_matcher(text, tlen, pattern, plen);
    }

    free(pattern);
    free(text);
}
