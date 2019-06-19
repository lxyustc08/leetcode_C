#include <stdlib.h>
#include <stdio.h>

//MAX_LENGTH 1000+1，C语言字符串最后一位必须为'\0'
#define MAX_LENGTH 1001

/* 
 * 寻找输入s的最长回文子串，算法思路：
 * 遍历s，将s中的元素视为回文子串生成的种子，计算当前种子可生成的最长子串length，
 * 将length与当前最长回文子串的长度进行比较
 */
char *longestPalindrome(char * s){

    char *substring = (char*)malloc(sizeof(char) * MAX_LENGTH);

    //max_length用于存储当前阶段最大的回文子串长度，pos_start指示回文子串开始位置，pos_end指示回文子串结束位置
    int max_length, max_start, max_end, pos_start, pos_end;
    max_start = max_end = pos_start = pos_end = 0;

    max_length = 0;

    //index用于指示当前搜索位置
    int index = 0;
    //k用于指示种子附近搜索位置
    int k = 0;
    //count记录当前种子的最长回文子串长度
    int count = 0;

    while(s[index] != '\0'){
        //奇数长度的回文串的种子
        count = 1;
        k = 1;
        pos_start = pos_end = index;
        while(index - k >= 0 && s[index + k] != '\0'){
            if(s[index - k] != s[index + k])
                break;
            else
            {
                count += 2;
                pos_start--;
                pos_end++;
            }
            k++;
        }
        if(count > max_length){
            max_length = count;
            max_start = pos_start;
            max_end = pos_end;
        }
        if(s[index] == s[index + 1]){
            //偶数长度的回文串的种子
            k = 1;
            count = 2;
            pos_start = index;
            pos_end = index + 1;
            while(index - k >= 0 && s[index + 1 + 1] != '\0'){
                if(s[index - k] != s[index + 1 + k])
                    break;
                else
                {
                    count += 2;
                    pos_start--;
                    pos_end++;
                }
                k++;
            }
            if(count > max_length){
                max_length = count;
                max_start = pos_start;
                max_end = pos_end;
            }
        }
        index++;
    }

    int index_substring = 0;
    for(int index = max_start; index <= max_end; ++index){
        substring[index_substring] = s[index];
        index_substring++;
    }
    substring[index_substring] = '\0';
    return substring;
}

int main(){
    char *s = "";
    char *o = longestPalindrome(s);
    printf("%s\n", o);
}