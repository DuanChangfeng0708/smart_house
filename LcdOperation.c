#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "LcdOperation.h"
char nums[][19 * 16 / 8] = {
    /*--  文字:  0  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x3F, 0x00, 0x7F, 0x00, 0xF3, 0x80, 0xE3, 0x80, 0xE3, 0x80,
     0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0x77, 0x80, 0x7F, 0x00, 0x3E, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  1  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x1C, 0x00,
     0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  2  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x7F, 0x00, 0x7F, 0x80, 0xE3, 0x80, 0x43, 0x80, 0x03, 0x80,
     0x07, 0x00, 0x0F, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xFF, 0x80, 0xFF, 0x80,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  3  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x3F, 0x00, 0x77, 0x80, 0xE3, 0x80, 0x43, 0x80, 0x07, 0x80,
     0x1F, 0x00, 0x1F, 0x00, 0x03, 0x80, 0x03, 0x80, 0xE3, 0x80, 0xF3, 0x80, 0x7F, 0x00, 0x3E, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  4  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x3F, 0x00,
     0x3F, 0x00, 0x77, 0x00, 0xE7, 0x00, 0xFF, 0xC0, 0xFF, 0xC0, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  5  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x7F, 0x80, 0x70, 0x00, 0x60, 0x00, 0xFE, 0x00,
     0xFF, 0x00, 0xE3, 0x80, 0x03, 0x80, 0x03, 0x80, 0xE3, 0x80, 0xE7, 0x80, 0xFF, 0x00, 0x7E, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  6  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x7E, 0x00,
     0x7F, 0x80, 0xF3, 0x80, 0xE1, 0xC0, 0xE1, 0xC0, 0xE1, 0xC0, 0xF3, 0x80, 0x7F, 0x80, 0x3F, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  7  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0xFF, 0x80, 0x03, 0x80, 0x07, 0x00, 0x07, 0x00,
     0x0E, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  8  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x7F, 0x00, 0x7F, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xF7, 0x80,
     0x7F, 0x00, 0x7F, 0x00, 0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xFF, 0x00, 0x7F, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  9  --*/
    /*--  楷体14;  此字体下对应的点阵为：宽x高=10x19   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=16x19  --*/
    {0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x7F, 0x00, 0xFF, 0x80, 0xE3, 0x80, 0xE3, 0x80, 0xE3, 0x80,
     0xE7, 0x80, 0xFF, 0x00, 0x7F, 0x00, 0x0E, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x38, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

};
int Read(int fd, void *buf, int size)
{
    int n = read(fd, buf, size);
    if (n < 0)
    {
        perror("Read error \n");
        exit(-1);
    }
    return n;
}
int Write(int fd, void *buf, int size)
{
    int n = write(fd, buf, size);
    if (n < 0)
    {
        perror("Write error \n");
        exit(-1);
    }
    return n;
}
//将(x,y)处的像素点显示成color颜色
void draw_point(int x, int y, int color, int *des)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(des + 800 * y + x) = color;
    }
}
//在(x0,y0)处显示一个w宽,h高,color颜色的矩形
void draw_orth(int x0, int y0, int w, int h, int color, int *des)
{
    int x, y;
    for (y = y0; y < y0 + h; y++)
    {
        for (x = x0; x < x0 + w; x++)
        {
            draw_point(x, y, color, des);
        }
    }
}
//在(x0,y0)处显示一个w宽,h高,color颜色的方框
void draw_OuterSquare(int x0, int y0, int w, int h, int outWidth, int innerWidth, int color, int *des)
{
    if (h < outWidth || w < outWidth)
    {
        printf("draw_OuterSquare 参数有error\n");
        return;
    }
    //行
    for (int x = x0; x < x0 + w; x += outWidth)
    {
        draw_InnerSquare(x, y0, outWidth, outWidth, innerWidth, color, des);
        draw_InnerSquare(x, y0 + h - outWidth, outWidth, outWidth, innerWidth, color, des);
    }
    //列
    for (int y = y0; y < y0 + h; y += outWidth)
    {
        draw_InnerSquare(x0, y, outWidth, outWidth, innerWidth, color, des);
        draw_InnerSquare(x0 + w - outWidth, y, outWidth, outWidth, innerWidth, color, des);
    }
}

void draw_InnerSquare(int x0, int y0, int w, int h, int innerWidth, int color, int *des)
{
    if (h < innerWidth || w < innerWidth)
    {
        printf("draw_InnerSquare 参数有error\n");
        return;
    }
    int x, y;
    for (y = y0 + (h - innerWidth) / 2; y < y0 + (h - innerWidth) / 2 + innerWidth; y++)
    {
        for (x = x0 + (w - innerWidth) / 2; x < x0 + (w - innerWidth) / 2 + innerWidth; x++)
        {
            draw_point(x, y, color, des);
        }
    }
}
/*
   void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color)
   在位置为(x0,y0)处显示宽为w,高为h的汉字	
*/
void lcd_draw_word(int x0, int y0, int w, int h, char *data, int color, int *des)
{
    int i, k;

    for (i = 0; i < w * h / 8; i++)
    {
        for (k = 0; k < 8; k++)
        {
            if ((data[i] << k) & 0x80)
            {
                draw_point(x0 + (i * 8 + k) % w, y0 + i / (w / 8), color, des);
            }
        }
    }
}
//在(x0,y0)处显示一张路径为pathname的bmp图片
void display_bmp(int x0, int y0, const char *src, int *des)
{
    //打开BMP文件
    int fd_bmp = open(src, O_RDONLY);
    if (fd_bmp < 0)
    {
        perror(src);
        exit(-1);
    }

    unsigned char buf[4] = {0};
    //判断是否为BMP文件
    Read(fd_bmp, buf, 2);

    if (buf[0] == 0x42 && buf[1] == 0x4D)
    {
        ;
    }
    else
    {
        printf("%s is not bmp file!\n", src);
        exit(-1);
    }

    //将光标偏移至宽度数据之前
    lseek(fd_bmp, 0x12, SEEK_SET);
    //读取宽度数据
    Read(fd_bmp, buf, 4);
    //宽度数据的合成
    int width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
    //将光标偏移至高度数据之前
    lseek(fd_bmp, 0x16, SEEK_SET);
    //读取宽度数据
    Read(fd_bmp, buf, 4);
    //高度数据的合成
    int hight = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
    //将光标偏移至位深数据之前
    lseek(fd_bmp, 0x1c, SEEK_SET);
    //读取色深数据
    Read(fd_bmp, buf, 2);
    //位深数据的合成
    int depth = (buf[1] << 8) | buf[0];

    //求出BMP文件中像素数组每行的字节数
    //1个宽度1个像素点每个像素点24位（即3个字节 = 深度/8）深度为24的情况下
    int ColSize = width * depth / 8;

    //看每行的字节数是否为4的倍数,如果不是4的倍数,那么就需f要将赖子的个数求出来
    if (ColSize % 4 != 0)
    {
        ColSize = ColSize + 4 - (ColSize + 4) % 4;
    }
    int srcCols = ColSize / 4;
    //求出要在内存中用来保存像素数组所开辟的空间的每一行的字节数
    //int RealCol=(ColSize-ColSize%4)/4;

    //开辟空间保存像素数组数据
    //printf("width is %d,hight is %d,depth is %d,RealSize is %d\n",width,hight,depth,ColSize*hight+54);
    unsigned char *dateChar = (unsigned char *)malloc(ColSize * hight);

    //将光标偏移至像素数组数据之前,即从头开始偏移54，16进制为0x36
    lseek(fd_bmp, 0x36, SEEK_SET);
    //一次性的将像素数组数据读取到刚开辟出来的空间中去
    int nr = Read(fd_bmp, dateChar, ColSize * hight);

    int *date = (int *)malloc(width * hight * 4);
    for (int i = 0, j = 0; i < width * hight; i++, j += depth / 8)
    {

        date[i] = (dateChar[j + 2] << 16) | (dateChar[j + 1] << 8) | dateChar[j];
        if ((i + 1) % width == 0) //如果i到了行尾 j也要到行尾
        {
            j = j + srcCols - (j + srcCols) % srcCols;
            //printf("i==%d j==%d, j%width\n",i,j);
            j = j - depth / 8; //为了符合上面循环
        }
    }
    free(dateChar);
    //对数据进行处理后映射区域内写入即可
    /*
    for(int dateRow=hight-1,desRow=x0;dateRow>=0;desRow++,dateRow--)
    {
        for(int dateCol=0,desCol=y0;dateCol<width;dateCol++,desCol++)      
        {
            *(des+desRow*800+desCol)=*(date+dateRow*width+dateCol);
        }
    }*/
    for (int dateRow = hight - 1, desRow = y0; dateRow >= 0; desRow++, dateRow--)
    {
        for (int dateCol = 0, desCol = x0; dateCol < width; dateCol++, desCol++)
        {
            *(des + desRow * 800 + desCol) = *(date + dateRow * width + dateCol);
        }
    }
}
int *MmapGetLcd()
{
    int lcdFd = open("/dev/fb0", O_RDWR);
    if (lcdFd < 0)
    {
        perror("lcd 打开失败\n");
        exit(-1);
    }

    int *lcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFd, 0);
    if (lcd == MAP_FAILED)
    {
        perror("MMAP ERROR\n");
        exit(-1);
    }
    return lcd;
}
void lcd_draw_Num(int x0, int y0, int w, int h, int num, int color, int *des)
{
    int wei[10] = {0};
    int index = 0;
    if (num == 0)
    {
        wei[0] = 0;
        index++;
    }
    while (num && index < 10)
    {
        /* code */
        wei[index] = num % 10;
        num = num / 10;
        index++;
    }
    int currX = x0; //实际的x坐标
    for (int i = index - 1; i >= 0; i--)
    {
        lcd_draw_word(currX, y0, w, h, nums[wei[i]], color, des);
        currX = currX + w + w / 10;
    }
}