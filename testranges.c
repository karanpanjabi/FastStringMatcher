#include <stdio.h>

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
// int getmatchedpos(int32 num)
// {
//     //works with little endian num ?
//     static int32 low_3 = 1;
//     static int32 high_3 = 255;

//     static int32 low_2 = 1 << 8;
//     static int32 high_2 = (1 << 16) - 1;
    
//     static int32 low_1 = 1 << 16;
//     static int32 high_1 = (1 << 24) - 1;

//     if(num == 0)
//         return 4;
//     else if(num >= low_3 && num <= high_3)
//         return 3;
//     else if(num >= low_2 && num <= high_2)
//         return 2;
//     else if(num >= low_1 && num <= high_1)
//         return 1;  
//     else
//         return 0;
// }

int getmatchedpos(ws num)
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


int main()
{
    // char *A = "ABCD";
    // char *B = "CCCD";

    // int32 ai = *(int32 *) A;
    // int32 bi = *(int32 *) B;

    // int32 x = ai^bi;

    // printf("%d\n", sizeof(int32));
    // printf("%u %u\n", ai, bi);
    // printf("%u %d\n", x, getmatchedpos(x));

    char *A = "ABCDEFGH";
    char *B = "KKKDKKGH";

    ws ai = *(ws *) A;
    ws bi = *(ws *) B;

    ws x = ai^bi;

    printf("%ld\n", sizeof(ws));
    printf("%lu %lu\n", ai, bi);
    printf("%lu %d\n", x, getmatchedpos(x));
    
}
