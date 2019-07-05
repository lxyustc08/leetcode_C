#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 12

static char* range="2147483648";

int reverse(int x){
    char *str_tmp = (char *)malloc(sizeof(char) * LENGTH);
    memset(str_tmp, '\0', LENGTH);

    sprintf(str_tmp, "%d", x);

    int bits_length = 0;
    bits_length = strlen(str_tmp);
    
    //标志位，标识逆序后的结果是否溢出
    int overflow = 0;

    //交换的中间位置
    int half_index = 0;
    //开始交换的起始位置
    int begin_index = 0;
    //交换位置的和
    int sum_change = 0;

    if(x >= 0){
        half_index = (bits_length - 1) / 2;
        begin_index = 0;
        sum_change = bits_length - 1;
    }
    else{
        half_index = bits_length / 2;
        begin_index = 1;
        sum_change = bits_length;
    }

    for(int index = begin_index; index <= half_index; ++index){
        char tmp = str_tmp[index];
        str_tmp[index] = str_tmp[sum_change - index];
        str_tmp[sum_change - index] = tmp;
    }

    if((bits_length == 10 && x >= 0) || (bits_length == 11 && x < 0)){
        int index = begin_index;
        int range_index = 0;
        while(index != bits_length && overflow != 1){
            if(str_tmp[index] > range[range_index]){
                overflow = 1;
                break;
            } else if(str_tmp[index] < range[range_index])
            {
                overflow = 0;
                break;
            }
            index++;
            range_index++;
        }
    }
    if(overflow == 1)
        return 0;
    else
        return atoi(str_tmp);
}

int main(int argc, char* argv[]){
    int input = atoi(argv[1]);
    printf("%d\n", reverse(input));
    return 0;
}