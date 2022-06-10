#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdint.h>

int start;

void	eating(int n)
{
	struct timeval mytime;
	gettimeofday(&mytime, 0);
	printf("%d : %d\n", n, mytime.tv_usec);
}

void	*routine(void *data)
{
	int n = (intptr_t)data;
	//struct timeval mytime;
	//gettimeofday(&mytime, 0);
	//printf("at %d %dth thread is created\n", mytime.tv_usec - start, n + 1);
	eating(n);
	return ((void *)n);
}

int	main(void)
{
	pthread_t thread[100];
	int	n = 5;
	int	j = 0;
	struct timeval mytime;

	gettimeofday(&mytime, 0);
	start = mytime.tv_usec;
	while (j < n)
    {
        pthread_create(&thread[j], NULL, routine, (void *)(intptr_t)j);
        j ++;
    }
    j = 0;
    while (j < n)
    {
        pthread_join(thread[j], NULL);
        j ++;
    }
}
