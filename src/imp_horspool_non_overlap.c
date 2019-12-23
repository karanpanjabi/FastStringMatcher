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

#define WS(x) ((ws) x)

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
    int *table = (int *)malloc(256 * sizeof(int));

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
void horspool_matcher(char *text, int n, char *pattern, int m)
{
    int found = -1;

    int *badsym = badsymbolshift(pattern, m);

    // int *goodsuff = (int *) malloc((m+2)*sizeof(int));
    // suffixtable(pattern, m, goodsuff);

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
            printf("%d ", i-m+1);
            found = 1;
            i += m;
            continue;
        }
        else
        {
            i = i+badsym[text[i]];
        }
        
    }

    free(badsym);
    // free(goodsuff);

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("\n");
    
    
}

// finds the number of chars that have matched from right
int getmatchedchars(ws num)
{
    static ws low_7 = WS(1);
    static ws high_7 = (WS(1) << 8) - 1;

    static ws low_6 = WS(1) << 8;
    static ws high_6 = (WS(1) << 16) - 1;

    static ws low_5 = WS(1) << 16;
    static ws high_5 = (WS(1) << 24) - 1;

    static ws low_4 = WS(1) << 24;
    static ws high_4 = (WS(1) << 32) - 1;

    static ws low_3 = WS(1) << 32;
    static ws high_3 = (WS(1) << 40) - 1;

    static ws low_2 = WS(1) << 40;
    static ws high_2 = (WS(1) << 48) - 1;

    static ws low_1 = WS(1) << 48;
    static ws high_1 = (WS(1) << 56) - 1;
    

    if(num == 0)
        return sizeof(ws);
    else if(num >= low_7 && num <= high_7)
        return 7;
    else if(num >= low_6 && num <= high_6)
        return 6;
    else if(num >= low_5 && num <= high_5)
        return 5;  
    else if(num >= low_4 && num <= high_4)
        return 4; 
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
    int charleft = m;
    int charmatched = 0;

    static int wsbytes = sizeof(ws);

    while(charleft > 0)
    {
        // read charleft - ws .. charleft - 1
        int spos = charleft - wsbytes;

        if(spos >= 0)
        {
            ws p = *(ws *) (pattern + spos);
            ws t = *(ws *) (&text[i - (m-1)] + spos);

            int k = getmatchedchars(p^t);

            if(k == wsbytes)
            {
                charleft -= wsbytes;
                charmatched += wsbytes;
            }
            else
            {
                charleft -= k;
                charmatched += k;
                break;
            }
            
        }
        else
        {
            // number of chars left to be matched is less than wordsize
            ws p = 0;
            ws t = 0;

            memcpy(((char *) &p) + (wsbytes - charleft), pattern, charleft);
            memcpy(((char *) &t) + (wsbytes - charleft), text + (i - (m-1)), charleft);

            int k = getmatchedchars(p^t);

            if(k >= charleft)
            {
                charmatched += charleft;
                charleft = 0;
            }
            else
            {
                charmatched += k;
                charleft -= k;
                break;
            }  
        }
    }

    return charmatched;
}

void horspool_matcher_imp(char *text, int n, char *pattern, int m)
{
    int found = -1;

    int *badsym = badsymbolshift(pattern, m);

    int i = m - 1;
    int k;

    while (i <= n - 1)
    {
        k = 0;

        // check how much of the m characters match from the end and store in k

        k = get_matched_amt(pattern, text, m, n, i);

        // i = i - k;
        if(k == m)
        {
            printf("%d ", i-m+1);
            found = 1;
            i += m;
            continue;
        }
        else
        {
            i = i + badsym[text[i]];    // using horspools logic
        }
         
    }

    free(badsym);
    // free(goodsuff);

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

        // horspool_matcher(text, tlen, pattern, plen);
        horspool_matcher_imp(text, tlen, pattern, plen);
    }

    free(pattern);
    free(text);
}


// int main(int argc, char const *argv[])
// {
    
//     printf("%d\n", get_matched_amt("kbcdefghi", "abcdefghijkl", 9, 12, 8));

//     return 0;
// }
