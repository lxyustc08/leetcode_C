#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a[] = {1, 2, 3, 4};
    printf("%ld\n",sizeof(a));
    printf("the length of array a is %ld\n", sizeof(a)/sizeof(a[1]));
    return 0;
}
