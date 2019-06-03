#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* function_get()
{
    static __thread int var = 0;
    return &var;
}

void *function_add(void* adder)
{
    int _adder = (int)adder;
    printf("adder is %d\n", _adder);
    int *result = function_get();

    *result += _adder;
    printf("result = %d\n, the address of result is x%xud\n", *result, result);

    return (void*)result;
}

int main()
{
    pthread_t threads[2];
    volatile int index = 0;

    for(index; index != 2; ++index)
    {
        
        pthread_create(threads + index, NULL, function_add, (void*)index);
    }
    
    for(index = 0; index != 2; ++index)
    {
        pthread_join(threads[index], NULL);
    }

    return 0;
}

