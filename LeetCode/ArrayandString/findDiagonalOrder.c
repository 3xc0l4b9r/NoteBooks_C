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
	//i和j必须和matixRowSize,matrixColSize相对应，否则会出错
	int i = 0, j = 0;
	*returnSize = matrixRowSize*matrixColSize;
	int* returned = (int* )calloc(1, sizeof(int)*matrixRowSize*matrixColSize);


	for (k = 0; k < matrixRowSize*matrixColSize; k++) {
		returned[k] = matrix[i][j];
		//右上
		if (up) {

			//初始对角线方向为右上方
			if ((i-1) >= 0 && (j+1) < matrixColSize) {

				//(偏移量:行-1,列+1)
				i--, j++;

				/*向右上方移动时遇到上边界时,
				 * 若未达到右边界,则向右移动*/
			}else if ((j+1) < matrixColSize) {

				//(偏移量：行+0,列+1)
				j++;
				up = false;

				//否则,向下移动
			}else if ((i+1) < matrixRowSize) {

				//(偏移量:行+1,列+0)
				i++;
				up = false;

			}else break;

			//左下
		}else {

			//遇到边界时转向左下方
			if ((j-1) >= 0 && (i+1) < matrixRowSize) {

				//(偏移量:行+1,列-1)
				i++, j--;

				/* 向左下方移动时遇到左边界时,
				 * 若未达到下边界,则向下移动*/
			}else if ((i+1) < matrixRowSize) {

				//(偏移量：行+1,列+0)
				i++;
				up = true;

				//否则,向右移动
			}else if ((j+1) < matrixColSize) {

				//(偏移量：行+0,列+1)
				j++;
				up = true;

			}else break;
		}

	}

	return returned;
}
