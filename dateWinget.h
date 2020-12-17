#ifndef DATEWINGET
#define DATEWINGET
#include"Point.h"
struct GY39Date
{
    int temperature;//温度 
    int humidity;   //湿度
    int pressure;    //气压；
    int altitude;    //海拔;
};
void DateWiget(struct Point *p,int *smoke,struct GY39Date *gy39date,int *des);
#endif