#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void    *grab_the_fork(void *data)
{
    int i;


    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher grab the fork!\n", mytime.tv_usec,  *(int *)data);

  
    return ((void *)i);
}

int main(void)
{
    pthread_t thread_t[5];
    int status;
    int n = 1;


    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher grab the fork!\n",mytime.tv_usec, n ++);
    while (n < 7)
    {
        pthread_create(&thread_t[n - 2], NULL, grab_the_fork, (void *)&n);
        pthread_join(thread_t[n - 2], (void **)&status);
        //printf("return thread %d\n", n ++);
        n ++;
    }
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31
