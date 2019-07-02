/*
 * zigzag转换，使用二维数组作为临时存储，输出结果对二维数组扫描即可
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * convert(char * s, int numRows){

    int instr_len = strlen(s);

    //空字符串、单行以及0行直接返回
    if(instr_len == 0 || numRows <= 1)
        return s;

    char *output = (char*)malloc(sizeof(char) * (instr_len + 1));
    memset(output, '\0', instr_len + 1);
    /*
     * 将a0a1...aj，j=2m-3视作一个单元，确定有多少个单元
     * unitElements: 每个单元存储多少个字符串
     * unitColumns: 每个单元存储的列数
     * numUnit: 总共的单元数目
     */
    int unitElements = 2 * numRows - 2;
    int unitColumns = numRows - 1;
    int numUnit = instr_len / unitElements + 1;
    
    //临时存储二维数组列的数目
    int numTempColumns = numUnit * unitColumns;
    int numTempRows = numRows;

    //临时存储二维数组
    char tempstrMatrix[numTempRows][numTempColumns];

    //初始化临时存储二维数组
    for(int index = 0; index != numTempRows; ++index)
        memset(tempstrMatrix[index], '\0', numTempColumns);

    //设置临时存储二维数组
    for(int index = 0; index != numUnit; ++index){
        //当前单元的起始列与终止列
        int begin_column = index * unitColumns;
        int end_column = begin_column + unitColumns - 1;
        //当前单元存储字符串的索引
        int begin_index = unitElements * index;
        for(int row = 0; row != numRows; ++row){
            //防止越界
            if(begin_index == instr_len)
                break;
            tempstrMatrix[row][begin_column] = s[begin_index];
            begin_index++;
        }
        for(int column_i = begin_column + 1; column_i <= end_column; ++column_i){
            int sum_row_column = unitColumns + index * unitColumns;
            //防止越界
            if(begin_index == instr_len)
                break;
            tempstrMatrix[sum_row_column - column_i][column_i] = s[begin_index];
            begin_index++;
        }
    }

    //输出zigzag数组
    int output_index = 0;
    for(int row = 0; row != numTempRows; ++row){
        for(int column_ = 0; column_ != numTempColumns; ++column_){
            if(tempstrMatrix[row][column_] == '\0')
                continue;
            else{
                output[output_index] = tempstrMatrix[row][column_];
                output_index ++;
            }
        }
    }

    return output;
}

int main(int argc, char *argv[]){
    char *input_str = argv[1];
    char *output_str = NULL;
    int numRows = atoi(argv[2]);
    output_str = convert(input_str, numRows);
    printf("%s\n", output_str);
}