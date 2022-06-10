#include "philosopher.h"

void    ft_msleep(int time)
{
    struct timeval mytime;
    long target;

    gettimeofday(&mytime, 0);
    target = time + (mytime.tv_sec * 1000) + (mytime.tv_usec / 1000);
    while (target > (mytime.tv_sec * 1000) + (mytime.tv_usec / 1000))
    {
        gettimeofday(&mytime, 0);
        usleep(100);
    }
    }

int is_one(int n, t_philo *philo)
{
    const int       number = philo->sh_info->philo_num;

    if (RIGHT == LEFT)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        printf("at %ld %dth philosopher died - RIP\n", philo->former + 810, n);
        philo->sh_info->end = 1;
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
        return (1);
    }
    return (0);
}

void    ft_mutex_lock(int n, t_philo *philo)
{
    const int       number = philo->sh_info->philo_num;

    if (RIGHT == LEFT)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
        return ;
    }
    if (n % 2)
        pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
    else
    {
        if (philo->state == 0)
            usleep(200 * 1000);
        pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
    }
    if (n % 2)
        pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
    else
        pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
}

void    ft_mutex_unlock(int n, t_philo *philo)
{
    const int       number = philo->sh_info->philo_num;

    if (RIGHT == LEFT)
    {
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        return ;
    }
    if (n % 2)
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
    else
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
    if (n % 2)
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
    else
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
}

long    time_stamp(long sec, long usec, t_philo *philo)
{
    long    ret;
    long    s_ret;
    long    u_ret;

    s_ret = (sec - philo->sh_info->std_sec) * 1000000;
    u_ret = usec - philo->sh_info->std_usec;
    ret = (s_ret + u_ret) / 1000;
    return (ret);
}
void    start_eating(int n, t_philo *philo)
{
    struct timeval  mytime;
    long            wait;

    gettimeofday(&mytime, NULL);
    wait = time_stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former;
    printf("at %ld %dth philosopher start eating! waiting time: %ld, last eating: %ld\n", 
    time_stamp(mytime.tv_sec, mytime.tv_usec, philo), n, 
    wait,
    philo->former);
    philo->former = time_stamp(mytime.tv_sec, mytime.tv_usec, philo);
}

void    finish_eating(int n, t_philo *philo)
{
    struct timeval mytime;

    gettimeofday(&mytime, 0);
    printf("at %ld %dth philosopher finish eating!\n", time_stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
    philo->state ++;
}

int picking(int n, t_philo *philo)
{
    const int   number = philo->sh_info->philo_num;
    struct timeval mytime;
    long            wait;

    gettimeofday(&mytime, NULL);
    wait = time_stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former;
    if (wait > 609)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        printf("at %ld %dth philosopher died - RIP\n", wait + philo->former, n);
        philo->sh_info->end = 1;
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
        return (1);
    }
    else
        printf("at %ld %dth philosopher grab the forks!\n ", time_stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
    return (0);
}

void    eating(int n, t_philo *philo)
{
    const int   number = philo->sh_info->philo_num;

    start_eating(n, philo);
    ft_msleep(200);
    //usleep(200 * 1000);
    finish_eating(n, philo);
}

void sleeping(void)
{
    ft_msleep(200);
    //usleep(200 * 1000);
}

void thinking(void)
{
    usleep(500);
}

void    *philo_routine(void *data)
{
    t_philo         *philo;
    struct timeval  mytime;
    int             flag;

    //스레드의 탄생시점
    philo = (t_philo *)data;
    const int       n = philo->th_num + 1;
    const int       number = philo->sh_info->philo_num;
    gettimeofday(&mytime, 0);
    philo->former = time_stamp(mytime.tv_sec, mytime.tv_usec, philo);
    while (philo->state < 100)
    {
        if (is_one(n, philo))
            return ((void *)n);
        ft_mutex_lock(n, philo);
        if (picking(n, philo))
             return ((void *)n);
        eating(n, philo);
        ft_mutex_unlock(n, philo);
        sleeping();
        thinking(); //비대칭으로 포크를 잡게 하여 데드락을 해결하는 코드
    }
    return ((void *)n);
}

int main(int argc, char *argv[])
{
    int         j;
    t_philo     *philo;
    const int   n = atoi(argv[1]);

    j = 0;
    philo = philo_init(n);
    while (j < n)
    {
        pthread_create(&(philo[j].thread_t), NULL, philo_routine, (void *)(&philo[j]));
        pthread_detach(philo[j].thread_t);
        j ++;
    }
    while (1)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        if (philo->sh_info->end != 0)
        {
            pthread_mutex_unlock(&(philo->sh_info->mutex_c));
            break ;
        }
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
    }
    j = 0;
    while (j < n)
        pthread_mutex_destroy(&(philo->sh_info->mutex_s[j ++]));
    pthread_mutex_destroy(&(philo->sh_info->mutex_c));
    free_all(philo);
    //철학자 스레드들이 돌아가는 와중에 free된 메모리를 건드릴수도 있음
	//철학자 스레드들을 모조리 종료시키고 메인 스레드를 종료 시키는 방향으로 다시 짜야 하나......?
}
