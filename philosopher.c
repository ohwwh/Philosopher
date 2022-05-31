#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    struct timeval stv, etv;
    gettimeofday(&stv, 0);
    usleep(1);
    gettimeofday(&etv, 0);
    printf("%d\n", etv.tv_usec - stv.tv_usec);
}