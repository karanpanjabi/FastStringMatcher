#include <stdio.h>
#include <string.h>
#include <inttypes.h>

// __BYTE_ORDER__

#define LITTLE_ENDIAN 1

#if __WORDSIZE == 64
typedef int64_t ws;
#elif __WORDSIZE == 32
typedef int32_t ws;
#endif

#define WS(x) ((ws) x)


// finds the number of chars that have matched from right
int getmatchedpos32(int32_t num)
{
    //works with little endian num ?
    static int32_t low_3 = 1;
    static int32_t high_3 = 255;

    static int32_t low_2 = 1 << 8;
    static int32_t high_2 = (1 << 16) - 1;
    
    static int32_t low_1 = 1 << 16;
    static int32_t high_1 = (1 << 24) - 1;

    if(num == 0)
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

int getmatchedamt_right(ws num)
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

int getmatchedamt_left(ws num)
{
    static int wsbytes = sizeof(ws);
    if(num == 0)
        return wsbytes;
    
    for (int i = wsbytes-1; i >= 1; i--)
    {
        if(num % (WS(1) << (i*8)) == 0)
            return i;
    }
    return 0;
}


int main()
{
    // char *A = "ABCD";
    // char *B = "CCCD";

    // int32_t ai = *(int32_t *) A;
    // int32_t bi = *(int32_t *) B;

    // int32_t x = ai^bi;

    // printf("%d\n", sizeof(int32_t));
    // printf("%u %u\n", ai, bi);
    // printf("%u %d\n", x, getmatchedpos32(x));


    // char *A = "ABCDEFGH";
    // char *B = "KKKDKKGH";

    // ws ai = *(ws *) A;
    // ws bi = *(ws *) B;

    // ws x = ai^bi;

    // printf("%ld\n", sizeof(ws));
    // printf("%lu %lu\n", ai, bi);
    // printf("%lu %d\n", x, getmatchedamt_right(x));
    

    // ws p = 0;

    // char *pat = "ABCDEF";

    // memcpy(((char *) &p) + (8 - 6), pat, 6);

    // printf("%lu\n", p);

    // 00000000 01000111 01000110 01000101 01000100 01000011 01000010 01000001


    char *A = "ABCDEFGH";
    char *B = "AKKKKKKK";

    ws ai = *(ws *) A;
    ws bi = *(ws *) B;

    ws x = ai^bi;

    printf("%ld\n", sizeof(ws));
    printf("%lu %lu\n", ai, bi);
    printf("%lu %d\n", x, getmatchedamt_left(x));
}
