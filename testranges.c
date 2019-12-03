#include <stdio.h>

typedef unsigned int int32;

#define LITTLE_ENDIAN 1

int getmatchedpos(int32 num)
{
    //works with little endian num ?
    static int32 low_3 = 1;
    static int32 high_3 = 255;

    static int32 low_2 = 1 << 8;
    static int32 high_2 = 255 << 8 | 255;
    
    static int32 low_1 = 1 << 16;
    static int32 high_1 = 255 << 16 | 255 << 8 | 255;

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

int main()
{
    char *A = "ABCD";
    char *B = "CCKD";

    int32 ai = *(int32 *) A;
    int32 bi = *(int32 *) B;

    int32 x = ai^bi;

    printf("%d\n", sizeof(int32));
    printf("%u %u\n", ai, bi);
    printf("%u %d\n", x, getmatchedpos(x));
    
}
