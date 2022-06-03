#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int afork[5] = {2, 2, 2, 2, 2};
int start;
pthread_mutex_t mutex_s;
pthread_mutex_t mutex_n;

void    *grab_the_fork(void *data)
{
    uintptr_t n = (int)data;

    struct timeval mytime;
    pthread_mutex_lock(&mutex_s);
    gettimeofday(&mytime, NULL);
    afork[(n - 1 + 5) % 5] --;
    pthread_mutex_unlock(&mutex_s);
    printf("at %d %luth philosopher grab the left fork! [%d], [%d], [%d], [%d], [%d]\n", mytime.tv_usec - start,  n, afork[0], afork[1], afork[2], afork[3], afork[4]);
    pthread_mutex_lock(&mutex_s);
    gettimeofday(&mytime, NULL);
    afork[(n - 2 + 5) % 5] --;
    pthread_mutex_unlock(&mutex_s);
    printf("at %d %luth philosopher grab the right fork! [%d], [%d], [%d], [%d], [%d]\n", mytime.tv_usec - start,  n, afork[0], afork[1], afork[2], afork[3], afork[4]);

    return ((void *)n);
}

int main(void)
{
    pthread_t thread_t[5];
    int status;
    int j = 1;
    int n = 1;
    int index[5];

    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    start = mytime.tv_usec;
    pthread_mutex_init(&mutex_s, 0);
    pthread_mutex_init(&mutex_n, 0);
    gettimeofday(&mytime, NULL);
    while (n < 6)
    {
        pthread_create(&thread_t[n - 1], NULL, grab_the_fork, (void *)(uintptr_t)n);
        n ++;
    }
    while (j < 6)
    {
        pthread_join(thread_t[j - 1], NULL);
        j ++;
    }
    //while(1);
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31