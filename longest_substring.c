#include <stdlib.h>
#include <stdio.h>

int lengthOfLongestSubstring(char * s){
    //the begin position of substring
    int start_index = 0;
    //the length of substring
    int sub_length = 0;
    
    //the iter of string, from the second one to iter
    int iter_index = 0;
    
    while(s[iter_index] != '\0'){
        int index = 0;
        for(index = start_index; index != iter_index; index++){
            // the character pointed by iter_index is repeated
            if(s[index] == s[iter_index] && iter_index != 0){
                // find a new bigger length value, update length value and 
                //if(sub_length < iter_index - start_index){
                //    sub_length = iter_index - start_index;
                //}
                // update start_index
                start_index = index + 1;
                break;
            }
        }
        // there is no repeat characters
        if (index == iter_index)
        {
            sub_length = sub_length < iter_index - start_index + 1 ? iter_index - start_index + 1: sub_length;
        }
        

        iter_index ++ ;
    }
    
    return sub_length;
}

int main(int agc, char* argv[]){
    char *a = argv[1];

    int length = lengthOfLongestSubstring(a);

    printf("length = %d\n", length);
}