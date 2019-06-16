#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) \
    (float)((a) > (b) ? (a) : (b))
#define MIN(a, b) \
    (float)((a) > (b) ? (b) : (a))
#define ODD(a) \
    ((a) % 2 == 1 ? 1 : 0)
#define AVERAGE(a, b) \
    ((a) + (b)) / 2.0

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

    float median = 0.0;

    //使用long_array指向较长的数组，使用short_array指向较短的数组
    //使用long_size指向较长数组的大小，short_size指向较短数组的大小
    int *long_array, *short_array, long_size, short_size, numsTSize;
    long_array = short_array = NULL;

    long_size = short_size = 0;

    //numsTSize存储两个数列总的元素数目
    numsTSize = nums1Size + nums2Size;

    if(nums1Size <= nums2Size){
        long_array = nums2;
        long_size = nums2Size;
        short_array = nums1;
        short_size = nums1Size;
    }
    else{
        long_array = nums1;
        long_size = nums1Size;
        short_array = nums2;
        short_size = nums2Size;
    }

    //处理特殊情况，较短数组的长度为0
    if(short_size == 0){
        if(ODD(long_size))
            median = (float)long_array[(long_size-1) / 2];
        else
            median = AVERAGE(long_array[(long_size-1) / 2] , (float)long_array[(long_size - 1) / 2 + 1]);
        goto end;
    }

    //使用short_index指向short_array的搜索位置，使用long_index指向long_array的搜索位置
    //使用pos_start，pos_end指向short_array的搜索范围
    int short_index, long_index, pos_start, pos_end;
    short_index = long_index = pos_start = pos_end = 0;

    pos_start = 0;
    pos_end = short_size - 1;

    while(pos_start <= pos_end){

        //计算short_index与long_index
        short_index = (pos_start + pos_end) / 2;
        long_index = numsTSize / 2 - short_index;

        //short_index为0时，long_index存在越界可能性，因此需要单独处理
        if(short_index == 0){
            if(long_index <= long_size - 1){
                //long_index未越界
                if(long_array[long_index - 1] <= short_array[short_index]){
                    median = ODD(numsTSize) ? MIN(long_array[long_index], short_array[short_index]) : 
                            AVERAGE(long_array[long_index - 1], MIN(long_array[long_index],short_array[short_index]));
                    goto end;
                }
                else
                    pos_start += 1;
            }
            else{
               //long_index越界,可证明，仅在nums1Size==nums2Size的情况下才会出现数组越界的问题
               if(long_array[long_index - 1] <= short_array[short_index]){
                   median = AVERAGE(long_array[long_index - 1], short_array[short_index]);
                   goto end;
               }
               else
                   pos_start += 1;
            }
        }
        else{
        //short_index不为0时，long_index不存在越界的可能性，正常处理即可
            if(short_array[short_index - 1] > long_array[long_index])
                //太大，往前移
                pos_end -= 1;
            else if(long_array[long_index - 1] > short_array[short_index])
                //太小，往后移
                pos_start += 1;
            else{
                //刚刚好，为结果
                median = ODD(numsTSize) ? MIN(short_array[short_index], long_array[long_index]):
                        AVERAGE(MAX(short_array[short_index - 1], long_array[long_index - 1]), MIN(short_array[short_index], long_array[long_index]));
                goto end;
            }
        }
    }

    /* 
    如果循环中找不到结果，说明一点，short_array中不存在median，median在long_array中或处于两个数组的边界处，下面代码即对此种情况进行处理
    FIX,上述逻辑错误，若循环找不到结果，并不能说明“short_array中不存在median，median在long_array中或处于两个数组的边界处”，只能说明两点：
    1、pos_start > short_index - 1
    2、pos_end <= 0
    分为三种情况：
    1、short_array所有值均比long_array大；
    2、short_array所有值均比long_array小；
    3、short_array的值与long_array没有必然联系。
    对于情况3而言，仅仅出现在pos_start > short_index - 1的条件下
    */
    
    if(long_array[long_size - 1] <= short_array[0]){
        if(nums1Size != nums2Size){
            //位于long_array中
            median = ODD(numsTSize) ? (float)long_array[numsTSize / 2] :
                    AVERAGE(long_array[numsTSize / 2], long_array[numsTSize / 2 - 1]); //此处是以numsTSize作为分母，而非index
        }
        else if(nums1Size == nums2Size){
            median = AVERAGE(long_array[long_size - 1], short_array[0]);
        }
    }
    else if(long_array[0] >= short_array[short_size - 1]){
        if(nums1Size != nums2Size){
            //位于long_array中
            median = ODD(numsTSize) ? (float)long_array[numsTSize / 2 - short_size] :
                    AVERAGE(long_array[numsTSize / 2 - short_size], long_array[numsTSize /2 -short_size - 1]); //此处是以numsTSize作为分母，而非index
        }
        else if(nums1Size == nums2Size){
            median = AVERAGE(long_array[0], short_array[short_size - 1]);
        }
    }
    else{
        median = ODD(numsTSize) ? (float)long_array[long_index - 1] :
                AVERAGE(MAX(short_array[short_size - 1], long_array[long_index - 2]), long_array[long_index - 1]);
    }
    
end:
    return median;
}

int main(int argc, char* argv[]){
    int num1[2] = {1, 3};
    int num2[2] = {2, 4};

    double median = findMedianSortedArrays(num1, 2, num2, 2);
    printf("median = %f\n", median);
}    