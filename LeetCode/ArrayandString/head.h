#ifndef __HEAD_H_
#define __HEAD_H_

#include <stdio.h>
#include <stdlib.h>

int pivotIndex(int* nums, int numsSize);
int dominantIndex(int* nums, int numsSize);
int* plusOne(int* digits, int digitsSize, int* returnSize);
int* findDiagonalOrder(int** matrix,\
		int matrixRowSize, int matrixColSize,\
		int* returnSize);
#endif
