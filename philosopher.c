#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int fork_num[5] = {1, 1, 1, 1, 1};
int fork_own[5] = {0, 0, 0, 0, 0};
int state[5] = {0, 0, 0, 0, 0};
int start;
pthread_mutex_t mutex_s;
pthread_mutex_t mutex_n;

void    picking(int n)
{
    
    struct timeval mytime;
    pthread_mutex_lock(&mutex_s);
    if (fork_num[(n - 1 + 5) % 5])
    {
        fork_num[(n - 1 + 5) % 5] --;
        fork_own[n - 1] ++;
        gettimeofday(&mytime, NULL);
        //printf("at %d %dth philosopher grab the right fork! [%d], [%d], [%d], [%d], [%d]\n", mytime.tv_usec - start, n, fork_num[0], fork_num[1], fork_num[2], fork_num[3], fork_num[4]);
    }
    pthread_mutex_unlock(&mutex_s);
    pthread_mutex_lock(&mutex_s);
    if (fork_num[(n - 2 + 5) % 5])
    {
        fork_num[(n - 2 + 5) % 5] --;
        fork_own[n - 1] ++;
        gettimeofday(&mytime, NULL);
        //printf("at %d %dth philosopher grab the left fork! [%d], [%d], [%d], [%d], [%d]\n", mytime.tv_usec - start, n, fork_num[0], fork_num[1], fork_num[2], fork_num[3], fork_num[4]);
    }
    pthread_mutex_unlock(&mutex_s);
}

void    eating(int n)
{
    struct timeval mytime;

    pthread_mutex_lock(&mutex_s);
    if (fork_own[n - 1] == 2)
    {
        usleep(100);
        fork_num[(n - 1 + 5) % 5] ++;
        fork_num[(n - 2 + 5) % 5] ++;
        fork_own[n - 1] = 0;
        state[n - 1] ++;
        gettimeofday(&mytime, NULL);
        printf("at %d %dth philosopher finish eating! [%d], [%d], [%d], [%d], [%d]\n", mytime.tv_usec - start, n, fork_num[0], fork_num[1], fork_num[2], fork_num[3], fork_num[4]);
        pthread_mutex_unlock(&mutex_s);
    }
    pthread_mutex_unlock(&mutex_s);
}

void sleeping(int n)
{
    usleep(100);
}

void thinking(int n)
{
    usleep(100);
}

void    *philo(void *data)
{
    uintptr_t n = (int)data;
    int       flag = 0;
    struct timeval mytime;

    while (state[n - 1] < 5)
    {
        picking(n);
        eating(n);
        sleeping(n);
        thinking(n);
    }
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
        pthread_create(&thread_t[n - 1], NULL, philo, (void *)(uintptr_t)n);
        n ++;
    }
    while (j < 6)
    {
        pthread_join(thread_t[j - 1], NULL);
        j ++;
    }
    pthread_mutex_destroy(&mutex_s);
    pthread_mutex_destroy(&mutex_n);
    //while(1);
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31
