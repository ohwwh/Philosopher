#include "philosopher.h"

int    test(int n, t_philo *philo)
{
    const int   number = philo->sh_info->philo_num;
    int         ret;

    ret = 0;
    if (philo->sh_info->fork_num[LEFT] == 1)
    {
        if (philo->sh_info->fork_num[RIGHT] ==1)
            ret = 1;
    }
    return (ret);
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
}

void    finish_eating(int n, t_philo *philo)
{
    struct timeval mytime;

    gettimeofday(&mytime, 0);
    printf("at %ld %dth philosopher finish eating!\n", time_stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
    philo->former = time_stamp(mytime.tv_sec, mytime.tv_usec, philo);
    philo->state ++;
}

int picking(int n, t_philo *philo)
{
    const int   number = philo->sh_info->philo_num;
    struct timeval mytime;
    long            wait;

    /*philo->sh_info->fork_num[LEFT] --;
    philo->sh_info->fork_num[RIGHT] --;
    philo->sh_info->fork_own[n - 1] += 2;*/

    gettimeofday(&mytime, NULL);
    wait = time_stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former;
    if (wait > 600)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        printf("%dth philosopher died - RIP\n", n);
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
    usleep(200 * 1000);
    /*philo->sh_info->fork_num[LEFT] ++;
    philo->sh_info->fork_num[RIGHT] ++;
    philo->sh_info->fork_own[n - 1] = 0;*/
    finish_eating(n, philo);
}

void sleeping(void)
{
    usleep(200 * 1000);
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
        if (n % 2)
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
        else
        {
            usleep(100 * 1000);
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
        }
        if (n % 2)
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
        else
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
        if (picking(n, philo))
             return ((void *)n);
        eating(n, philo);
        if (n % 2)
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        else
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
        if (n % 2)
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
        else
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        sleeping();
        thinking(); //비대칭으로 포크를 잡게 하여 데드락을 해결하는 코드

        /*if (n % 2 == 0)
            usleep(100 * 1000);
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        flag = test(n, philo);
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
        if (flag == 1)
        {
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
            picking(n, philo);
            eating(n, philo);
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        }
        sleeping();
        thinking(); //양 쪽 포크를 다 집을 수 있을 때만 잡게 하여 데드락을 해결하는 코드*/
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
    /*j = 0;
    while (j < n)
    {
        pthread_join(philo[j].thread_t, NULL);
        j ++;
    }*/
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
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31