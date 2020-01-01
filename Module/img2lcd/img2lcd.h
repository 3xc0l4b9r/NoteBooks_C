#ifndef __IMG2LCD_H_
#define __IMG2LCD_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//jpeg解码库头文件包含
#include <jpeglib.h>

/* bmp file header : bmp文件头, 14
 * 文件类型(魔数)									:			2			:			0x00
 * 文件大小											:			4			:			0x02
 * 保留, 必须设置为0								:			2			:			0x06
 * 保留, 必须设置为0								:			2			:			0x08
 * 位图数据, (像素数组)的地址偏移, 也就是起始地址	:			4			:			0x0A
 * */

struct bitmap_header {
	int16_t type;
	//int8_t type[2];
	int32_t size; 
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits; 
}__attribute__((packed));

/* bitmap information : 位图信息头, 40
 * 位图信息头的大小															:			4			:			0x0E
 * 位图宽度(单位为像素), 有符号整数											:			4			:			0x12
 * 位图高度(单位为像素), 有符号整数(为负数表示从上到下存放行数据)			:			4			:			0x16
 * 色彩平面数, 只有1为有效值												:			2			:			0x1A
 * 每个像素所占位数, 即图像的色深, 典型值为1, 4, 8, 16, 24和32				:			2			:			0x1C
 * 说明图像压缩类型, BI_RGB(0)表示不压缩									:			4			:			0x1E
 * 图像大小, 指原始位图数据的大小, 与文件大小不是同一个概念					:			4			:			0x22
 * 水平分辨率(单位为像素/米), 有符号整数									:			4			:			0x26 
 * 垂直分辨率(单位为像素/米), 有符号整数									:			4			:			0x2A
 * 调色板颜色索引数, 为0时说明使用所有, 也就是2e色深次方					:			4			:			0x2E
 * 重要颜色数, 为0时说明所有颜色都是重要的									:			4			:			0x32
 * */

struct bitmap_information {
    int32_t size;
    int32_t width;
    int32_t height;
    int16_t planes;
    int16_t bit_count;
    int32_t compression;
    int32_t sizeImgs;
    int32_t xPel;
    int32_t yPel;
    int32_t clrused;
    int32_t clrImportant;
}__attribute__((packed));

/* bitmap data : 位图数据(24 : BGR, 32 : BGRA)
 * Windows 默认的扫描的最小单位是4字节, 如果数据对齐满足这个值的话对于数据的获取速度等都是有很大的增益的
 * BMP图像顺应了这个要求,要求每行的数据的长度必须是4的倍数,如果不够需要进行比特填充(以0填充),这样可以达到按行的快速存取
 * 每行的数据 = 4*((色深*宽度)/32)
 * 色深, 1, 4, 8, 16, 24, 32
 * 宽度
 * 高度
 * 位图数据大小
 * */

unsigned int *lcd_ptr;

int get_file_size(const char *pathname);
int point2lcd(unsigned int x, unsigned int y, unsigned int color);
int rect2lcd(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
int get_row_data(unsigned int w, unsigned int bpp);
int bmp2lcd(const unsigned char *pathname, unsigned int x, unsigned int y, unsigned int flags);
int jpeg2lcd(const unsigned char *pathname, unsigned int x, unsigned int y, unsigned char * buf, unsigned int size, unsigned int flags);

#endif
