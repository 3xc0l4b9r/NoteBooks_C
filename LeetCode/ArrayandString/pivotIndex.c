#include "pivotindex.h"

int pivotIndex(int* nums, int numsSize) 
{
	if (nums == NULL || numsSize <= 0 || numsSize > 10000) {
		return -1;
	}

	int i = 0, j = 0;
	int sum = 0, curSum = 0;

	//将整个数组计算总和sum
	while (i < numsSize) {
		sum += nums[i++];
	}

	//计算前j项和是否等于sum/2，是则返回下标
	while (j < numsSize) {
		if (sum - nums[j] == 2*curSum) {
			return j;
		}
		curSum += nums[j++];
	}

	return -1;
}
