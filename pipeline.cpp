#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include<ctime>
#include<arm_neon.h>
using namespace std;
void RAW()//先写后读
{
    for (int i = 0; i < 1000000000; ++i) {
        volatile int a = i;
        volatile int b = i + 1;
        a = a + 2;
        b = a + 3;
    }
}
void WAR()//先读后写
{
    for (int i = 0; i < 1000000000; ++i) {
        volatile int a = i;
        volatile int b = i + 1;
        a = b + a;
        b = a + b;
    }
}
void WAW()//写后再写
{
    for (int i = 0; i < 1000000000; ++i) {
        volatile int a = i;
        volatile int b = i + 1;
        a = i + 2;
        b = i + 3;
    }
}
void avoidhzd()
{
    for (int i = 0; i < 1000000000; ++i) {
        volatile int a = i + 2;
        volatile int b = i + 4;
    }
}
int main()
{
    struct timeval start, end1, end2, end3, end4;
    long t1, t2, t3, t4, r;
    gettimeofday(&start, NULL);
    RAW();
    gettimeofday(&end1, NULL);
    WAR();
    gettimeofday(&end2, NULL);
    WAW();
    gettimeofday(&end3, NULL);
    avoidhzd();
    gettimeofday(&end4, NULL);
    t1 = (end1.tv_sec * 1000 * 1000 + end1.tv_usec)
        - (start.tv_sec * 1000 * 1000 + start.tv_usec);
    t2 = (end2.tv_sec * 1000 * 1000 + end2.tv_usec)
        - (end1.tv_sec * 1000 * 1000 + end1.tv_usec);
    t3 = (end3.tv_sec * 1000 * 1000 + end3.tv_usec)
        - (end2.tv_sec * 1000 * 1000 + end2.tv_usec);
    t4 = (end4.tv_sec * 1000 * 1000 + end4.tv_usec)
        - (end3.tv_sec * 1000 * 1000 + end3.tv_usec);
    printf("先读后写时间 / us: % ld", t1);
    printf("\n先写后读时间/us: %ld", t2);
    printf("\n先写再写时间 / us: % ld", t3);
    printf("\n避免数据冒险时间/us: %ld", t4);

    return 0;
}
