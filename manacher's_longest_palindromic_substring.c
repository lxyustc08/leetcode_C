/*
 * manacher's algorithm to solve longest palindromic substring
 * the time complexity is O(n)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

#define MIN(a, b) \
    (a) > (b) ? (b) : (a)

//使用manacher's algorithm寻找最长回文子串
char *longestPalindrome(char * s){
    // 输出字符串

    int input_length = strlen(s);
    int LPS_length = 2 * input_length + 1;
    int LPS_array[LPS_length];

    char *output = (char *)malloc(sizeof(char) * (input_length + 1));
    memset(output, '\0', input_length + 1);
    if(s[0] == '\0')
        return output;
    

    //cp: centerposition，已知LPS的位置点
    //clp: centerLeftPosition, 已知LPS的位置的左侧点
    //crp: centerRightPosition, 已知LPS的位置的右侧点
    //new_cp: 新的centerposition
    int cp, clp, crp;
    cp = clp = crp = 0;
    LPS_array[cp] = 0;

    for(int index = 1; index != LPS_length; ++index){
        LPS_array[index] = 0;

        clp = cp - LPS_array[cp];
        crp = cp + LPS_array[cp];

        int mirror_index = 2 * cp - index;

        int Diff;
        Diff = crp - index;
        if(Diff > 0)
            LPS_array[index] = MIN(LPS_array[mirror_index], Diff);
        
        int k = LPS_array[index] + 1;
        while((index - k >= 0 && index + k <= LPS_length - 1) 
            && (((index - k ) % 2 == 0) || s[(index - k + 1) / 2 - 1] == s[(index + k + 1) / 2 - 1])){
            LPS_array[index]++;
            k++;
        }
        if(index + LPS_array[index] > crp)
            cp = index;
    }
    

    //寻找LPS_array中的最大值
    int max, max_index;
    max = max_index = 0;
    for(int index = 0; index != LPS_length; ++index){
        if(LPS_array[index] > max){
            max_index = index;
            max = LPS_array[index];
        }
    }

    //原始字符串的开始结束位置
    int pos_start;
    pos_start = (max_index - max) / 2;

    memcpy(output, s + pos_start, max);

    return output;
}

int main(){
    char *s = "abcbac";
    char *p = longestPalindrome(s);
    /*
    printf("%s\n", position);
    int index = 0;
    while(position[index] != '\0'){
        printf("%d ", LPS_array[index]);
        index ++;
    }
    */
    printf("%s\n", p);
    return 0;
}
