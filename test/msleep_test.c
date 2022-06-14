#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdint.h>

void    ft_msleep(int time)
{
    struct timeval mytime;
    long target;

    gettimeofday(&mytime, 0);
    target = time * 1000 + (mytime.tv_sec * 1000000) + (mytime.tv_usec);
    while (target > (mytime.tv_sec * 1000000) + (mytime.tv_usec))
    {
        usleep(500);
        gettimeofday(&mytime, 0);
    }
}

long    time_stamp(long sec, long usec, long std_sec, long std_usec)
{
    long    ret;
    long    s_ret;
    long    u_ret;

    s_ret = (sec - std_sec) * 1000;
    u_ret = (usec - std_usec) / 1000;
    ret = s_ret + u_ret;
    return (ret);
}

int main(void)
{
    struct timeval mytime;
    int std_sec;
    int std_usec;

    while (1)
    {
         gettimeofday(&mytime, 0);
        std_sec = mytime.tv_sec;
        std_usec = mytime.tv_usec;
        printf("%ld\n", time_stamp(mytime.tv_sec, mytime.tv_usec, std_sec, std_usec));
        ft_msleep(400);
        gettimeofday(&mytime, 0);
        printf("%ld\n", time_stamp(mytime.tv_sec, mytime.tv_usec, std_sec, std_usec));
    }
}