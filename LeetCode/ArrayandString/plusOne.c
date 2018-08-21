/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
	int sum = 0;
	int index = 0;
	int carry = 0;
	int *newdigits = NULL;

	/*空指针或空数组*/
	if(!digits || digitsSize == 0) {
		*returnSize = 0;
		return digits;
	}

	*returnSize = digitsSize;
	index = digitsSize - 1;

	/*从低位往高位遍历,最低位加一操作*/
	while(index >= 0) {

		sum = (index == digitsSize-1)?(digits[index] + 1 + carry):(digits[index] + carry);
		//0~9
		digits[index] = sum % 10;
		//0~1
		carry = sum / 10;

		if(carry == 0) {
			return digits;
		}

		--index;
	}

	/*最高位有进位*/
	if(carry) {
		*returnSize = digitsSize + 1;
		//calloc和malloc返回的指针都是void*类型，不能当作普通指针直接使用，需要转换
		newdigits = (int *)calloc(1, (digitsSize + 1)*sizeof(int));
		newdigits[0] = carry;
		for(index = 0; index < digitsSize; ++index) {
			newdigits[index+1] = digits[index];
		}

		return newdigits;
	}

	return digits;
}
