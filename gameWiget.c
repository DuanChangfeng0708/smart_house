
#include "gameWiget.h"
#include "LcdOperation.h"
#include "Point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SNAKE_X 100
#define SNAKE_Y 150
#define BOOM_X 100
#define BOOM_Y 250
#define GANME2048_X 100
#define GANME2048_Y 400

#define SNAKE_MAX_LEN 98 * 78
#define INIT_SNAKE_LEN 3
#define STEP_LEN 6
#define MAX_SPEED 500000
#define MAP_WIDTH 600
#define MAP_HIGHT 480
char SnakeWord[][40 * 35 / 8] = {
    /*--  文字:  贪  --*/
    /*--  楷体26;  此字体下对应的点阵为：宽x高=36x35   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=40x35  --*/
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
     0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF,
     0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xFF, 0xF8, 0xC7, 0xFF, 0xFF, 0xFF,
     0xF0, 0xE1, 0xFF, 0xFF, 0xFF, 0xE0, 0x30, 0xFF, 0xFF, 0xFF, 0xC0, 0x18,
     0x3F, 0xFF, 0xFF, 0x86, 0x1C, 0x0F, 0xFF, 0xFF, 0x0F, 0xE6, 0x01, 0xFF,
     0xFE, 0x1E, 0x01, 0x00, 0x3F, 0xFC, 0x00, 0x01, 0xC0, 0x7F, 0xF0, 0x83,
     0x87, 0xFF, 0xFF, 0xE1, 0xFF, 0x8F, 0xFF, 0xFF, 0xCF, 0xFF, 0x80, 0xFF,
     0xFF, 0xFF, 0xC0, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x78, 0xFF, 0xFF, 0xFF,
     0xC7, 0xF8, 0xFF, 0xFF, 0xFF, 0xC6, 0x18, 0xFF, 0xFF, 0xFF, 0xC6, 0x18,
     0xFF, 0xFF, 0xFF, 0xC6, 0x38, 0xFF, 0xFF, 0xFF, 0xC6, 0x38, 0xFF, 0xFF,
     0xFF, 0xC6, 0x30, 0xFF, 0xFF, 0xFF, 0xC4, 0x38, 0xFF, 0xFF, 0xFF, 0xC4,
     0x39, 0xFF, 0xFF, 0xFF, 0xE4, 0x0F, 0xFF, 0xFF, 0xFF, 0xF8, 0xC0, 0xFF,
     0xFF, 0xFF, 0xF0, 0xE0, 0x7F, 0xFF, 0xFF, 0xC1, 0xF0, 0x3F, 0xFF, 0xFF,
     0x87, 0xFC, 0x3F, 0xFF, 0xFC, 0x1F, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},

    /*--  文字:  吃  --*/
    /*--  楷体26;  此字体下对应的点阵为：宽x高=36x35   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=40x35  --*/
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0xFF,
     0xFF, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF,
     0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x07, 0xFF, 0xFF, 0x07, 0x80,
     0x07, 0xFF, 0x80, 0x03, 0x00, 0x1F, 0xFF, 0x80, 0x03, 0x1F, 0xFF, 0xFF,
     0xC3, 0x86, 0x3F, 0xFF, 0xFF, 0xC3, 0x84, 0x7F, 0xFF, 0xFF, 0xC3, 0x8C,
     0xFF, 0xFF, 0xFF, 0xC3, 0x8F, 0xF0, 0xFF, 0xFF, 0xE3, 0x8F, 0xC0, 0x7F,
     0xFF, 0xE0, 0x04, 0x00, 0xFF, 0xFF, 0xE0, 0x3E, 0x21, 0xFF, 0xFF, 0xE3,
     0xFF, 0xC3, 0xFF, 0xFF, 0xE3, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0x87,
     0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFE, 0xFF,
     0xFF, 0xFF, 0x1F, 0xFC, 0x7F, 0xFF, 0xFF, 0x1F, 0xFC, 0x7F, 0xFF, 0xFF,
     0x1F, 0xFC, 0x7F, 0xFF, 0xFF, 0x1F, 0xF8, 0x7F, 0xFF, 0xFF, 0x03, 0xC0,
     0x7F, 0xFF, 0xFF, 0x80, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x00, 0xFF, 0xFF,
     0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},

    /*--  文字:  蛇  --*/
    /*--  楷体26;  此字体下对应的点阵为：宽x高=36x35   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=40x35  --*/
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x7F, 0xF0, 0xFF,
     0xFF, 0xFC, 0x1F, 0xF0, 0x3F, 0xFF, 0xFE, 0x1F, 0xF8, 0x3F, 0xFF, 0xFE,
     0x1F, 0xFC, 0x3F, 0xFF, 0xFE, 0x1F, 0xFF, 0xF3, 0xFF, 0xFE, 0x1F, 0xFF,
     0xC0, 0xFF, 0xFE, 0x1F, 0x9C, 0x00, 0x7F, 0xFE, 0x3F, 0x80, 0x70, 0x7F,
     0xFE, 0x21, 0x8F, 0xE0, 0xFF, 0xFE, 0x00, 0x0F, 0xE3, 0xFF, 0xC0, 0x00,
     0x1F, 0xEF, 0xFF, 0xE0, 0x20, 0x1F, 0xFF, 0xFF, 0xE2, 0x23, 0x07, 0x87,
     0xFF, 0xE0, 0x23, 0xC3, 0x83, 0xFF, 0xF0, 0x03, 0xC3, 0x07, 0xFF, 0xF0,
     0x07, 0xC0, 0x1F, 0xFF, 0xF8, 0x27, 0xC0, 0x7F, 0xFF, 0xF8, 0x23, 0xC1,
     0xFF, 0xFF, 0xFE, 0x21, 0xC7, 0xFF, 0xFF, 0xFE, 0x00, 0xC7, 0xFE, 0x7F,
     0xFE, 0x00, 0xC7, 0xFE, 0x7F, 0xF0, 0x38, 0xC7, 0xFE, 0x7F, 0x80, 0xFF,
     0xC7, 0xFE, 0x3F, 0xC1, 0xFF, 0xC3, 0xFC, 0x3F, 0xE7, 0xFF, 0xE0, 0x40,
     0x3F, 0xFF, 0xFF, 0xF0, 0x00, 0x3F, 0xFF, 0xFF, 0xF8, 0x00, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
char score[][24 * 21 / 8] = {
    /*--  文字:  分  --*/
    /*--  楷体16;  此字体下对应的点阵为：宽x高=22x21   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=24x21  --*/
    {0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x38,
     0x00, 0x03, 0x98, 0x00, 0x03, 0x8C, 0x00, 0x07, 0x0F, 0x00, 0x07,
     0x07, 0x80, 0x0E, 0x03, 0xC0, 0x1C, 0x1F, 0xF0, 0x3F, 0xFE, 0xF0,
     0x6F, 0xCE, 0x00, 0x01, 0xCE, 0x00, 0x03, 0x8C, 0x00, 0x03, 0x8C,
     0x00, 0x07, 0x1C, 0x00, 0x0E, 0xDC, 0x00, 0x1C, 0xF8, 0x00, 0x38,
     0x78, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  数  --*/
    /*--  楷体16;  此字体下对应的点阵为：宽x高=22x21   --*/
    /*--  宽度不是8的倍数，现调整为：宽度x高度=24x21  --*/
    {0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x80, 0x00, 0x03, 0xE7,
     0x00, 0x0F, 0xF7, 0x00, 0x0F, 0xCE, 0x00, 0x07, 0xEE, 0x00, 0x1F,
     0xED, 0xE0, 0x1F, 0x9F, 0xC0, 0x0F, 0xFF, 0x00, 0x1F, 0x77, 0x00,
     0x3F, 0xFF, 0x00, 0x07, 0xFF, 0x00, 0xFF, 0xCE, 0x00, 0x77, 0xCE,
     0x00, 0x07, 0x8F, 0x00, 0x03, 0xFB, 0x80, 0x0F, 0xF3, 0xE0, 0x3C,
     0xC1, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

struct Point snakeMap[SNAKE_MAX_LEN] = {{0, 0}}; //贪吃蛇有效活动范围地图的索引
struct GlobleMAP globleMap[80][100] = {{-1, TYPE_MAP}};

int HeadIndex, TailIndex;
int socreGet = 0;
int speed = 200000;

int x2Index(int x) { return (x - 200) / 6; };
int y2Index(int y) { return (y) / 6; };
void SnakeGame(int *des, struct Point *Point) {
    while (1) {
        SnakeGameInit(des);
        struct Point *p = (struct Point *)malloc(sizeof(struct Point));
        p->x = -1;
        p->y = -1;
        char ch = 'w';
        int gameOverFlag = 0;
        while (1) {
            if (p->x != Point->x || p->y != Point->y) {
                p->x = Point->x;
                p->y = Point->y;
                if ((p->x - TURNBACK_X) * (p->x - TURNBACK_X) +
                        (p->y - TURNBACK_X) * (p->y - TURNBACK_X) <
                    25 * 25) //检测返回按钮
                {
                    return;
                } else if (gameOverFlag == 0 && ch != 's' &&
                           480 * (p->x - 200) > p->y * 600 &&
                           480 * (p->x - 800) < -600 * p->y) //上
                {
                    ch = 'w';
                } else if (gameOverFlag == 0 && ch != 'w' &&
                           480 * (p->x - 200) < p->y * 600 &&
                           480 * (p->x - 800) > -600 * p->y) //下
                {
                    ch = 's';
                } else if (gameOverFlag == 0 && ch != 'd' &&
                           480 * (p->x - 200) < p->y * 600 &&
                           480 * (p->x - 800) < -600 * p->y) // zuo
                {
                    ch = 'a';
                } else if (gameOverFlag == 0 && ch != 'a' &&
                           480 * (p->x - 200) > p->y * 600 &&
                           480 * (p->x - 800) > -600 * p->y) // you
                {
                    ch = 'd';
                } else if (gameOverFlag == 1 && p->x < 400 && p->x > 250 &&
                           p->y > 227 && p->y < 315) {
                    break;
                    /* code */
                } else if (gameOverFlag == 1 && p->x < 550 && p->x > 400 &&
                           p->y > 227 && p->y < 315) {
                    return;
                    /* code */
                }
            }

            //每一次蛇移动一格
            if (gameOverFlag == 0 && snakeMove(des, ch)) //判断游戏是否结束
            {
                display_bmp(250, 165, "../image/gameOver.bmp", des);
                gameOverFlag = 1;
            }
            usleep(MAX_SPEED - speed);
        }
    }
}

void createFood(int *des) {
    srandom(time(NULL));

    int flag = 1; //检测食物坐标是否合法
    int x, y;
    do {
        x = (random() % (MAP_WIDTH / 6));
        y = (random() % ((MAP_HIGHT / 6)));
        x = x * 6 + 200;
        y = y * 6 + 0;
    } while (globleMap[y2Index(y)][x2Index(x)].type != TYPE_MAP);
    globleMap[y2Index(y)][x2Index(x)].type = TYPE_FOOD;
    printf("food.x = %d,food.y = %d,row=%d,col=%d\n", x, y, y2Index(y),
           x2Index(x));

    //按坐标将生成的食物画到屏幕上去
    draw_InnerSquare(x, y, 6, 6, 5, 0x00ff0000, des);
}
int snakeMove(int *des, int direction) {
    int newHeaderX, newHeaderY;       //新蛇头的坐标
    int newHeaderPreIndex;            //新蛇头坐标以前对应的索引
    int newHeaderPreX, newHeaderPreY; //新蛇头的索引以前对应的坐标
    int newHeaderPreType;             //新蛇头以前的类型
    int oldTailX, oldTailY;           //老蛇尾坐标
    switch (direction) {
    case 'w':
        newHeaderX = snakeMap[HeadIndex].x;
        newHeaderY = snakeMap[HeadIndex].y - STEP_LEN;
        break;
    case 's':
        newHeaderX = snakeMap[HeadIndex].x;
        newHeaderY = snakeMap[HeadIndex].y + STEP_LEN;
        break;
    case 'a':
        newHeaderX = snakeMap[HeadIndex].x - STEP_LEN;
        newHeaderY = snakeMap[HeadIndex].y;
        break;
    case 'd':
        newHeaderX = snakeMap[HeadIndex].x + STEP_LEN;
        newHeaderY = snakeMap[HeadIndex].y;
        break;
    }
    HeadIndex = HeadIndex == 0 ? SNAKE_MAX_LEN - 1 : HeadIndex - 1;

    //判断是不是BODY||WALL
    //--------------------------------------------------------------------------
    if (globleMap[y2Index(newHeaderY)][x2Index(newHeaderX)].type == TYPE_BODY ||
        globleMap[y2Index(newHeaderY)][x2Index(newHeaderX)].type == TYPE_WALL) {
        printf("GAME OVER\n");

        return 1;
    }
    //判断是否吃到食物
    else if (globleMap[y2Index(newHeaderY)][x2Index(newHeaderX)].type ==
             TYPE_FOOD) {
        draw_orth(newHeaderX, newHeaderY, 6, 6, 0x00ffffff, des);
        createFood(des);
        //更改分数
        socreGet++;
        //更改速度
        speed = speed < 400000 ? speed + 50000 : speed;
        draw_orth(59, 235, 92, 22, 0x00ffffff, des);
        lcd_draw_Num(59, 235, 16, 19, socreGet, 0x00ff0000, des);
    } else {
        oldTailX = snakeMap[TailIndex].x;
        oldTailY = snakeMap[TailIndex].y;
        //删除蛇尾
        draw_orth(oldTailX, oldTailY, 6, 6, 0x00ffffff, des);
        globleMap[y2Index(oldTailY)][x2Index(oldTailX)].type = TYPE_MAP;
        globleMap[y2Index(newHeaderY)][x2Index(newHeaderX)].type = TYPE_BODY;
        globleMap[y2Index(newHeaderY)][x2Index(newHeaderX)].index = -1;
        TailIndex = (TailIndex == 0) ? SNAKE_MAX_LEN - 1 : TailIndex - 1;
    }
    //输出新蛇头
    snakeMap[HeadIndex].x = newHeaderX;
    snakeMap[HeadIndex].y = newHeaderY;
    draw_InnerSquare(newHeaderX, newHeaderY, 6, 6, 5, 0x0000ff00, des);
    return 0;
}
void SnakeGameInit(int *des) {
    //初始化背景为白色
    draw_orth(0, 0, 800, 480, 0x00ffffff, des);
    //初始化map
    draw_OuterSquare(200, 0, MAP_WIDTH, MAP_HIGHT, 6, 5, 0x00000000, des);
    for (int row = 0; row < 80; row++) {
        for (int col = 0; col < 100; col++) {
            if (row == 0) {
                globleMap[row][col].index = -1;
                globleMap[row][col].type = TYPE_WALL;
                continue;
            } else if (row == 79) {
                globleMap[row][col].index = -1;
                globleMap[row][col].type = TYPE_WALL;
                continue;
            }

            if (col == 0) {
                globleMap[row][col].index = -1;
                globleMap[row][col].type = TYPE_WALL;
                continue;
            } else if (col == 99) {
                globleMap[row][col].index = -1;
                globleMap[row][col].type = TYPE_WALL;
                continue;
            }
            globleMap[row][col].index = -1;
            globleMap[row][col].type = TYPE_MAP;
        }
    }

    display_bmp(0, 0, "../image/return.bmp", des);
    //初始化贪吃
    // draw_OuterSquare(20,80,170,60,9,6,0x00ff000000,des);
    lcd_draw_word(30, 90, 40, 35, SnakeWord[0], 0x00000000, des);
    lcd_draw_word(80, 90, 40, 35, SnakeWord[1], 0x00000000, des);
    lcd_draw_word(130, 90, 40, 35, SnakeWord[2], 0x00000000, des);

    //初始化分数
    draw_OuterSquare(35, 200, 125, 72, 9, 6, 0x00ff000000, des);
    lcd_draw_word(59, 210, 24, 21, score[0], 0x00000000, des);
    lcd_draw_word(107, 210, 24, 21, score[1], 0x00000000, des);
    lcd_draw_Num(59, 235, 16, 19, 0, 0x00ff0000, des);
    //初始化she shen
    HeadIndex = 0;
    TailIndex = HeadIndex + 2;
    draw_InnerSquare(500, 240, 6, 6, 5, 0x0000ff00, des);
    snakeMap[HeadIndex].x = 500;
    snakeMap[HeadIndex].y = 240;
    globleMap[x2Index(500)][y2Index(240)].type = TYPE_BODY;
    globleMap[x2Index(500)][y2Index(240)].index = HeadIndex;
    draw_InnerSquare(500, 240 + STEP_LEN, 6, 6, 5, 0x0000ff00, des);

    snakeMap[HeadIndex + 1].x = 500;
    snakeMap[HeadIndex + 1].y = 240 + STEP_LEN;
    globleMap[x2Index(500)][y2Index(240 + STEP_LEN)].type = TYPE_BODY;
    globleMap[x2Index(500)][y2Index(240 + STEP_LEN)].index = HeadIndex + 1;

    draw_InnerSquare(500, 240 + 2 * STEP_LEN, 6, 6, 5, 0x0000ff00, des);
    snakeMap[TailIndex].x = 500;
    snakeMap[TailIndex].y = 240 + 2 * STEP_LEN;
    globleMap[x2Index(500)][y2Index(240 + 2 * STEP_LEN)].type = TYPE_BODY;
    globleMap[x2Index(500)][y2Index(240 + 2 * STEP_LEN)].index = TailIndex;
    //初始化食物
    createFood(des);
}
void WigetInit(int *des) {
    //背景圖片
    display_bmp(0, 0, "../image/GameView.bmp", des);
}
void GameWiget(int *des, struct Point *point) {
    int isCallFromOtherWiget = 1;
    struct Point *p = (struct Point *)malloc(sizeof(struct Point));
    p->x = -1;
    p->y = -1;
    while (1) {
        if (p->x != point->x || p->y != point->y) {
            p->x = point->x;
            p->y = point->y;
            if (isCallFromOtherWiget) //如果是其他界面调用的本函数 则重新绘画
            {
                WigetInit(des);
                isCallFromOtherWiget = 0;
            }
            if ((p->x - TURNBACK_X) * (p->x - TURNBACK_X) +
                    (p->y - TURNBACK_X) * (p->y - TURNBACK_X) <
                25 * 25) //检测返回按钮
            {
                return;
            } else if ((p->x - SNAKE_X) * (p->x - SNAKE_X) +
                           (p->y - SNAKE_Y) * (p->y - SNAKE_Y) <
                       50 * 50) {
                /* code */
                SnakeGame(des, point);
                isCallFromOtherWiget = 1;
            }
            /*else
            if((p->x-BOOM_X)*(p->x-BOOM_X)+(p->y-BOOM_Y)*(p->y-BOOM_Y)<10000)
            {

                boomGame(des,p);
                isCallFromOtherWiget=1;
            }
            else
            if((p->x-GANME2048_X)*(p->x-GANME2048_X)+(p->y-GANME2048_Y)*(p->y-GANME2048_Y)<10000)
            {

                game2048(des,p);
                isCallFromOtherWiget=1;
            }*/
        }
    }
}