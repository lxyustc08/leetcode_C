#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BELONG_NUMS(X) \
    (((X) <= '9') && ((X) >= '0'))

#define BELONG_SING(X) \
    ((X) == '-' || (X) == '+')

int myAtoi(char * str){
    int str_length = strlen(str);
    //符号标识位，标识正负
    bool signal = true;

    //转换部分的首末下标
    int start_index, end_index;
    start_index = end_index = -1;

    //标识位，标识是否为队列头部的whitespace
    bool head_whitespace_flag = true;

    //跳过开头空格
    int iter = 0;
    while(str[iter] == ' ')
        iter++;

    //寻找转换部分
    for(int index = iter; index <= str_length; ++index){
        if(BELONG_NUMS(str[index])){
            if(start_index == -1)
                start_index = index;
            continue;
        }
        if(BELONG_SING(str[index])){
            if(!BELONG_NUMS(str[index + 1])){
                end_index = index - 1;
                break;
            }
            else if(index > start_index && start_index != -1){
                end_index = index - 1;
                break;
            }
            else
            {
                start_index = index + 1;
                signal = str[index] == '+' ? true : false;
                continue;
            }
            
        }
        if(!BELONG_NUMS(str[index]) && !BELONG_SING(str[index]))
        {
            end_index = index - 1;
            break;
        }
    }
    int ret = 0;

    if(start_index == -1){
        ret = 0;
        goto end;
    }
    
    int signal_ = signal ? 1 : -1;

    iter = start_index;
    while(str[iter] == '0')
        iter++;
    start_index = iter;
    int num_length = end_index - start_index + 1;
    if(num_length > 10)
        ret = signal ? INT_MAX : INT_MIN;
    else if(num_length <= 10)
    {
        for(int index = start_index; index <= end_index; ++index){
            
            if(ret > INT_MAX / 10 || (ret == INT_MAX / 10 && str[index] > '7')){
                ret = INT_MAX;
                break;
            }
            if(ret < INT_MIN / 10 || (ret == INT_MIN / 10 && str[index] > '8')){
                ret = INT_MIN;
                break;
            }

            ret = ret * 10 + (str[index] - '0') * signal_;
        }
    }
    
end:
    return ret;
}

int main(int argc, char *argv[]){
    char *str_input = argv[1];
    int ret = 0;
    ret = myAtoi(str_input);
    printf("%d\n", ret);
    return 0;
}