#include "philosopher.h"

void    test(int n, t_philo *philo)
{
    
}

void    print_start_eating(int n, t_philo *philo)
{
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher start eating! waiting time: %d, last eating: %d\n", 
    mytime.tv_usec - philo->sh_info->start, n, 
    mytime.tv_usec - philo->former,
    philo->former - philo->sh_info->start);
}

void    print_finish_eating(int n, t_philo *philo)
{
    int i;
    const int   number = philo->sh_info->philo_num;

    i = 0;
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher finish eating!\n", mytime.tv_usec - philo->sh_info->start, n);
    pthread_mutex_lock(&(philo->sh_info->mutex_s[(n + number) % number]));
    pthread_mutex_lock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));
    //pthread_mutex_lock(&philo->sh_info->mutex_c);
    philo->sh_info->fork_num[(n + number) % number] ++;
    philo->sh_info->fork_num[(n - 2 + number) % number] ++;
    philo->fork_own = 0;
    philo->state ++;
    philo->former = mytime.tv_usec;
    //pthread_mutex_unlock(&philo->sh_info->mutex_c);
    pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n + number) % number]));
    pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));
}

void    print_picking(int n, t_philo *philo)
{
    int i;

    i = 0;
    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher grab the forks! / ", mytime.tv_usec - philo->sh_info->start, n);
    while (i < philo->sh_info->philo_num)
        printf("[%d] ", philo->sh_info->fork_num[i ++]);
    printf("\n");
}

void    picking(int n, t_philo *philo)
{
    struct timeval mytime;
    const int   number = philo->sh_info->philo_num;

    pthread_mutex_lock(&(philo->sh_info->mutex_s[(n + number) % number]));
    pthread_mutex_lock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));
    //pthread_mutex_lock(&philo->sh_info->mutex_c);
    if (philo->sh_info->fork_num[(n + number) % number] && philo->sh_info->fork_num[(n - 2 + number) % number])
    {
        philo->sh_info->fork_num[(n + number) % number] --;
        philo->sh_info->fork_num[(n - 2 + number) % number] --;
        print_picking(n, philo);
        philo->fork_own += 2;
    }
    //pthread_mutex_unlock(&philo->sh_info->mutex_c);
    pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n + number) % number]));
    pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));
}

void    eating(int n, t_philo *philo)
{
    struct timeval mytime;
    const int   number = philo->sh_info->philo_num;

    if (philo->fork_own == 2)
    {   
        print_start_eating(n, philo);
        usleep(200);
        print_finish_eating(n, philo);
    }
}

void sleeping(void)
{
    usleep(200);
}

void thinking(void)
{
    //usleep(200);
}

void    *philo_routine(void *data)
{
    t_philo *philo = (t_philo *)data;
    struct timeval mytime;
    gettimeofday(&mytime, 0);
    const int   n = philo->th_num + 1;
    const int   number = philo->sh_info->philo_num;

    philo->former = mytime.tv_usec;
    while (philo->state < 1)
    {
        /*pthread_mutex_lock(&(philo->sh_info->mutex_s[(n + number) % number]));
        pthread_mutex_lock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));*/
        picking(n, philo);
        eating(n, philo);
        /*pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n - 2 + number) % number]));
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[(n + number) % number]));*/
        sleeping();
        //thinking();
    }
    /*printf("%dth fork_own: %d / [%d], [%d], [%d], [%d], [%d]\n", n, philo->fork_own,
    philo->sh_info->fork_num[0], philo->sh_info->fork_num[1], philo->sh_info->fork_num[2], 
    philo->sh_info->fork_num[3], philo->sh_info->fork_num[4]);*/
    return ((void *)n);
}

int main(int argc, char *argv[])
{
    //pthread_t *thread_t;
    int status;
    int j = 0;
    const int   n = atoi(argv[1]);
    t_philo *philo;

    philo = philo_init(n);
    while (j < n)
    {
        pthread_create(&(philo[j].thread_t), NULL, philo_routine, (void *)(&philo[j]));
        j ++;
    }
    j = 0;
    while (j < n)
    {
        pthread_join(philo[j].thread_t, NULL);
        j ++;
    }
    pthread_mutex_destroy(&(philo->sh_info->mutex_c));
    free_all(philo);
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31
