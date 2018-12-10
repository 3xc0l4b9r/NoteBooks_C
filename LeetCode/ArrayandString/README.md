## ![Diagonal Traverse](https://github.com/3xc0l4b9r/NoteBooks_C/blob/master/LeetCode/ArrayandString/findDiagonalOrder.c "蛇形遍历")

**题目大意**

给定M×N个元素的矩阵（M行，N列），以对角线顺序返回矩阵的所有元素

**解题思路**

在遍历过程中有几种情况：向右遍历、向下遍历、向左下遍历、向右上遍历，

给定两个变量i, j（记作matrix[i][j]）记录当前坐标，通过判断当前坐标是否越界确定下个坐标位置

初始方向为右上角遍历，偏移量位：i--, j++, 向右上方移动时遇到上边界时,若未达到右边界,则向右遍历，否则,向下遍历

依此类推，可以将所有的情况与边界情况都列出来

同时需要排除三种特殊情况：当矩阵为空时不存在遍历结果，当矩阵行或列为1时直接将矩阵从下到上遍历

## ![Find Pivot Index](https://github.com/3xc0l4b9r/NoteBooks_C/blob/master/LeetCode/ArrayandString/pivotIndex.c "查找主索引")

**题目大意：**

给定数组，寻找枢轴下标，使得其左侧的值之和等于右侧的值之和，

如果存在，返回最左侧的枢轴下标，否则返回-1。

**解题思路：**

先求出整个数组的总和，

然后遍历，已遍历过的枢轴的值进行累加，

使用数组总和减去当前枢轴下标的值

判断是否等于已遍历过的枢轴的总和，

是则返回下标，否则继续遍历

## ![Largest Number At Least Twice of Others](https://github.com/3xc0l4b9r/NoteBooks_C/blob/master/LeetCode/ArrayandString/dominantIndex.c "最大的数字至少是其他数字的两倍")

**题目大意：**

在给定的整数数组中，总是有一个最大的元素，

查找数组中最大的元素是否至少是数组中其他每个数字的两倍，

如果是，返回最大元素的索引，否则返回-1。

**解题思路：**

记录下数组中的最大值和次大值，最后判断一下最大值是否大于等于次大值的二倍即可。

## ![Plus One](https://github.com/3xc0l4b9r/NoteBooks_C/blob/master/LeetCode/ArrayandString/plusOne.c "+1")

**题目大意**

给定表示非负整数的非空数字数组，加上整数的1,

存储数字使得最高有效数字位于列表的开头，并且数组中的每个元素包含单个数字,

您可以假设整数不包含任何前导零，除了数字0本身。

**解题思路**

从低位往高位遍历,最低位加一，其他位不变，当遇到9，则向前一位进一

当最高位有进位时，在最高位前面扩展一个数位
