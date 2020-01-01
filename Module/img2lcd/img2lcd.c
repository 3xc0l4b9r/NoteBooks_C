#include "img2lcd.h"

//获取文件大小
int get_file_size(const char *pathname)
{
    struct stat statbuf;
    
    int rt = stat(pathname, &statbuf);

    if (rt == -1) {
        printf("failed to get file attributes\n");
        return -1;
    }

    int size = statbuf.st_size;

    return size;
}

//画点
int point2lcd(unsigned int x, unsigned int y, unsigned int color)
{
    *(lcd_ptr+800*y+x) = color;
}

//点成面
int rect2lcd(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
    int i, j;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            point2lcd(i+x, j+y, color);
        }
    }
}

//返回扫描行所占的实际字节数
int get_row_data(unsigned int w, unsigned int bpp)
{
	//一个扫描行所占用的字节数
	int width_byte;

    switch (bpp) {
        case 1 :
            width_byte = (w+7)/8;
            break;
        case 4 :
            width_byte = (w/2)+(w%2);
            break;
        case 8 :
            width_byte = w;
            break;
        case 16 : case 24 : case 32 :
            width_byte = w*bpp/8;
            break;
        default :
         return -1;
    }

    //define WIDTHBYTES(bits) (((bits)+31)/32*4)
    return (width_byte+3)/4*4;
}

/* *bmp2lcd : 指定位置显示固定大小的jpeg图片
 * pathname : 要显示的bmp图片文件名，
 * x,y : 起点位置
 * flags : 缩放比例
 * */

int bmp2lcd(const unsigned char *pathname, unsigned int x, unsigned int y, unsigned int flags)
{
    unsigned int bmp_fd;
    unsigned int i, j, w, h, bpp, r, g, b, color, line;
    struct bitmap_header bheader;
    struct bitmap_information binfo;

    //打开bmp文件，权限为可读
    bmp_fd = open(pathname, O_RDONLY);

    if (-1 == bmp_fd) {
        fprintf(stderr, "open bmp file : %s failed! \n", pathname);
        return -1;
    }

    //读取bmp图片文件头
    read(bmp_fd, &bheader, sizeof(bheader));
    read(bmp_fd, &binfo, sizeof(binfo));

    w = binfo.width;
    h = binfo.height;
    bpp = binfo.bit_count;

    //获取一个扫描行所占的实际字节数并申请内存空间
    unsigned int row_data = get_row_data(w, bpp);
	unsigned char *rgb_data = calloc(1, row_data*h*sizeof(int));

    //读取bmp图片颜色数据
    read(bmp_fd, rgb_data, row_data*h*sizeof(int));

    if (flags) {
        line = flags;
        w = w/line;
        h = h/line;
    }else {
        line = 1;
    }
    
    for (j = 0; j < h;j++) {
        for (i = 0; i < w; i++) {
            b = *((rgb_data+i*line*(bpp/8)+row_data*j*line));
            g = *((rgb_data+i*line*(bpp/8)+row_data*j*line+1));
            r = *((rgb_data+i*line*(bpp/8)+row_data*j*line+2));
            color = b;
            color |= (g << 8);
            color |= (r << 16);
            point2lcd(i+x, h-1-j+y, color);
        }
    }


    close(bmp_fd);

    return 0;
}

/* *jpeg2lcd : 指定位置显示固定大小的jpeg图片
 * pathname : 要显示的jpeg图片文件名，
 * x,y : 起点位置
 * buf : 要显示的图片颜色数据
 * size : 图片颜色数据大小
 * flags : 缩放比例
 * */

int jpeg2lcd(const unsigned char *pathname, unsigned int x, unsigned int y, unsigned char *buf, unsigned int size, unsigned int flags)
{
    unsigned int jpeg_fd;
    unsigned int jpeg_size;
    unsigned char *tmp;

    unsigned int x_s = x;
    unsigned int x_e, y_e;
    unsigned int i, j, w, h, line, color;

    //1, 分配jpeg对象结构体空间，并初始化
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    if (pathname != NULL) {

        //打开jpeg文件，权限可读可写
        jpeg_fd = open(pathname, O_RDWR);

        if (-1 == jpeg_fd) {
            fprintf(stderr, "open jpeg file : %s failed !\n", pathname);
            return -1;
        }

        //获取jpeg文件的大小
        jpeg_size = get_file_size(pathname);

        //为jpeg文件申请内存空间
        tmp = calloc(1, jpeg_size);

        //读取jpeg文件所有内容到内存中
        read(jpeg_fd, tmp, jpeg_size);

    }else {
        jpeg_size = size;
        tmp = buf;
    }

    //默认错误管理设置
    cinfo.err = jpeg_std_error(&jerr);

    //2, JPEG压缩对象的初始化
    jpeg_create_decompress(&cinfo);

    //3, 申请内存缓冲区数据源
    jpeg_mem_src(&cinfo, tmp, jpeg_size);

    //4, 读取jpeg文件的头信息
    (void)jpeg_read_header(&cinfo, TRUE);

    //5, 开始解码
    (void)jpeg_start_decompress(&cinfo);

    //6, 读取解码数据

    //用来存放图像数据的缓冲区变量
    unsigned char *img_data;

    //每行数据的实际大小
    unsigned int row_data = cinfo.output_width*cinfo.output_components;

    //
    img_data = (unsigned char *)(*cinfo.mem->alloc_sarray)
                ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_data, 1);

    
    if (flags) {
        w = cinfo.output_width/flags;
        h = cinfo.output_height/flags;
        line = flags;
    }else {
        w = cinfo.output_width;
        h = cinfo.output_height;
        line = 1;
    }

    //output_scanline : 当前已经读取的行号
    //如此即可依次读出所有数据并填充到缓冲区中
    //flags : 每次读取的行数
    while (cinfo.output_scanline < cinfo.output_height) {
        for (i = 0; i < line; i++) {
            (void)jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&img_data, 1);
        }

        for (i = 0; i < w; i++) {
            unsigned char r = *(img_data+3*i*line);
            unsigned char g = *(img_data+3*i*line+1);
            unsigned char b = *(img_data+3*i*line+2);
            color = b;
            color |= (g << 8);
            color |= (r << 16);
            //在对应位置显示像素点颜色值
            point2lcd(x, y, color);
            x++;
        }
        y++;
        x = x_s;
    }


    //7, 解码完成

    //结束解压操作
    (void)jpeg_finish_decompress(&cinfo);

    //释放资源
    jpeg_destroy_decompress(&cinfo);

    if (pathname != NULL) {
        close(jpeg_fd);
        free(buf);
    }

    return 0;
}
