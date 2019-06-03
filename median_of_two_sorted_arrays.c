#include <stdio.h>
#include <stdlib.h>

/*
 * basic idea，find a position position i in nums1, and a position j in nums2, the i, j will divies the nums1 and nums2 respectly
 * as left and right, the division will fill the condition:
 * 1, len(nums1_left) + len(nums2_left) = len(nums1_right) + len(nums2_right);
 * 2, max(nums1_left and nums2_left) <= max(nums1_right) + max(nums2_right)
 */

/*
 * use binary search to find the position
 */ 
int find_position(int* nums1, int* nums2, int begin_nums1, int end_nums1, int total_num){
    // get the middle position
    int middle_nums1 = (begin_nums1 + end_nums1) / 2;

    // get the division position of nums2
    int position_nums2 = total_num - middle_nums1;

    if(middle_nums1 == 0 || position_nums2 == 0)
        return middle_nums1;
    // the division position of nums1 is too big, find the first half
    else if(nums1[middle_nums1-1] > nums2[position_nums2])
        return find_position(nums1, nums2, begin_nums1, middle_nums1 - 1, total_num);
    // the division position of nums1 is too small, find the second half
    else if(nums2[position_nums2 - 1] > nums1[middle_nums1])
        return find_position(nums1, nums2, middle_nums1 + 1, end_nums1, total_num);
    else
        return middle_nums1;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){

    int *nums1_input, *nums2_input;
    nums1_input = nums2_input = NULL;

    int base_end = 0;

    int total_num = (nums1Size + nums2Size) / 2;

    if(nums1Size > nums2Size){
        nums1_input = nums2;
        nums2_input = nums1;
        base_end = nums2Size;
    } else
    {
        nums1_input = nums1;
        nums2_input = nums2;
        base_end = nums1Size;
    }
    

    int division = find_position(nums1_input, nums2_input, 0, base_end - 1, total_num);

    float median = 0.0;

    if(division != 0){
        if((nums1Size + nums2Size) % 2 == 1)
            median = nums1_input[division] < nums2_input[total_num - division] ? 
                nums1_input[division] : nums2_input[total_num - division];
        else
        {
            int max_left = nums1_input[division - 1] > nums2_input[total_num - division - 1] ?
                nums1_input[division - 1] : nums2_input[total_num - division - 1];
            int min_right = nums1_input[division] < nums2_input[total_num - division] ?
                nums1_input[division] : nums2_input[total_num-division];
            median = ((float)max_left + (float)min_right) / 2;
        }
    } else if(division == 0){
        if((nums1Size + nums2Size) % 2 == 1){
            if(nums1_input[0] < nums2_input[total_num - division - 1]){
                median = nums1_input[0] < nums2_input[total_num - division - 1] ?
                    
            }
        }
    }

    return median;
}

int main(int argc, char* argv[]){
    int num1[5] = {1, 2, 8, 9 ,10};
    int num2[1] = {4};

    double median = findMedianSortedArrays(num1, 5, num2, 1);
    printf("median = %f\n", median);
}