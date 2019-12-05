#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <limits.h>

#include <signal.h>

#if __WORDSIZE == 64
typedef int64_t ws;
#elif __WORDSIZE 32
typedef int32_t ws;
#endif

void naive_matcher(char *text, int tlen, char *pattern, int plen)
{
    int found = -1;
    for (int s = 0; s <= tlen - plen; s++)
    {
        int j = 0;
        while(j<plen && pattern[j] == text[s+j])
        {
            j++;
        }

        if(j == plen)
        {
            found = 1;
            // printf("%d ", s);
        }
    }

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("1\n");
    
}

void naive_matcher_imp(char *text, int tlen, char *pattern, int plen)
{
    int found = -1;
    for (int s = 0; s <= tlen - plen; s++)
    {
        // if(s == 1) raise(SIGINT);
        int j = 0;
        int charleft = plen;
        while(j<plen)
        {
            if(charleft == sizeof(ws))
            {
                ws patws = *(ws *) (pattern + j);
                ws tws = *(ws *) (text + s + j);

                if(patws == tws)
                {
                    j += sizeof(ws);
                    charleft -= sizeof(ws);
                }
                else
                {
                    break;
                }
            }
            else if(charleft < sizeof(ws))
            {
                // read charleft number of chars from pattern and text
                ws patws = 0;
                ws tws = 0;

                memcpy(&patws, pattern + j, charleft);
                memcpy(&tws, text + s + j, charleft);

                if(patws == tws)
                {
                    j += charleft;
                    charleft -= charleft;
                }
                else
                {
                    break;
                }
            }
            else
            {
                // read 8 bytes of chars from text and pattern
                ws patws = *(ws *) (pattern + j);
                ws tws = *(ws *) (text + s + j);
                // if all chars match then, increase j by that 8, decrease charleft by 8
                if(patws == tws)
                {
                    j += sizeof(ws);
                    charleft -= sizeof(ws);
                }
                else
                {
                    break;
                }
                
                // else increase shift by 1 (done by for loop)
            }
            
        }

        if(j == plen)
        {
            found = 1;
            // printf("%d ", s);
        }
    }

    if(found == -1)
    {
        printf("-1\n");
        return;
    }
    printf("1\n");
}

int main(int argc, char const *argv[])
{
    char *text = (char *) malloc(((int) 1e8) * sizeof(char));
    scanf("%[^\n]s", text);
    getchar();

    int tlen = strlen(text);

    int t;
    scanf("%d", &t);
    getchar();

    int plen;
    char *pattern = (char *) malloc(((int) 1e6) * sizeof(char));
    for (int tests = 0; tests < t; tests++)
    {
        scanf("%[^\n]s", pattern);
        getchar();

        plen = strlen(pattern);

        naive_matcher_imp(text, tlen, pattern, plen);
        // naive_matcher(text, tlen, pattern, plen);
    }

    free(pattern);
    free(text);
}
