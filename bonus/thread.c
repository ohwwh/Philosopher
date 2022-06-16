#include "philosopher.h"

static int  iter_condition(t_philo *philo)
{
    if (philo->sh_info->must_eat == -1)
        return (1);
    else
        return (philo->state < philo->sh_info->must_eat);
}

static void    start_simulation(int number, t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        if (philo->sh_info->cnt != number)
            philo->sh_info->cnt ++;
        if (philo->sh_info->cnt == number)
        {
            pthread_mutex_unlock(&(philo->sh_info->mutex_c));
            break ;
        }
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
    }
}

static void    simulation(int n, int number, t_philo *philo)
{
    while (iter_condition(philo))
    {   
        if (number == 1)
        {
            ft_msleep(philo->sh_info->time_to_die + 100);
            break ;
        }
        fork_mutex_lock(n, philo);
        if (picking(n, philo) || eating(n, philo))
        {
            fork_mutex_unlock(n, philo);
            break ;
        }
        fork_mutex_unlock(n, philo);
        sleeping(philo);
        thinking();
    }
}

void    *routine(t_philo *philo)
{
    struct timeval  mytime;
    int             n;
    int             number;

    n = philo->th_num + 1;
    number = philo->sh_info->philo_num; 
    start_simulation(number, philo);
    gettimeofday(&mytime, 0);
    pthread_mutex_lock(&(philo->sh_info->mutex_m[n - 1]));
    philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
    pthread_mutex_unlock(&(philo->sh_info->mutex_m[n - 1]));
    simulation(n, number, philo);
    philo->end = 1;
    pause();
    return ((void *)n);
}