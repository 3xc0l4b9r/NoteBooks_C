#include "head.h"

int* findDiagonalOrder(int** matrix,\
		int matrixRowSize, int matrixColSize,\
		int* returnSize) 
{

	if (matrix == NULL || matrixRowSize == 0 || matrixColSize == 0) {
		*returnSize = 0;
		return NULL;
	}


	int k;
	bool up = true;
	int i = 0, j = 0;
	*returnSize = matrixRowSize*matrixColSize;
	int* returned = (int* )calloc(1, sizeof(int)*matrixRowSize*matrixColSize);


	for (k = 0; k < matrixRowSize*matrixColSize; k++) {
		returned[k] = matrix[i][j];
		//右上
		if (up) {
			//判断是否到了上边界，没有则继续往右上
			if ((i-1) >= 0 && (j+1) < matrixColSize) {
				//行在减，列在加
				i--, j++;
			//到了上边界，则转换方向向右边
			}else if ((j+1) < matrixColSize) {
				j++;
				up = false;
			//判断是否到了最右下角的元素，到了则全部退出
			}else if ((i+1) < matrixRowSize) {
				i++;
				up = false;
			}else break;
		//左下
		}else {
			if ((j-1) >= 0 && (i+1) < matrixRowSize) {
				i++, j--;
			}else if ((i+1) < matrixRowSize) {
				i++;
				up = true;
			}else if ((j+1) < matrixColSize) {
				j++;
				up = true;
			}else break;
		}

	}

	return returned;
}
