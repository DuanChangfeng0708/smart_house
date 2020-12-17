#include "LcdOperation.h"
#include "Point.h"
#include "dateWinget.h"
#include "gameWiget.h"

#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
// 1024 * 600
#define GAME_X 100
#define GAME_Y 500
#define DATE_X 950
#define DATE_Y 500
#define LIGHT_X 540
#define LIGHT_Y 350

#define CRTSCTS 020000000000 /* flow control */
char *path[] = {"../image/Main1.bmp", "../image/Main2.bmp"};
//获取点击坐标的线程函数

#define COM2 "/dev/ttySAC1"

static int uart_com_init(const char *COM) {
    int fd = open(COM, O_RDWR);
    if (fd == -1) {
        perror("COM");
        exit(-1);
    }

    struct termios com;

    // com.cflag ： 0000 1111 1111 1111 1000 1111 1010 1011
    // CS8 : 0001  0000
    //  com.cflag | CS8 :
    //  1010 1011 |  0001 0000   ->   1011 1011
    //  1010 -> CS5      0001 -> CS8
    com.c_cflag &= ~(CSIZE); // 0xF0
    com.c_cflag |= CS8;      // 将我们的 数据位 设置位 8bit -> 0x10

    com.c_cflag &= ~CSTOPB;  // 设置为1个bit位
    com.c_cflag |= CREAD;    // 使能接收
    com.c_cflag &= ~PARENB;  // 不使能我们的奇偶校验位
    com.c_cflag |= CLOCAL;   // 忽略调制解调的过程
    com.c_cflag &= ~CRTSCTS; // 不使用流控

    cfsetispeed(&com, B9600);
    cfsetospeed(&com, B9600);

    tcflush(fd, TCSAFLUSH); // 刷新我缓冲区，怕和别人的数据重合。。。

    tcsetattr(fd, TCSANOW, &com);

    return fd;
}

void *GetTouchXY(void *arg) {
    struct Point *p = (struct Point *)arg;
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch < 0) {
        perror("filed to open touch screen");
        exit(-1);
    }

    int ret;
    struct input_event ev;
    int x = -1, y = -1;
    while (1) {
        ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev)) {
            continue;
        }

        if (x >= 0 && y >= 0) {
            p->x = x;
            p->y = y;
            x = y = -1;
            printf("x: %d\n,y : %d", p->x, p->y);
        }

        if (ev.type == EV_ABS && ev.code == ABS_X) //这是一个x轴坐标的输入事件
        {
            if (x < 0)
                x = ev.value;

        } else if (ev.type == EV_ABS &&
                   ev.code == ABS_Y) //这是一个y轴坐标的输入事件
        {
            if (y < 0 && x > 0)
                y = ev.value;
        }
    }
}
void *getSmokeDate(void *arg) {
    unsigned char cmd[10] = {0xFF, 0x1, 0x86, 0, 0, 0, 0, 0, 0x79};
    unsigned char buf[10] = {0};
    int *n = (int *)arg;
    int fd = open("/dev/ttySAC1", O_RDWR);
    if (fd < 0) {
        perror("-------------open Somke error \n");
        exit(-1);
    }
    Write(fd, cmd, 9);
    while (1) {
        Read(fd, buf, 9);
        if (buf[0] == 0xff && buf[1] == 0x86) {
            *n = buf[2] << 8 | buf[3];
            // printf("somke is  %d \n", *n);
        } else {
            printf("-----------somke read error   \n");
        }

        sleep(2);
    }
}
void *getGY39Date(void *arg) {
    int gy39_fd = uart_com_init(COM2);
    if (gy39_fd < 0) {
        perror("GY39 open error\n");
        exit(-1);
    }
    struct GY39Date *gy39Date = (struct GY39Date *)arg;
    //全部测试：返回24字节
    unsigned char cmd[3] = {0xA5, 0x83, 0x28};
    //单独测试光照，返回9字节
    unsigned char cmd2[3] = {0xA5, 0x51, 0xF6};
    //单独测试温度，湿度，气压，海拔，返回15字节
    unsigned char cmd3[3] = {0xA5, 0x52, 0xF7};
    unsigned char buf[24] = {0};

    while (1) {
        if (Write(gy39_fd, cmd3, 3) == 3) {
            Read(gy39_fd, buf, 15);
            for (int i = 0; i < 15; i++) {
                printf("%d:%x ", i, buf[i]);
            }
            printf("\n");
            if (buf[0] == 0x5a && buf[1] == 0x5a && buf[2] == 0x45) {
                gy39Date->temperature = (buf[4] << 8 | buf[5]) / 100;
                gy39Date->pressure =
                    (buf[6] << 24 | buf[7] << 16 | buf[8] << 8 | buf[9]) / 100;
                gy39Date->humidity = (buf[10] << 8 | buf[11]) / 100;
                gy39Date->altitude = (buf[12] << 8 | buf[13]) / 100;
            }
        }
        sleep(2);
    }
}
int dray_mainWiget(int *des, int *Background, struct Point *point) {
    //放置背景1
    display_bmp(0, 0, path[*Background], des);
    struct Point p;
    p.x = -1;
    p.y = -1;
    while (1) {

        //灯光开关
        if (p.x != point->x || p.y != point->y) {
            // printf("x:%d,y:%d\n",point->x,point->y);
            p.x = point->x;
            p.y = point->y;
            if ((p.x - LIGHT_X) * (p.x - LIGHT_X) +
                    (p.y - LIGHT_Y) * (p.y - LIGHT_Y) <
                50 * 50) {
                // printf("p->x=%d,p->y=%d\n",p.x,p.y);
                if (*Background == 0) {
                    display_bmp(0, 0, path[1], des);
                    printf("+18 亚特兰蒂斯24K钛合金Pro 5G 故宫尊享版 "
                           "小台灯『亮』了\n");
                    *Background = 1;
                } else if (*Background == 1) {
                    display_bmp(0, 0, path[0], des);
                    printf("+18 亚特兰蒂斯24K钛合金Pro 5G 故宫尊享版 "
                           "小台灯『灭』了\n");
                    *Background = 0;
                }
                printf("------------ p->x=%d,p->y=%d\n", p.x, p.y);
                usleep(500);
            }
            //数据界面
            else if ((p.x - DATE_X) * (p.x - DATE_X) +
                         (p.y - DATE_Y) * (p.y - DATE_Y) <
                     50 * 50) {
                return 1; //返回数据界面
            } else if ((p.x - GAME_X) * (p.x - GAME_X) +
                           (p.y - GAME_Y) * (p.y - GAME_Y) <
                       50 * 50) {
                /* code */
                return 2;
            }
        }
        // sleep(1);
    }
}
int main() {
    int *des = NULL;
    //初始化界面
    des = MmapGetLcd();
    pthread_t TouchThread, thread1, thread2;
    ;
    struct Point p;

    int smoke;
    struct GY39Date gy39date;
    if (pthread_create(&TouchThread, NULL, GetTouchXY, &p)) {
        perror("Touch Thread  error\n");
        exit(-1);
    }
    /*if(pthread_create(&thread1,NULL,getSmokeDate,&smoke))
    {
        perror("smoke thread error\n");
        exit(-1);
    }*/
    if (pthread_create(&thread2, NULL, getGY39Date, &gy39date)) {
        perror("GY39 thread error\n");
        exit(-1);
    }
    int background = 0;
    while (1) {
        int whichWiget = dray_mainWiget(des, &background, &p);
        if (whichWiget == 1) //数据界面
        {
            DateWiget(&p, &smoke, &gy39date, des);
            continue;
        } else if (whichWiget == 2) {
            /* code */
            GameWiget(des, &p);
            continue;
        }
    }
}