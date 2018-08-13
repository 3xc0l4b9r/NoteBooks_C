#include "head.h"

int dominantIndex(int* nums, int numsSize)
{
	int i;
	int max = 0, maxIndex = -1;

	if (numsSize > 50 || numsSize < 1) {
		maxIndex = -1;
	}

	if (numsSize == 1) {
		maxIndex = 0;
	}

	for (i = 0; i < numsSize; i++) {   
		if (nums[i] > max) {
			if (nums[i] >= (max*2)) {
				maxIndex = i;
			}else {
				maxIndex = -1;
			}
			max = nums[i];
		}else if (nums[i] * 2 > max) {
			maxIndex = -1;
		}
	}

	return maxIndex;
}
