/*
 * fast zigzag转换，不使用额外的临时存储空间，直接
 * 按照转换前后字符串下标对应关系进行转换
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * convert(char * s, int numRows){
    /**
     * 仍然将输入数组划分为单元，每个单元元素个数为2 * numRows - 2
     */

    //获取输入数组的长度
    int strl_input = strlen(s);

    //分配输出数组空间
    char *str_output = (char*)malloc(sizeof(char) * (strl_input + 1));
    memset(str_output, '\0', strl_input + 1);

    if(numRows <= 1){
        memcpy(str_output, s, strl_input + 1);
        return str_output;
    }

    /**
     * 确认可划分为多少个单元
     * numElements: 每个单元拥有的元素数目
     * numColumns: 每个单元拥有的列数
     * numUnits: 数组可划分为的单元数
     */
    int numElements = 2 * numRows - 2;
    int numColumns = numRows - 1;
    int numUnits = strl_input / numElements + 1;

    /**
     * 进行转换，基于以下事实：
     * 1、按照行索引进行；
     * 2、每个单元中首末行仅贡献1个元素；
     * 3、每个单元中除首末行外，共享2个元素；
     */
    int str_output_index = 0;
    int unit_dia_sum[numUnits];
    //计算每个单元除首末行外各行元素下标和
    for(int index_unit; index_unit != numUnits; ++index_unit)
        unit_dia_sum[index_unit] = (2 * index_unit + 1) * numElements;
    for(int row_index =  0; row_index != numRows; ++row_index)
        for(int unit_index = 0; unit_index != numUnits; ++unit_index){
            if(row_index == 0 || row_index == numRows - 1){
                //首末行贡献1个元素
                int index_input = row_index + unit_index * numElements;
                if(index_input < strl_input){
                    str_output[str_output_index] = s[index_input];
                    str_output_index++;
                }
            }
            else{
                //其他行贡献2个元素
                int index_input1 = row_index + unit_index * numElements;
                int index_input2 = unit_dia_sum[unit_index] - index_input1;
                if(index_input1 < strl_input){
                    str_output[str_output_index] = s[index_input1];
                    str_output_index ++;
                }
                if(index_input2 < strl_input)
                {
                    str_output[str_output_index] = s[index_input2];
                    str_output_index ++;
                }
            }
        }
    
    return str_output;
}

int main(int argc, char* argv[]){
    char *input_string = argv[1];
    int numRows = atoi(argv[2]);
    char *output_string = convert(input_string, numRows);

    printf("%s\n", output_string);
    free(output_string);
    return 0;
}