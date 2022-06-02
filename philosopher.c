#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int number_of_fork = 6;
int start;

void    *grab_the_fork(void *data)
{
    int i;


    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    number_of_fork --;
    printf("at %d %dth philosopher grab the fork! fork is %d\n", mytime.tv_usec - start,  *(int *)data, number_of_fork);

  
    return ((void *)i);
}

int main(void)
{
    pthread_t thread_t[5];
    int status;
    int n = 1;


    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    start = mytime.tv_usec;
    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher grab the fork!\n",mytime.tv_usec - start, n ++);
    while (n < 7)
    {
        pthread_create(&thread_t[n - 2], NULL, &grab_the_fork, (void *)&n);
        pthread_detach(thread_t[n - 2]);
        //printf("return thread %d\n", n ++);
        n ++;
    }
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31
