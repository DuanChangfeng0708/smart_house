#ifndef GAMEWIGET
#define GAMEWIGET

#include"LcdOperation.h"
#include"Point.h"
#define TURNBACK_X 15
#define TURNBACK_Y 25
#define SNAKE_X 100
#define SNAKE_Y 150
#define BOOM_X 100
#define BOOM_Y  250
#define GANME2048_X 100
#define GANME2048_Y 400

#define TYPE_MAP  0
#define TYPE_BODY 1
#define TYPE_FOOD 2
#define TYPE_WALL 3

struct GlobleMAP
{
    int index;
    int type;
};



void WigetInit(int *des);
void GameWiget(int *des,struct Point *p);
void createFood(int *des);
void snakeGame(int* des, struct Point *p);  
void SnakeGameInit(int *des);
int snakeMove(int *des,int direction);
int x2Index(int x);
int y2Index(int y);
void boomGame(int*des ,struct Point *p);

void game2048(int *des ,struct Point *p);

#endif