#ifndef LCDOPERATION
#define LCDOPERATION

int Read(int fd,void * buf,int size);
int Write(int fd,void* buf,int size);
//将(x,y)处的像素点显示成color颜色
void draw_point(int x,int y,int color,int *des);
//在(x0,y0)处显示一个w宽,h高,color颜色的矩形
void draw_orth(int x0,int y0,int w,int h,int color,int *des);
//在(x0,y0)处显示一个w宽,h高,color颜色的方框
void draw_OuterSquare(int x0,int y0,int w,int h,int outWidth,int innerWidth, int color,int *des);
void draw_InnerSquare(int x0,int y0,int w,int h,int weight,int color,int *des);
/*
   void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color)
   在位置为(x0,y0)处显示宽为w,高为h的汉字	
*/
void lcd_draw_word(int x0,int y0,int w,int h,char *data,int color,int* des);
void lcd_draw_Num(int x0,int y0,int w,int h,int num,int color,int* des);
//在(x0,y0)处显示一张路径为pathname的bmp图片
void display_bmp(int x0,int y0,const char *src,int *des);
/*获取一个映射地址*/
int *MmapGetLcd();

#endif