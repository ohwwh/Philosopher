#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void    *grab_the_fork(void *data)
{
    int i;

    printf("%dth philosopher grab the fork!\n", *(int *)data);
    return ((void *)i);
}

int main(void)
{
    pthread_t thread_t[5];
    int status;
    int n = 1;

    printf("%dth philosopher grab the fork!\n", n ++);
    while (n < 7)
    {
        pthread_create(&thread_t[n - 2], NULL, grab_the_fork, (void *)&n);
        pthread_join(thread_t[n - 2], (void **)&status);
        printf("return thread %d\n", n ++);
    }
}