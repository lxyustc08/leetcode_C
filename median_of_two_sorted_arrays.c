#include <stdio.h>
#include <stdlib.h>

/*
 * basic idea，find a position position i in nums1, and a position j in nums2, the i, j will divies the nums1 and nums2 respectly
 * as left and right, the division will fill the condition:
 * 1, len(nums1_left) + len(nums2_left) = len(nums1_right) + len(nums2_right);
 * 2, max(nums1_left and nums2_left) <= min(nums1_right and nums2_right)
 */

/*
 * use binary search to find the position, no recursive
 */ 

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    // use length_long and length_short to indicate the two arrays
    // in whitch length_long points to the longer array, length_short points to the shorter array
    int *length_short, *length_long;
    length_long = length_short = NULL;

    // varable range indicates the search range
    int range = 0;

    // give the value to length_long and length_short
    if(nums1Size > nums2Size){
        length_long = nums1;
        length_short = nums2;
        range = nums2Size;
    }
    else
    {
        length_long = nums2;
        length_short = nums1;
        range = nums1Size;
    }

    
    // use binary search to find the median of two sorted arrays
    // the p_median indicates the result which we want, and the indicates belong to rigth

    int numsTSize = (nums1Size + nums2Size) / 2;//numsTSize indicates the half of sum of array1 and array2
    int pos_start, pos_end, search_i, search_j;
    pos_start = search_i = search_j = pos_end = 0;
    pos_end = range - 1;

    while((search_i = (pos_start + pos_start) / 2) >= 1){
        search_j = numsTSize - search_i;
        if(length_short[search_i - 1] > length_long[search_j]){ // the search_i is too bigger, move forward
            pos_end = search_i;
        }
        else if(length_long[search_j - 1] > length_short[search_i]){ // the search_i is too small, move down
            pos_start = search_i;
        }
    }
}

int main(int argc, char* argv[]){
    int num1[5] = {1, 2, 8, 9 ,10};
    int num2[1] = {4};

    double median = findMedianSortedArrays(num1, 5, num2, 1);
    printf("median = %f\n", median);
}    